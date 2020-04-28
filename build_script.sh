
if [[ $1 == "FOCUS" || $1 == "focus" ]]; then
CROSS_COMPILER=arm-hisiv500-linux-
fi
CC=${CROSS_COMPILER}gcc

TARGET=$1
echo "TARGET = "$TARGET
SRC_FILE=$TARGET.c
echo "SRC_FILE = "$SRC_FILE

if [[ $1 == "FOCUS" || $1 == "focus" ]]; then
TARGET_DIR=../007_ipm-hi/app/_output/hi3516cv300/edvr/

$CC -o $TARGET $SRC_FILE && cp $TARGET $TARGET_DIR
echo "Copy files to Target("$TARGET_DIR")"
else
$CC -o $TARGET $SRC_FILE
fi
