# Author: ppdha82 <ppdha82@focushns.com>

TOP_DIR=$(PWD)
COMPILER=C
TARGET=analysis_ai_metadata
#TARGET=dirent

ifeq ($(COMPILER), C)
COMPILER=gcc
FLAG=-D'__DEBUG_ON__'
SRC_DIR=c_source
EXT_NAME=c
else
ifeq ($(COMPILER), CPP)
COMPILER=g++
FLAG=-D'__DEBUG_ON__'
SRC_DIR=cpp_source
EXT_NAME=cpp
endif
endif
MAIN_FILE=$(TOP_DIR)/$(SRC_DIR)/$(TARGET).$(EXT_NAME)

TARGET_DIR=$(TOP_DIR)
TARGET_LIB_DIR=$(TOP_DIR)


INC_DIR=-I$(TOP_DIR)/include

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

