
if [[ $1 == "" ]];then
	echo "too few argumet"
	exit 1
fi

if [[ $2 == "" ]];then
	echo "too few argumet"
	exit 1
fi

LIB_PNG=
INC_PNG=
LIB_JANSSON=
INC_JANSSON=
LIB_SSL=
INC_SSL=

TARGET_BASE=../0001_ipm-hi/app
EXT_LIB_PATH=$TARGET_BASE/extlib/lib/arm-hisiv500-linux
EXT_INC_PATH=$TARGET_BASE/extlib/include

if [[ $1 == "libpng" ]]; then
	PNG_PATH=../319_libpng_focus
	echo "support libpng"
if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
	LIB_PNG="-L$PNG_PATH/output/lib -L$PNG_PATH/extlib"
	INC_PNG="-I$PNG_PATH -I$PNG_PATH/extinc"
fi
	LIB_PNG+=" -lz -lm -lpng"
fi

if [[ $1 == "jansson_test" ]]; then
if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
	LIB_JANSSON="-L$EXT_LIB_PATH"
	INC_JANSSON="-I$EXT_INC_PATH"
fi
	LIB_JANSSON+=" -ljansson -lm"
fi

if [[ $1 == "setup_enc_dec" ]]; then
if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
	LIB_SSL="-L$EXT_LIB_PATH"
	INC_SSL="-I$EXT_INC_PATH"
else
	LIB_SSL="-L/usr/x86_64-linux-gnu"
	INC_SSL="-I/usr/include"
fi
	LIB_SSL+=" -lssl -lcrypto"
fi

if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
CROSS_COMPILER=arm-hisiv500-linux-
fi
CC=${CROSS_COMPILER}gcc

TARGET=$1
echo "TARGET = "$TARGET
SRC_FILE=$TARGET.c
echo "SRC_FILE = "$SRC_FILE

LIB_FLAG=$LIB_PNG
LIB_FLAG+=$LIB_JANSSON
LIB_FLAG+=$LIB_SSL
echo "LIB_FLAG = "$LIB_FLAG

INC_FLAG=$INC_PNG
INC_FLAG+=$INC_JANSSON
INC_FLAG+=$INC_SSL
echo "INC_FLAG = "$INC_FLAG

rm -f $TARGET
$CC -o $TARGET $SRC_FILE $INC_FLAG $LIB_FLAG -g

if [[ $2 == "FOCUS" || $2 == "focus" ]]; then
#TARGET_DIR=$TARGET_BASE/_output/hi3516cv300/edvr/
TARGET_DIR=$TARGET_BASE/_output/hk3516/edvr/
#TARGET_DIR=$TARGET_BASE/_output/hi3516cv300/edvr/

cp $TARGET $TARGET_DIR
echo "Copy files to Target("$TARGET_DIR")"
fi

