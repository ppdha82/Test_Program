#!/usr/bin/env python
'''
from openpyxl import load_workbook
load_wb = load_workbook("./FOCUS_MODEL_DEFINE.xlsx", data_only=True)
load_ws = load_wb['Sheet1']


print(load_ws['A1'].value)

print(load_ws.cell(1, 2).value)
'''
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

while key is not None:
    key = sheet.cell(section, index).value;
    value = sheet.cell(section, index+1).value;
    print("sheet.cell([row = ", section, ").value = ", key, ":", value)
    section += 1

