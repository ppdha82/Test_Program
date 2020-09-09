#!/usr/bin/env python3

import openpyxl
import os

xlsxFilename = "FOCUS_STRING.xlsx"
testFilename = "test.txt"

REMOVAL_WORD = [ "_PRC", "_FRE", "_GER", "_KOR", "_JPN", "_CHI", "_ENG"]
ENCODING = [ "BIG5-HKSCS", "ISO-8859-1", "ISO-8859-2", "EUC-KR", "EUC-JP", "EUC-CN", "UTF-8" ]
book = openpyxl.Workbook()
sheet = book.active
sheet.title = 'Sheet1'
column = 'A'
row = '1'
testFile = open(testFilename, "w")

cur_pwd = os.getcwd() + "/temp"
cur_pwd_list = os.listdir(cur_pwd)
print("cur_pwd_list = " + str(cur_pwd_list))
dir = cur_pwd
removalWord = ""

for htmFile in cur_pwd_list:
	next_column = chr(ord(column) + 1)
	print("htmFile = " + htmFile)
	charset = ""
	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			if "charset" in repr(data) and not "RES_COMMON_CHARSET" in repr(data):
				print("charset data = " + str(data))
				charsetPosition = str(data).find("charset=")
				print("position = " + str(charsetPosition) +"; string = " + str(data)[charsetPosition:])
				charsetSplit = str(data)[charsetPosition:].split("\"")
				print("charsetSplit = " + str(charsetSplit))
				index = 0
				for string in charsetSplit:
					if "charset=" in string:
						if len(string) == len("charset="):
							charset = charsetSplit[index + 1]
						else:
							charset = string.replace("charset=", "", -1)
						break
					index += 1
				print("charset = " + charset)
				break

	idx = 0
	for key in ENCODING:
		if key == charset:
			removalWord = REMOVAL_WORD[idx]
			print("removalWord = " + removalWord)
		idx += 1

	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			foundIndex = str(data).find("COMMON_CHARSET")
			if foundIndex != -1:
				keyTmp = str(data).split("\t")
				key = keyTmp[0].replace("COMMON_CHARSET", "", -1)
				#print("foundIndex = " + str(foundIndex) + "; key = " + key)
				break


	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			print("data = " + str(data))
			pos = str(column + row)
			mid_data = data.decode(encoding=charset).rstrip()
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
			last_data = str(mid4_data).replace(removalWord, "", -1)
			print("last_data = " + last_data)
			sheet[pos] = last_data
			next_pos = str(next_column) + str(row)
			sheet[next_pos] = mid2_data[1]
			print("mid2_data[1] = " + str(mid2_data[1]))
			row = str(int(row) + 1)
			#print("dec(data) = " + data.decode(encoding='big5-hkscs'))
	row = '1'
	column = chr(ord(column) + 2)



#book = openpyxl.load_workbook(xlsxFilename)
#sheet = book['Sheet2']

book.save(xlsxFilename)
testFile.close()
