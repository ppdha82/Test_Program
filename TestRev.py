#!/usr/bin/env python3

import os
# ini 파일 read 하기 위해 ConfigParser 를 사용하려 했으나,
# model ini 파일에 section 구분을 하지 않아 read 안되고 section 없는 ini 파일을
# 지원하지 않는 것을 확인함
import csv

cur_pwd = ""
dir_list = []
sub_dir_list = []

def move_to_base_dir():
	''' change current dir to "define" '''
	global cur_pwd
	cur_pwd = os.getcwd()
	#print(cur_pwd)
	os.chdir("./define")
	#print("current dir = ", os.getcwd())

def move_to_dir(target):
	pwd = print(os.getcwd())
	#print("pwd+target = ", pwd + target)
	os.chdir(pwd + target)
	#print(os.getcwd())

def move_to_main_dir():
	#print(os.getcwd())
	os.chdir("..")
	#print("current dir = ", os.getcwd())

def get_list_in_dir():
	''' find dir and file in sub_dir '''
	global cur_pwd
	cur_pwd = os.getcwd()
	cur_pwd_list = os.listdir(cur_pwd)
	#print("cur_pwd_list = ", cur_pwd_list, "; type = ", type(cur_pwd_list))
	return cur_pwd_list

def get_list_in_target_dir(path, target):
	''' find dir and file in sub_dir '''
	cur_pwd_list = os.listdir(path + "/" + target)
	#print("cur_pwd_list = ", cur_pwd_list, "; type = ", type(cur_pwd_list))
	return cur_pwd_list

def seperate_file_dir(cur_pwd_list):
	global dir_list
	global cur_pwd
	for x in cur_pwd_list:
		if os.path.isfile(x) == True:
			result = "file"
		elif os.path.isdir(x) == True:
			result = "directory"
			dir_list = cur_pwd + "/" + x
		else:
			result = "unknown"
		#print(x, " is ", result)

def run():
	global sub_dir_list

	csvFilename = "FOCUS_DEFINE_MODEL_TEST.csv"
	workfile = open(os.getcwd() + "/" + csvFilename, 'w', encoding='utf-8', newline='')
	move_to_base_dir()

	sub_dir_list = get_list_in_dir()
	#print("sub_dir_list = ", sub_dir_list)
	seperate_file_dir(sub_dir_list)

	''' deal with file '''
	if len(dir_list) <= 0:
		print("Exit Program")
		return False

#	csvFilename = "./FOCUS_DEFINE_MODEL_TEST.csv"
#	workfile = open(csvFilename, 'w', encoding='utf-8')
#	workfile.close()

	#print("list = ", dir_list)
	sub_dir_list = os.listdir(dir_list)
	'''
	print("sub_dir_list =", sub_dir_list)
	index = 1
	for a in sub_dir_list:
		print("sub_dir_list[", index, "] = ", a)
		index += 1
	'''
	dev_index = 0
	index = 1
	data = sub_dir_list.pop(0)
	csv_index = 1
	wr_csv = csv.writer(workfile)

	# initialize key about OEM & MODEL
	header_list = ["OEM", "MODEL"]
	value_list = [[""], [""],]
	while len(sub_dir_list) > 0:
		print("data[" + str(index) + "] = ", data)
		ini_file_list = get_list_in_target_dir(dir_list, data)
		path = dir_list + "/" + data

		print("[check] path = ", path)
		print("[check] ini_file_list = ", ini_file_list)
		if len(ini_file_list) > 0:
			ini_index = 1
			for ini_data in ini_file_list:
				found_value_index = 0
				for header in header_list:
					if "OEM" == header:
						print("header (" + header + ") is found(key = OEM, (" + str(dev_index) + ", " + str(found_value_index) + "))")
						print("len(value_list) = " + str(len(value_list)) + "; found_value_index = " + str(found_value_index))
						if len(value_list) <= dev_index:
							print("add list to value_list [OEM]")
							value_list.append([""])
						# add OEM value
						value_list[dev_index][found_value_index] = data
						break
					found_value_index += 1

				found_value_index = 0
				for header in header_list:
					if "MODEL" == header:
						print("header (" + header + ") is found(key = MODEL, (" + str(dev_index) + ", " + str(found_value_index) + "))")
						print("len(value_list) = " + str(len(value_list)) + "; found_value_index = " + str(found_value_index))
						if len(value_list[dev_index]) <= found_value_index:
							print("add list to value_list [MODEL]")
							value_list[dev_index].append("")
						# add MODEL value
						value_list[dev_index][found_value_index] = ini_data
						break
					found_value_index += 1
				print("[value] ini_file_list[" + str(ini_index) + "] = " + ini_data)
				sub_path_file = path + "/" + ini_data
				print("sub_path_file =", sub_path_file)
				read_file = open(sub_path_file, 'r')
				print("read_file  >>>>>>")
				read_all_line = read_file.read().splitlines()
				print(read_all_line)

				for read_line in read_all_line:
					print("read_line >>>>> " + read_line)
					if len(read_line) <= 0:
						break
					slices_line = read_line.split('=')
					slice_key = slices_line[0]
					slice_value = slices_line[1]
					if not slice_key in header_list:
						print("add " + slice_key + " in header_list")
						header_list.append(slice_key)
					found_index = 0
					for header in header_list:
						if slice_key == header:
							while len(value_list[dev_index]) <= found_index:
								value_list[dev_index].append("")
							print("header_list = " + str(header_list))
							print("header (" + header + ") is found(slice_key = " + slice_key + ", " + str(found_index) + ")")
							print("len(value_list[" + str(dev_index) + "]) = " + str(len(value_list[dev_index])) + "; dev_index = " + str(dev_index), "found_index = " + str(found_index))
							value_list[dev_index][found_index] = slice_value
							print("value_list[" + str(dev_index) + "] = " + str(value_list[dev_index]))
							break
						found_index += 1
					csv_index += 1
				ini_index += 1
				dev_index += 1
		data = sub_dir_list.pop(0)
		index += 1

	wr_csv.writerow(header_list)
	print_index = 0
	while len(value_list) > print_index:
		wr_csv.writerow(value_list[print_index])
		print_index += 1
	workfile.close()
	print("header_list = ", header_list)
	print("value_list = ", value_list)

run()
