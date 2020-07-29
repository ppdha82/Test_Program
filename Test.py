#!/usr/bin/env python3
import csv
import os

OEM_PATH = "./define/model_spec/"
OEM_WHOLE_PATH_NAME = ""

def makeDirectory():
	try:
		print("RUN getOemName1")
		OEM_NAME = a_list[1][0]
		print("OEM_NAME = ", OEM_NAME)
		print("RUN getOemName2")
		global OEM_WHOLE_PATH_NAME
		OEM_WHOLE_PATH_NAME = OEM_PATH + OEM_NAME
		print("OEM_WHOLE_PATH_NAME = ", OEM_WHOLE_PATH_NAME)
		if not(os.path.isdir(OEM_WHOLE_PATH_NAME)):
			os.makedirs(OEM_WHOLE_PATH_NAME)
	except OSError as e:
		if e.error != errno.EEXIST:
			print("Failed to create directory")
			raise

def gen_file(row):
	print("OEM_WHOLE_PATH_NAME = ", OEM_WHOLE_PATH_NAME)
	sValue = OEM_WHOLE_PATH_NAME + str("/") + a_list[1][1]
	print("sValue = ", sValue)
	return open(sValue, 'w')

csvFilename = "./FOCUS_DEFINE_MODEL.csv"
a_list = []

workfile = open(csvFilename, 'r', encoding='utf-8')
rdCsv = csv.reader(workfile)

for line in rdCsv:
	a_list.append(line)
	print("line = ", line)

print("a_list[0][0] = ", a_list[0][0], "; a_list[1][1] = ", a_list[1][1])
workfile.close()

index = 1

print("RUN makeDirectory1")
makeDirectory()
print("RUN makeDirectory2")
print("RUN gen_file1")
ini_file = gen_file(index)
print("RUN gen_file2")

''' ARCH, SENSOR_TYPE, IPDEVICE_TYPE, SUB_MODEL, SENSOR, CDS_MODE, IR_PWM, SUPPORT_H265, SUPPORT_MFZ, SUPPORT_PIRIS, ALPUC, USE_LPR, DDNS, DTON, NTOD '''
columnIndex = 0
keyLen = len(a_list[0]) - 2
print("keyLen = ", keyLen)
while columnIndex < keyLen:
	valueIndex = columnIndex + 2
	if(ini_file.writable()):
		data = a_list[0][valueIndex] + ' = ' + a_list[1][valueIndex] + '\n'
		ini_file.write(data)
	print("a_list[", columnIndex, "] = ", a_list[1][valueIndex])
	columnIndex += 1