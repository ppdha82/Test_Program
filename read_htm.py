#!/usr/bin/env python3

with open("temp/res_chinese_PRC.htm", "rb") as input:
    for data in input.readlines():
        print("data = " + str(data))
        #print("dec(data) = " + data.decode(encoding='big5-hkscs'))

