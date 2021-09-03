


int get_index_from_timestamp(IFRAMEINFO *idxbuf, unsigned timestamp)
{
  int start=0, mid=0, end=0;

  assert (idxbuf);

  end = INDEX_COUNT(idxbuf)-1;

  if (start > end) {
    ERR("[2] Bad idxobject found. Aborting\n");
    return -ERR_BADIDX;
  }

#if 1
  {
    int i;
    for(i = 0; i < end; i++) {
      ERR("timestamp=%d, offset=%d\n",
          INDEX_STAMP(idxbuf, i),
          INDEX_OFFSET(idxbuf, i));
    }
  }
#endif
  while(1) {
    mid=(start+end)/2;
    if (timestamp==INDEX_STAMP(idxbuf, mid)) { /* Found exact stamp value. */
      break;
    }
    else if (timestamp < INDEX_STAMP(idxbuf, mid)) {
      end = mid - 1;
    }
    else if (timestamp > INDEX_STAMP(idxbuf, mid)) {
      start = mid + 1;
    }

    if (start>end) {	/* Could not find the data, but we know the most close one. */
      break;
    }
  }

  // In some cases, the first index value is incorrect.
  if(mid == 0) {
    if(INDEX_OFFSET(idxbuf, mid) > INDEX_OFFSET(idxbuf, mid+1)) {
      mid += 1;
    }
  }

  return	mid;
}


