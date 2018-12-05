#read_and_open.py
import os
import sys

filter_key="SUPPORT_MFZ"
filter_result="MFZ_list"

rm_command="rm "
ls_command="ls -al "
rm_result=rm_command + filter_result
ls_result=ls_command + filter_result
os.system(rm_result)
os.system(ls_result)

filter_command="grep -nr " + filter_key + " * | cut -d \":\" -f1 > " + filter_result
print(filter_command)
os.system(filter_command)

f = open (filter_result, 'r')
while True:
    line = f.readline()
    if not line : break
    command = 'vi ' + line
    print(command)
    os.system(command)
f.close()
