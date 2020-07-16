#!/usr/bin/env python

import openpyxl

filename = "./FOCUS_DEFINE_MODEL.xlsx"
book = openpyxl.load_workbook(filename)
sheet = book['Sheet1']

key = "x"
section = 1
index = 1

print("type(key) = ", type(key))

if len(key) != 0:
    print("key has space")
else:
    print("key is null")

'''while True:'''
while key is not None:
    key = sheet.cell(section, index).value;
    value = sheet.cell(section, index+1).value;
    print("sheet.cell([row = ", section, ").value = ", key, ":", value)
    section += 1
    '''if section > 5:
        break'''

