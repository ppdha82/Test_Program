#!/bin/sh

watch -n 1 "ls -l > result.txt" &
sleep 7
killall watch
