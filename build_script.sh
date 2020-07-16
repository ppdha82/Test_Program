
if [[ $2 == "" ]];then
	echo "too few argumet"
	exit 1
fi

LIB_PNG=
INC_PNG=
if [[ $1 == "libpng" ]]; then
	PNG_PATH=../319_libpng_focus
	echo "support libpng"
	LIB_PNG="-L$PNG_PATH/output/lib -lpng -L$PNG_PATH/extlib -lz -lm"
	INC_PNG="-I$PNG_PATH -I$PNG_PATH/extinc"
fi

if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
CROSS_COMPILER=arm-hisiv500-linux-
fi
CC=${CROSS_COMPILER}gcc

TARGET=$1
echo "TARGET = "$TARGET
SRC_FILE=$TARGET.c
echo "SRC_FILE = "$SRC_FILE

if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
#TARGET_DIR=../008_ipm-hi/app/_output/hi3516cv300/edvr/
#TARGET_DIR=../011_ipm-hi/app/_output/hk3516/edvr/
TARGET_DIR=../012_ipm-hi/app/_output/hi3516cv300/edvr/

rm -f $TARGET
$CC -o $TARGET $SRC_FILE $LIB_PNG $INC_PNG && cp $TARGET $TARGET_DIR
echo "Copy files to Target("$TARGET_DIR")"
else
$CC -o $TARGET $SRC_FILE
fi
