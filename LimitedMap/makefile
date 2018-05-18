CC = clang++
OUT_FILE_NAME = LimitedMap
CFLAGS= -Wall -std=c++14
INC=  -I../../education/test_tool
OUT_DIR= ./bin

all: dirmake
	$(CC) $(CFLAGS) $(INC) $(LIBS) *.cpp ../../education/test_tool/test_helpers.cpp -o $(OUT_DIR)/$(OUT_FILE_NAME)
		
dirmake:
	@mkdir -p $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/* Makefile.bak
	rm -r $(OUT_DIR)

rebuild: clean build