int playback_prepare_file_to_serve (ST_PLAYOBJ * playobj, struct st_request req, int scheme)
{
  int date, time;			/* Ssf date & time to play. */
  long ideal_stamp;
  int hdrsz, ret=-ERR_NOFILE;
  boolean	currecfile;
  int filesz, idxsz;

  assert (playobj);

  /* 1. Find ssf file that matching the request.
   * 2. Open ssf, idx file.
   * 3. Read in ssf header.
   * 	3.1 Request deletion if ssf header is invalid.
   * 4. Read in idx file.
   *	4.1 Request deletion if idx header is invalid.
   * 5. Find time stamp relative to start of the ssf.
   * 6. Get index number to start play from time stamp.
   * 7. Set video device properties according to the play stream.
   * 6. Set frame play routine.
   *
   */
  _DBG_R("CH %d: Request of prepare file (%d - %d DST:%d)\n", req.ch, req.date, req.time, req.dst);


  if ((find_ssf2_dst(playobj->ssfname, &date, &time, req.date, req.time, req.ch, req.dst, scheme)) < 0)
  {
    _DBG_R ("CH %d: Could not find ssf\n", req.ch);
    ret = -ERR_NOFILE;
    goto err;
  }

  _DBG_R("CH %d: file ssf (%s\n", req.ch, playobj->ssfname);

  playobj->req.date = date;
  playobj->req.time = time;
  playobj->req.ch = req.ch;
  playobj->req.playmode = req.playmode;
  playobj->req.playspeed = req.playspeed;
  playobj->req.dst = 0;

  if (strstr(playobj->ssfname, SSF_DST_EXTENSION))
    playobj->ssf_dst = TRUE;
  else
    playobj->ssf_dst = FALSE;


  {
    char * tmp;
    strcpy (playobj->idxname, playobj->ssfname);
    if ((tmp = strstr(playobj->idxname, SSF_SSF_EXTENSION))==NULL) {
      ret = -ERR_NOFILE;
      goto err;
    }
    strcpy(tmp, SSF_IDX_EXTENSION);
  }

  currecfile = isrecordingssf (playobj->ssfname);

  //if (currecfile)
  //	_DBG_R("Playback file is current rec ssf(%s)\n", playobj->ssfname);

  //_printf("open1) ssf=%s idx=%s\n", playobj->ssfname, playobj->idxname);
  if ((playobj->ssf = open(playobj->ssfname, O_RDONLY)) < 0) {
    perror ("open");
    _DBG_R ("filename = %s\n", playobj->ssfname);
    ret = -ERR_NOFILE;
    goto err;
  }

  if ((playobj->ssf_fp = fdopen (playobj->ssf, "r")) == NULL) {
    perror ("fdopen");
    ret = -ERR_NOFILE;
    goto err;
  }

  if ((playobj->idx = open (playobj->idxname, O_RDONLY)) < 0) {
    perror ("open");
    _DBG_R ("filename = %s\n", playobj->idxname);
    ret = -ERR_NOFILE;
    goto err;
  }

  if (getfilesz(playobj->ssf) <= SSFHDR_MINSZ) {
    if (currecfile==FALSE) {
      _DBG_R ("playback_prepare_file_to_serve: Too small ssf file (%s)\n", playobj->ssfname);
      remove_file (playobj->ssfname, 1);
      remove_file (playobj->idxname, 1);
#if __POS__
      remove_file (playobj->pdxname, 1);
#endif
    }
    ret = -ERR_SSFHDR;
    goto err;
  }

  idxsz = check_idxsz (playobj->idx, playobj->ssfname, playobj->idxname, currecfile);

  _DBG_R("CH %d: check_idxsz (sz: %d)\n", playobj->req.ch, idxsz);
  if (idxsz < 0) {
    ret = -ERR_IDXHDR;
    goto err;
  }

  if ((hdrsz = read_ssfhdr (playobj->ssf, playobj->ssfhdr)) < 0) {
    if (currecfile==FALSE) {
      _DBG_R ("playback_prepare_file_to_serve: Bad ssf header (%s)\n", playobj->ssfname);
      remove_file (playobj->ssfname, 1);
      remove_file (playobj->idxname, 1);
#if __POS__
      remove_file (playobj->pdxname, 1);
#endif
    }
    ret = -ERR_SSFHDR;
    goto err;
  }
  _DBG_R("hdrsz (%d)\n", hdrsz);

  if ((playobj->filep=(FILEPROP *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_FILEPROP))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->videop=(VIDEOPROP *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_VIDEOPROP))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->audiop=(AUDIOPROP *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_AUDIOPROP))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->indexp=(IFRAMEPROP *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_IFRAMEPROP))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->eventp=(EVENTPROP *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_EVENTPROP))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->dataobj=(DATAHDR *)get_propobj(playobj->ssfhdr, hdrsz, SSFID_DATAHDR))==NULL) {
    ret = -ERR_SSFHDR;
    goto err;
  }

  if ((playobj->idxmap = mmap (0, MAX_IDXFILESZ,  PROT_READ, MAP_SHARED | MAP_FILE, playobj->idx, 0)) == (char *)-1) {
    ERR("mmap\n");
    perror("mmap");
    ret = -ERR_MEM;
    goto err;
  }

  playobj->idxend = playobj->idxmap + MAX_IDXFILESZ;

  filesz = check_idxhdr(playobj->idxmap);

  _DBG_R("CH %d: check_idxhdr (sz: %d)\n", playobj->req.ch, filesz);

  if (filesz < 0) {
    if (currecfile == FALSE) {
      _DBG_R ("playback_prepare_file_to_serve: Bad idx header (%s)\n", playobj->idxname);
      remove_file (playobj->ssfname, 1);
      remove_file (playobj->idxname, 1);
#if __POS__
      remove_file (playobj->pdxname, 1);
#endif
    }
    ret = -ERR_IDXHDR;
    goto err;
  }

  if (scheme == SEEK_FORWARD) {
    if (gettime_dst2(playobj->req.time) < gettime_dst2(req.time))
      req.time = playobj->req.time;

  } else if (scheme == SEEK_BACKWARD) {
    if (gettime_dst2(playobj->req.time) > gettime_dst2(req.time))
      req.time = 23016060;
  }

  ideal_stamp = get_timestamp (req, playobj->ssfhdr, hdrsz) * 1000;

  _DBG_R("CH %d: %d, %d ideal_stamp (%ld)\n", req.ch, req.date, req.time, ideal_stamp);
  _DBG_R("CH %d: %lu, %u\n", req.ch, INDEX_ID((IFRAMEINFO *)playobj->idxmap), INDEX_COUNT((IFRAMEINFO *)playobj->idxmap));

  playobj->idxstart = get_index_from_timestamp ((IFRAMEINFO *)playobj->idxmap, ideal_stamp);

  if (playobj->idxstart < 0) {
    if (currecfile == FALSE) {
      _DBG_R ("playback_prepare_file_to_serve: Bad idx header2 (%s)\n", playobj->idxname);
      remove_file (playobj->ssfname, 1);
      remove_file (playobj->idxname, 1);
#if __POS__
      remove_file (playobj->pdxname, 1);
#endif
    }
    ret = -ERR_IDXHDR;
    goto err;
  }

  playobj->index = playobj->idxstart;
  playobj->offset = INDEX_OFFSET (playobj->idxmap, playobj->index);

  playobj->creatime_sec = get_ssf_creation_time (playobj->ssfhdr, hdrsz);

  {
    long encryptkey =  FILEPROP_ENCKEY (playobj->filep);
    BF_Init (& playobj->ctx, & encryptkey);
  }


  _DBG_R ("CH %d: %s, DATE=%d TIME=%d IDX=%d OFF=%d\n", req.ch, playobj->ssfname, date, time, playobj->index, playobj->offset);
  return 0;
