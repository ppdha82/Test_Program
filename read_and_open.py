#read_and_open.py
import os
import sys

filter_key="SUPPORT_MFZ"
filter_result="MFZ_list"
filter_inverse_key="SUPPORT_MFZ=0"

def init():
    # remove old result file
    rm_command="rm "
    rm_result=rm_command + filter_result
    os.system(rm_result)

    # check whether is removed old result file
    ls_command="ls -al "
    ls_result=ls_command + filter_result
    return os.system(ls_result)

def make():
    filter_command="grep -nr " + filter_key + " * | grep -v " + filter_inverse_key + " | cut -d \":\" -f1 > " + filter_result
    print(filter_command)
    os.system(filter_command)

def run():
    f = open (filter_result, 'r')
    while True:
        line = f.readline()
        if not line : break
        command = 'vi ' + line
        print(command)
        os.system(command)
    f.close()    

max_arg = 1
cur_arg = len(sys.argv) - 1
if cur_arg > max_arg:
    log = "There is too many argument(current = " + str(cur_arg) + "; max = " + str(max_arg) + ")"
    print(log)
    exit()

for i in range (1, cur_arg + 1) :
    print(sys.argv[i])

result=0
if sys.argv[1] == "init":
    result = init()
    if result == 0:
        print("Failed to initialize")
    exit()

if sys.argv[1] == "make":
    make()
    exit()

if sys.argv[1] == "run":
    result = run()
    exit()

if sys.argv[1] == "run_all":
    result = init()
    make()
    run()

exit()

