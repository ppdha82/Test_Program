import sys

# 아래 정의되어있는 파일리스트에 문자열을 추가해준다
# [name] 파일에 [encoding] 인코딩으로 RES_ID + [code] 를 정의
files = [ {"code": "ARABIC",    "name": "res_arabic.htm",       "encoding": "arabic"}
        , {"code": "BG5",       "name": "res_chn_trad.htm",     "encoding": "BIG5-HKSCS"}
        , {"code": "ENG",       "name": "res_eng.htm",          "encoding": "euc-kr"}
        , {"code": "FRA",       "name": "res_fra.htm",          "encoding": "Windows-1252"}
        , {"code": "GER",       "name": "res_ger.htm",          "encoding": "Windows-1252"}
        , {"code": "JPN",       "name": "res_jpn.htm",          "encoding": "euc-jp"}
        , {"code": "KOR",       "name": "res_kor.htm",          "encoding": "euc-kr"}
        , {"code": "NED",       "name": "res_ned.htm",          "encoding": "Windows-1252"}
        , {"code": "NORWEGIAN", "name": "res_norwegian.htm",    "encoding": "Windows-1252"}
        , {"code": "POR",       "name": "res_por.htm",          "encoding": "Windows-1252"}
        , {"code": "SWEDISH",   "name": "res_swedish.htm",      "encoding": "Windows-1252"}]

if len(sys.argv) >= 3:
    for info in files:
        defineString = "%-50s"%(sys.argv[1] + "_" + info["code"])
        resString = "\"" + sys.argv[2] + "\""
        text = ("#define " + defineString + " " + resString + "\n")
        if len(sys.argv) >= 4:
            if sys.argv[3] == "1": #debug mode
                print("%-20s"%info["name"], text, end="")

        f = open(info["name"], "ab")
        data = text.encode(info["encoding"])
        f.write(data)
        f.close()
    print("Done!")
else:
    print("Invalid format")
    print("format: python3 appendString.py [RES_ID] [RES_STRING] (DEBUG)")
    print("example: python3 appendString.py RES_HELLO_WORLD \"HELLO WORLD\"")