err:
  __playobj_release(playobj);
  _DBG_R ("CH %d: FAILED TO PREPARE PLAYOBJ (%d - %d) BY %d\n", req.ch, req.date, req.time, ret);
  return ret;
}


inline int playback_prepare_next_file_to_serve(ST_PLAYOBJ *playobj, struct st_request req) {
  return playback_prepare_file_to_serve(playobj, req, SEEK_FORWARD);
}


static int vod_nextfile (struct st_stream *svr, int playmode, int cam)
{
	int ret;
	ST_PLAYOBJ *newobj = NULL;
	ST_PLAYOBJ *playobj = VOD (svr, cam).playobj;
	
	newobj = playobj_init("vod_nextfile");
	
	playback_frame_flush (playobj);
	
	switch (playmode) {		
	case PLAYMODE_FB:

		SEARCH_LOCK ();
		ret = playback_prepare_file_to_serve(newobj, playobj->req, SEEK_BACKWARD);
		SEARCH_UNLOCK ();
	
		if (ret < 0) {
			_DBG_G ("CH:%d  Failed to prepare prev file\n", playobj->req.ch);
			playobj_release (newobj);
			newobj = NULL;
		}
		else {
			_DBG_G ("CH:%d Success to prepare prev file (%s)\n", playobj->req.ch, newobj->ssfname);
			playobj_release (playobj);			
			VOD (svr, cam).playobj = newobj;
			return 0;
		}
		break;
		
	case PLAYMODE_PLAY:
	case PLAYMODE_FF:
	default:

		SEARCH_LOCK ();
		ret = playback_prepare_file_to_serve(newobj, playobj->req, SEEK_FORWARD);
		SEARCH_UNLOCK ();

		if (ret < 0) {
			_DBG_G ("CH:%d  Failed to prepare next file\n", playobj->req.ch);
			playobj_release (newobj);
			newobj = NULL;
		}
		else {
			_DBG_G ("CH:%d Success to prepare next file (%s)\n", playobj->req.ch, newobj->ssfname);
			playobj_release (playobj);
			VOD (svr, cam).playobj = newobj;
			return 0;
		}
		break;
	}

	if (newobj)
		playobj_release(newobj);

	return ret;
	
}



static int handle_nextplay(struct st_stream *strsvr, int sd, struct phdr *ph) {

	struct preqnextplay	req;
	int rethdr;
	int cam;

	{// Get request data.
		char buf[1*K];
		char *tmp = buf;

		recvmsgfrom(strsvr, sd, buf, ph->len);

		setfield (char, req.cam , tmp);
	}
	_DBG_G("handle_nextplay ch=%d\n", req.cam);
	cam = req.cam;

	if (! VALIDCH (cam)) {
		return REPLY_CAM (RETBADPARM);
	}

	rethdr = vod_nextfile (strsvr, VOD (strsvr, cam).prevmode, cam);

	switch (rethdr) {
	case 0:
		// set previous playmode
		if (VOD (strsvr, cam).cmd.playmode == PLAYMODE_STOP)
			VOD (strsvr, cam).cmd.playmode = VOD (strsvr, cam).prevmode;

		VOD (strsvr, cam).transhdr = 1;
		return REPLY_CAM (RETSUCCESS);
		//return 0;

	case -ERR_NOFILE:
		return REPLY_CAM (RETNOFILE);

	case -ERR_MEM:
		return REPLY_CAM (RETNOFILE);

	case -ERR_SSFHDR:
	case -ERR_IDXHDR:
		return REPLY_CAM (RETBADFILE);

	default:
		return REPLY_CAM (RETINTER);
	}

}



