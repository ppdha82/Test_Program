#!/usr/bin/env python3

import openpyxl
import os

xlsxFilename = "FOCUS_STRING.xlsx"
testFilename = "test.txt"

REMOVAL_WORD = [ "_PRC", "_FRE", "_GER", "_KOR", "_JPN", "_CHI", "_ENG"]
ENCODING = [ "BIG5-HKSCS", "ISO-8859-1", "ISO-8859-2", "EUC-KR", "EUC-JP", "EUC-CN", "UTF-8" ]

# Excel 파일 생성
book = openpyxl.Workbook()
sheet = book.active
sheet.title = 'Sheet1'

# Value 입력을 위한 column/row
column = 'A'
row = '2'

# debugging 용 파일 생성 빈칸 없이 html 파일을 txt 로 쓰기
testFile = open(testFilename, "w")

# htm 파일 테스트용 임시경로
cur_pwd = os.getcwd() + "/temp"
cur_pwd_list = os.listdir(cur_pwd)
print("cur_pwd_list = " + str(cur_pwd_list))
dir = cur_pwd

# postfix 삭제용 "_FRE"...
removalWord = ""

# key string 버퍼
# Excel 에 쓰기 전에 버퍼에 저장하면서 중복 및 특정 언어에만 있는 key 탐색
keyArray = []

# htm 파일 전체 탐색 loop
for htmFile in cur_pwd_list:
	next_column = chr(ord(column) + 1)
	print("htmFile = " + htmFile)
	charset = ""

	# htm 파일의 해당 국가의 설정(charset) 검색
	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			if "charset" in repr(data) and not "RES_COMMON_CHARSET" in repr(data):
				print("charset data = " + str(data))
				# 문자열 중 "charset="과 일치하는 문자열 찾기 (없다면 어떻게??)
				charsetPosition = str(data).find("charset=")
				print("position = " + str(charsetPosition) +"; string = " + str(data)[charsetPosition:])
				# 문자열 중 "\""을 구분자로 문자열 분리함
				charsetSplit = str(data)[charsetPosition:].split("\"")
				print("charsetSplit = " + str(charsetSplit))
				index = 0
				for string in charsetSplit:
					# 분리된 문자열 중에 "charset=" 을 포함하는 경우를 찾아서
					if "charset=" in string:
						# 분리된 문자열이 "charset="과 일치한다면 그 다음 문자열을 모두 대문자로 치환함
						if len(string) == len("charset="):
							charset = charsetSplit[index + 1].upper()
						# 분리된 문자열이 "charset="을 포함하되 일치하지 않는다면 "charset="을 제거함
						else:
							charset = string.replace("charset=", "", -1).upper()
						break
					index += 1
				print("charset = " + charset)
				break

	# postfix 삭제를 위해 charset를 Excel 에 쓰기
	idx = 0
	for key in ENCODING:
		if key == charset:
			removalWord = REMOVAL_WORD[idx]
			sheet[column + '1'] = REMOVAL_WORD[idx]
			print("removalWord = " + removalWord)
		idx += 1

	# COMMON_CHARSET 을 찾아 문서의 encoding 찾기
	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			foundIndex = str(data).find("COMMON_CHARSET")
			if foundIndex != -1:
				keyTmp = str(data).split("\t")
				key = keyTmp[0].replace("COMMON_CHARSET", "", -1)
				#print("foundIndex = " + str(foundIndex) + "; key = " + key)
				break

	# Excel 에 key/value 쓰기
	with open(dir + "/" + htmFile, "rb") as input:
		for data in input.readlines():
			needToAppend = 1
			#print("data = " + str(data))
			mid_data = data.decode(encoding=charset).rstrip()
			testFile.write(str(mid_data))
			if len(str(mid_data)) >= 2:
				testFile.write("\n")
			mid2_data = mid_data.split("\"")
			if(len(mid2_data) < 2):
				continue
			#print("mid2_data = " + str(mid2_data))

			mid3_data = mid2_data[0].split(" ")
			#print("mid3_data = " + str(mid3_data))
			if(len(mid3_data) < 2):
				continue
			mid4_data = mid3_data[1].replace("\t", "", -1)

			last_data = str(mid4_data).replace(removalWord, "", -1)
			print("last_data = " + last_data)
			# buffer size 보다 라인 수가 작을 경우 buffer size 증가
			if len(keyArray) < int(row):
				keyArray.append(last_data)
				print("Enter = " + last_data + "(" + str(len(keyArray) - 1) + ")")
			else:
				idx = 0
				while len(keyArray) > idx:
					if keyArray[idx] == last_data:
						print("Found same keyword idx = " + str(idx) + "(" + last_data + ")")
						needToAppend = 0
					idx += 1
			print("len(keyArray) = " + str(len(keyArray)))
			###
			#if needToAppend == 1:
			pos = str(column + row)
			sheet[pos] = last_data
			###
			next_pos = str(next_column) + str(row)
			sheet[next_pos] = mid2_data[1]
			print("mid2_data[1] = " + str(mid2_data[1]))
			row = str(int(row) + 1)
			#print("dec(data) = " + data.decode(encoding='big5-hkscs'))
	row = '2'
	column = chr(ord(column) + 2)



#book = openpyxl.load_workbook(xlsxFilename)
#sheet = book['Sheet2']

book.save(xlsxFilename)
testFile.close()
