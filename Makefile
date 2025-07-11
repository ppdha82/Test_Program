# Author: ppdha82 <ppdha82@focushns.com>

TOP_DIR=$(PWD)
# COMPILER_TYPE=C
COMPILER_TYPE=CPP
PLATFORM=X86
#PLATFORM=ARM
# TARGET=exam_cstdio
#TARGET=analysis_ai_metadata
TARGET=memoryManager
BAEKJOON_NO=5597

FLAG=-D'__DEBUG_ON__'
CFLAG=-D'__DEBUG_ON__'
CPP_FLAG=-D'__DEBUG_ON__'
# CPP_STRING_FLAG=-std=c++0x
CPP_STRING_FLAG=--std=c++11
CPP_FLAG+=$(CPP_STRING_FLAG)
INC_DIR=-I$(TOP_DIR)/include

ifeq ($(COMPILER_TYPE), C)
SRC_DIR=c_source
COMPILER=ccdv gcc
EXT_NAME=c
FLAG=$(CFLAG)
endif
ifeq ($(COMPILER_TYPE), CPP)
SRC_DIR=cpp_source
COMPILER=ccdv g++
EXT_NAME=cpp
FLAG=$(CPP_FLAG)
endif
#FLAG+=-lpthread
MAIN_FILE=$(TOP_DIR)/$(SRC_DIR)/$(TARGET).$(EXT_NAME)

TARGET_DIR=$(TOP_DIR)
TARGET_LIB_DIR=$(TOP_DIR)
OUTPUT_DIR=output
RM=rm

#OPENCV_OPT=$(shell pkg-config opencv4 --libs --cflags)

opencv:
	@echo build $@
	g++ -o $(OUTPUT_DIR)/$@ $(SRC_DIR)/opencv_test.cpp $(OPENCV_OPT)
	@echo finish $@

opencv_clean:
	@echo run $@
	rm -rf $(OUTPUT_DIR)/opencv 
	@echo finish $@

fopen:
	@echo build $@
	$(COMPILER) -o $(OUTPUT_DIR)/$@ $(SRC_DIR)/$@.$(EXT_NAME) $(INC_DIR) $(CFLAG)
	ls -l $(OUTPUT_DIR)/$@
	@echo finish $@

baekjoon_clean:
	@echo $@
	$(RM) $(OUTPUT_DIR)/baekjoon_*
	@echo finish $@

baekjoon:
	@echo build $@
	$(COMPILER) -o $(OUTPUT_DIR)/$@_$(BAEKJOON_NO) $(SRC_DIR)/$@_$(BAEKJOON_NO).$(EXT_NAME) $(INC_DIR) $(CPP_FLAG)
	ls -l $(OUTPUT_DIR)/$@_$(BAEKJOON_NO)
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

