# Author: ppdha82 <ppdha82@focushns.com>

TARGET=time
MAIN_FILE=$(TARGET).c

C_COMPILER=gcc

TARGET_DIR=./
TARGET_LIB_DIR=./

C_FLAG=-D'__DEBUG_ON__'

all: clean $(TARGET)
	@echo "finish $@"

install:
	@echo $@
	@echo "Copy files to $(TARGET_DIR)"
	@cp $(TARGET) $(TARGET_DIR)
	@cp -a lib$(TARGET).so $(TARGET_LIB_DIR)
	@echo Complete copying files

$(TARGET):
	@echo linking...
	$(C_COMPILER) -o $(TARGET) $(MAIN_FILE) $(C_FLAG)
	chmod 755 $@
	@echo =========== build end ===========

clean:
	@echo $@
	@echo Removing: $(TARGET) lib$(TARGET).so
	@rm -f $(TARGET) lib$(TARGET).so

