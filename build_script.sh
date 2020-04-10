
CC=arm-hisiv500-linux-gcc
TARGET=$1
SRC_FILE=$TARGET.c
TARGET_DIR=../008_ipm-hi/app/_output/hi3516cv300/edvr/

$CC -o $TARGET $SRC_FILE && cp $TARGET $TARGET_DIR
