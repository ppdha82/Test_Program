#!/usr/bin/env python3
'''
from openpyxl import load_workbook
load_wb = load_workbook("./FOCUS_MODEL_DEFINE.xlsx", data_only=True)
load_ws = load_wb['Sheet1']


print(load_ws['A1'].value)

print(load_ws.cell(1, 2).value)
'''
import openpyxl

def gen_file(column):
    row = 1
    key = 0
    while key is not None:
        key = sheet.cell(row, column).value
        print("key = ", key)
        if key == "MODEL":
            sValue = sheet.cell(row, column + 1).value
            print("sValue = ", sValue)
            return open(sValue, 'w')
        row += 1
    return None

filename = "./FOCUS_DEFINE_MODEL.xlsx"
book = openpyxl.load_workbook(filename)
sheet = book['Sheet1']

sKey = " "
section = 1
index = 1

print("RUN gen_file1")
ini_file = gen_file(index)
print("RUN gen_file2")

while sKey is not None:
    sKey = sheet.cell(section, index).value
    value = sheet.cell(section, index+1).value
    if sKey is not None and ini_file is not None :
        data = str(sKey) + '=' + str(value) + '\n'
        if(ini_file.writable()):
            ini_file.write(data)
    print("sheet.cell([row = ", section, ").value = ", sKey, ":", value)
    section += 1
