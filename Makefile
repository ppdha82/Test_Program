# Author: ppdha82 <ppdha82@focushns.com>

TOP_DIR=$(PWD)
COMPILER_TYPE=C
PLATFORM=X86
#PLATFORM=ARM
TARGET=test_jansson
#TARGET=analysis_ai_metadata
#TARGET=dirent

FLAG=-D'__DEBUG_ON__'
CFLAG=-D'__DEBUG_ON__'

ifeq ($(COMPILER_TYPE), C)
SRC_DIR=c_source
COMPILER=gcc
FLAG+=-lpthread
EXT_NAME=c
endif
ifeq ($(COMPILER_TYPE), CPP)
SRC_DIR=cpp_source
COMPILER=g++
FLAG+=-lpthread
EXT_NAME=cpp
endif
MAIN_FILE=$(TOP_DIR)/$(SRC_DIR)/$(TARGET).$(EXT_NAME)

TARGET_DIR=$(TOP_DIR)
TARGET_LIB_DIR=$(TOP_DIR)

INC_DIR=-I$(TOP_DIR)/include

fopen:
	@echo build $@
	SRC_DIR=c_source/
	$(COMPILER) -o $(SRC_DIR)/$@ $(SRC_DIR)/$@.c $(INC_DIR) $(CFLAG)
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

