
import requests
import time

while True:

  DYNLINK = "http://www.dynlink.net"

  GET_SVR_TIME = "/dynlink/get_svr_time.aspx"

  TARGET="test_domain_name"

  req = requests

  res = req.get(DYNLINK)

  print(res.text)

  res = req.get(DYNLINK + GET_SVR_TIME)

  print(res.text)

  e = res.text.find("#]")
  myIP = res.text[2:e]

  print(myIP)

  times = res.text.find("[$") + 2;

  svrtime = res.text[times:times+14]

  y = res.text[times:times+4]
  times += 4
  m = res.text[times:times+2]
  times += 2
  d = res.text[times:times+2]
  times += 2

  h = res.text[times:times+2]
  times += 2
  min = res.text[times:times+2]
  times += 2
  sec = res.text[times:times+2]

  print(y, m, d, h, min, sec)

  hash = int(y) + int(m) + int(d) + int(h) * int(min) * int(sec)
  data = "%sTimeCheck%d"%(svrtime, hash)
  import base64

  data = data.encode("utf-8")
  b64data = base64.b64encode(data)
  b64data = str(b64data)[2:].replace("'", "")

  requrl = "http://www.dynlink.net/dynlink/chk_domain_without_port.aspx?key=%s&clientip=%s&mac=b8:27:eb:d0:68:3f&dom=%s&usr=&pwd=&update=1"%(b64data, myIP, TARGET)
  print(requrl)

  res = req.get(requrl)

  print(res.text)

  time.sleep(600)
