
if [[ $2 == "" ]];then
	echo "too few argumet"
	exit 1
fi

LIB_PNG=
INC_PNG=
LIB_JANSSON=
INC_JANSSON=

TARGET_BASE=../015_ipm-hi/app
EXT_LIB_PATH=$TARGET_BASE/extlib/lib/arm-hisiv500-linux
EXT_INC_PATH=$TARGET_BASE/extlib/include

if [[ $1 == "libpng" ]]; then
	PNG_PATH=../319_libpng_focus
	echo "support libpng"
	LIB_PNG="-L$PNG_PATH/output/lib -lpng -L$PNG_PATH/extlib -lz -lm"
	INC_PNG="-I$PNG_PATH -I$PNG_PATH/extinc"
fi

if [[ $1 == "jansson_test" ]]; then
	LIB_JANSSON="-L$EXT_LIB_PATH -ljansson -lm"
	INC_JANSSON="-I$EXT_INC_PATH"
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
#TARGET_DIR=$TARGET_BASE/_output/hi3516cv300/edvr/
#TARGET_DIR=$TARGET_BASE/_output/hk3516/edvr/
TARGET_DIR=$TARGET_BASE/_output/hi3516cv300/edvr/
LIB_FLAG=$LIB_PNG
LIB_FLAG+=$LIB_JANSSON
INC_FLAG=$INC_PNG
INC_FLAG+=$INC_JANSSON

rm -f $TARGET
$CC -o $TARGET $SRC_FILE $INC_FLAG $LIB_FLAG && cp $TARGET $TARGET_DIR
echo "Copy files to Target("$TARGET_DIR")"
else
$CC -o $TARGET $SRC_FILE
fi