int vod_transframe (struct st_stream *svr, int cam) {

	ST_PLAYOBJ *playobj = NULL;
	struct st_frame * buf = NULL;		// The frame to be sent.
	int ret= 0;
	__u64 playstamp;

	assert (svr);

	playobj = VOD (svr, cam).playobj;

	if (VOD (svr, cam).transhdr) {
		vod_transhdr (svr, cam);
		VOD (svr, cam).transhdr = FALSE;
	}

	if (PLAYBACK_EMPTY_FRAMEBUFFER (playobj))
		goto read_frame;

	buf = clist_entry (playobj->buf_head.next, struct st_frame, iframe);
	playstamp = playobj->creatime_sec *1000 +DATAUNIT_STAMP ((DATAUNIT *) buf->data_unit);

#ifdef __VOD_SYNC__
	{
		int i;
		__u64 baseline = 0;

		switch(PLAYBACK_PLAYMODE(playobj)) {
		case PLAYMODE_PLAY:
		case PLAYMODE_FF:
			foreach_cam_ch(i)
				if (svr->netstamp [i] > 0) {
					if (baseline == 0)
						baseline = svr->netstamp [i];

					if (baseline > svr->netstamp [i])
						baseline = svr->netstamp [i];
				}
			end_foreach

			if (baseline >= playstamp) {
				__transframe (svr, buf, cam);
				svr->netstamp[cam] = 0;
				debugf("---ch=%d, %Ld\n", cam, playstamp);
				__frame_release(buf);
				playobj->playbuf_numframe--;

			} else {
				return 0;
			}
			break;

		case PLAYMODE_FB:
			foreach_cam_ch(i)
				if (svr->netstamp [i] > 0) {
					if (baseline == 0)
						baseline = svr->netstamp [i];

					if (baseline < svr->netstamp [i])
						baseline = svr->netstamp [i];
				}
			end_foreach

			if (baseline <= playstamp) {
				__transframe (svr, buf, cam);
				svr->netstamp[cam] = 0;
				debugf("---ch=%d, %Ld\n", cam, playstamp);
				__frame_release(buf);
				playobj->playbuf_numframe--;

			} else {
				return 0;
			}
			break;

		default:
			return 0;
		}
	}
#else
	ret = __transframe (svr, buf, cam);
	if (ret < 0)
		return ret;

	__frame_release(buf);
	playobj->playbuf_numframe--;
#endif

	//debug ("VOD: CH%d nr frame in buffer = %d\n", cam, playobj->playbuf_numframe);

	// NOTE
	//	frame buffer may flood without count limitation, because we read 2 frames (odd/even) in case of D1.
	if (playobj->playbuf_numframe > 256) // We already have enough frames in buffer.
		return 0;

read_frame:

#define REPLY_EOF() \
({\
	char sndbuf [256];\
	char * tmp = NULL;\
	int msgsz;\
	tmp = sndbuf + sizeof (struct phdr);\
	setnetbuf (tmp, char, cam);\
	setnetbuf (tmp, char, 1);\
	msgsz = tmp - (char *) (sndbuf + sizeof (struct phdr));\
	reply2client (svr, svr->sock, sndbuf, REPLYID (PSENDSTREAM), RETEOFRAME, msgsz);\
})

	if (playobj->playbuf_numframe > MAX_VOD_FRAME_IN_LIST)
		return 0;

	switch(PLAYBACK_PLAYMODE(playobj)) {
		case PLAYMODE_PLAY:
			ret = playback_read_frame(playobj, NULL, 0);
			break;

		case PLAYMODE_FF:
			ret = playback_read_frame_ff(playobj, NULL, 0);
			break;

		case PLAYMODE_FB:
			ret = playback_read_frame_fb(playobj, NULL, 0);
			break;

		case PLAYMODE_STOP:
		default:
			/* Nothing to do */
			break;
	}

	if (ret == -ERR_EOFRAME) {
		if(vod_nextfile (svr, VOD (svr, cam).prevmode, cam) != 0) {
			_DBG_R("CH %d: END OF FRAME VOD TRANSFRAME\n", playobj->req.ch);
			VOD (svr, cam).cmd.playmode = PLAYMODE_STOP;
			return REPLY_EOF();
		}
		VOD(svr, cam).transhdr = 1;
		return 0;
	}

	buf = clist_entry (playobj->buf_head.prev, struct st_frame, iframe);
	svr->netstamp[cam] = playobj->creatime_sec *1000 +DATAUNIT_STAMP ((DATAUNIT *) buf->data_unit);
	return 0;
}
