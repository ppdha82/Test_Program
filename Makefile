# Author: ppdha82 <ppdha82@focushns.com>

TOP_DIR=$(PWD)
COMPILER_TYPE=C
PLATFORM=X86
#PLATFORM=ARM
TARGET=test_jansson
#TARGET=analysis_ai_metadata
#TARGET=dirent

ifeq ($(COMPILER_TYPE), C)
ifeq ($(PLATFORM), X86)
COMPILER=gcc
else
COMPILER=arm-hisiv500-linux-gcc
endif	# X86
FLAG=-D'__DEBUG_ON__'
FLAG+=-lpthread
ifeq ($(PLATFORM), X86)
FLAG+=-ljansson -Llib
else
FLAG+=-ljansson -Llib/arm -lm -DARM_TARGET
endif	# X86
SRC_DIR=c_source
EXT_NAME=c
else
ifeq ($(COMPILER_TYPE), CPP)
COMPILER=g++
FLAG=-D'__DEBUG_ON__'
FLAG+=-lpthread
SRC_DIR=cpp_source
EXT_NAME=cpp
endif
endif
MAIN_FILE=$(TOP_DIR)/$(SRC_DIR)/$(TARGET).$(EXT_NAME)

TARGET_DIR=$(TOP_DIR)
TARGET_LIB_DIR=$(TOP_DIR)

INC_DIR=-I$(TOP_DIR)/include

fopen:
	@echo build $@
	SRC_DIR=c_source/
	$(COMPILER) -o $(SRC_DIR)/$@ $(SRC_DIR)/$@.c $(INC_DIR) $(FLAG)
	ls -l $(SRC_DIR)/$@
	@echo finish $@

all: $(TARGET)
	@echo all $(TARGET) $(MAIN_FILE) $(FLAG) $(INC_DIR)
	@echo "finish $@"

install:
	@echo $@
	@echo "Copy files to $(TARGET_DIR)"
	@cp $(TARGET) $(TARGET_DIR)
	@cp -a lib$(TARGET).so $(TARGET_LIB_DIR)
	@echo Complete copying files

$(TARGET):
	@echo linking... $(MAIN_FILE)
	$(COMPILER) -o $(TARGET) $(MAIN_FILE) $(FLAG) $(INC_DIR)
	chmod 755 $@
	@echo =========== build end ===========

clean:
	@echo $@
	@echo Removing: $(TARGET) lib$(2).so
	@rm -f $(TARGET) lib$(TARGET).so

