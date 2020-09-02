#!/usr/bin/env python3

import openpyxl
import os

xlsxFilename = "FOCUS_STRING.xlsx"
testFilename = "test.txt"
htmFilename = "res_chinese_PRC.htm"

book = openpyxl.Workbook()
sheet = book.active
sheet.title = 'Sheet1'
column = 'A'
row = '1'
next_column = chr(ord(column) + 1)
testFile = open(testFilename, "w")

with open("temp/" + htmFilename, "rb") as input:
    for data in input.readlines():
        print("data = " + str(data))
        pos = str(column + row)
        mid_data = data.decode(encoding='big5-hkscs').rstrip()
        testFile.write(str(mid_data))
        if len(str(mid_data)) >= 2:
            testFile.write("\n")
        mid2_data = mid_data.split("\"")
        if(len(mid2_data) < 2):
            continue
        print("mid2_data = " + str(mid2_data))

        mid3_data = mid2_data[0].split(" ")
        print("mid3_data = " + str(mid3_data))
        if(len(mid3_data) < 2):
            continue
        mid4_data = mid3_data[1].replace("\t", "", -1)
        last_data = mid4_data.replace("_PRC", "", -1)
        print("last_data = " + str(last_data))
        sheet[pos] = last_data
        next_pos = str(next_column) + str(row)
        sheet[next_pos] = mid2_data[1]
        row = str(int(row) + 1)
        #print("dec(data) = " + data.decode(encoding='big5-hkscs'))

#book = openpyxl.load_workbook(xlsxFilename)
#sheet = book['Sheet2']

book.save(xlsxFilename)
testFile.close()