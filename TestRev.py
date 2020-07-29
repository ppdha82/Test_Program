#!/usr/bin/env python3

import os

cur_pwd = ""
dir_list = []
sub_dir_list = []

def move_to_base_dir():
	''' change current dir to "define" '''
	print(os.getcwd())
	os.chdir("./define")
	print("current dir = ", os.getcwd())

def move_to_dir(target):
	pwd = print(os.getcwd())
	print("pwd+target = ", pwd + target)
	os.chdir(pwd + target)
	print(os.getcwd())

def move_to_main_dir():
	print(os.getcwd())
	os.chdir("..")
	print("current dir = ", os.getcwd())

def get_list_in_dir():
	''' find dir and file in sub_dir '''
	global cur_pwd
	cur_pwd = os.getcwd()
	cur_pwd_list = os.listdir(cur_pwd)
	print("cur_pwd_list = ", cur_pwd_list, "; type = ", type(cur_pwd_list))
	return cur_pwd_list

def get_list_in_target_dir(path, target):
	''' find dir and file in sub_dir '''
	cur_pwd_list = os.listdir(path + "/" + target)
	print("cur_pwd_list = ", cur_pwd_list, "; type = ", type(cur_pwd_list))
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
		print(x, " is ", result)

def run():
	global sub_dir_list
	move_to_base_dir()
	sub_dir_list = get_list_in_dir()
	print("sub_dir_list = ", sub_dir_list)
	seperate_file_dir(sub_dir_list)

	''' deal with file '''
	if len(dir_list) <= 0:
		print("Exit Program")
		return False

	print("list = ", dir_list)
	sub_dir_list = os.listdir(dir_list)

	print("sub_dir_list =", sub_dir_list)
	index = 1
	for a in sub_dir_list:
		print("sub_dir_list[", index, "] = ", a)
		index += 1

	index = 1
	data = sub_dir_list.pop(0)
	while len(sub_dir_list) > 0:
		print("data[", index, "] = ", data)
		ini_file_list = get_list_in_target_dir(dir_list, data)
		print("[check] ini_file_list = ", ini_file_list)
		if len(ini_file_list) > 0:
			ini_index = 0
			for ini_data in ini_file_list:
				print("[value] ini_file_list[", ini_index, "] = ", ini_data)
				ini_index += 1
		data = sub_dir_list.pop(0)
		index += 1

run()
