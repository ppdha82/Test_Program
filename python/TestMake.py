#!/usr/bin/env python3

import os
import csv

cur_pwd = os.getcwd()
print("cur_pwd = " + cur_pwd)
target_dir = "define/model_spec/OEM_FOCUS"
os.chdir(cur_pwd + "/" + target_dir)
sub_cur_pwd = os.getcwd()
print("cur_pwd = " + str(sub_cur_pwd))

target_file = sub_cur_pwd + "/" + "IPC-2061"
read_file = open(target_file, 'r')
print("read_file =>>>>>>>")
print(read_file.read())

read_file.seek(0)
for line in read_file.readlines():
    print("line =>> " + line)


csvFilename = "FOCUS_DEFINE_MODEL_TEST.csv"
workfile = open(cur_pwd + "/" + csvFilename, 'w', encoding='utf-8')
wr_csv = csv.writer(workfile)
csv_index = 1
wr_csv.writerow("merong" + str(csv_index))
csv_index += 1
wr_csv.writerow("merong" + str(csv_index))
workfile.close()
