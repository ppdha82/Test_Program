#!/usr/bin/env python3
import csv
import os

OEM_PATH = "./_define/model_spec/"
OEM_WHOLE_PATH_NAME = ""
a_list = []
model_count = 0

def makeDirectory(row):
	try:
		print("RUN getOemName1")
		OEM_NAME = a_list[row][0]
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
	sValue = OEM_WHOLE_PATH_NAME + str("/") + a_list[row][1]
	print("sValue = ", sValue)
	return open(sValue, 'w')

def main():
	csvFilename = "./FOCUS_DEFINE_MODEL_TEST.csv"

	workfile = open(csvFilename, 'r', encoding='utf-8')
	rdCsv = csv.reader(workfile)

	for line in rdCsv:
		global model_count
		model_count += 1
		a_list.append(line)
		print("line = ", line)

	print("a_list[0][0] = ", a_list[0][0], "; a_list[1][1] = ", a_list[1][1])
	workfile.close()

	index = 1

	while index < model_count:
		print("RUN makeDirectory1")
		makeDirectory(index)
		print("RUN makeDirectory2")
		print("RUN gen_file1(" + str(index) + ")")
		ini_file = gen_file(index)
		print("RUN gen_file2")

		''' ARCH, SENSOR_TYPE, IPDEVICE_TYPE, SUB_MODEL, SENSOR, CDS_MODE, IR_PWM, SUPPORT_H265, SUPPORT_MFZ, SUPPORT_PIRIS, ALPUC, USE_LPR, DDNS, DTON, NTOD '''
		columnIndex = 0
		keyLen = len(a_list[index - 1]) - 2
		print("keyLen = ", keyLen)
		while columnIndex < keyLen:
			valueIndex = columnIndex + 2
			if(ini_file.writable()):
				data = a_list[index - 1][valueIndex] + '=' + a_list[1][valueIndex] + '\n'
				ini_file.write(data)
			print("a_list[", columnIndex, "] = ", a_list[index][valueIndex])
			columnIndex += 1
		index += 1

main()