PS = ps4

FILE_MAIN = main
FILE1 = bmp
FILE2 = transformations

BUILD_DIR := ./build
O_FILES = $(BUILD_DIR)/$(FILE_MAIN).o $(BUILD_DIR)/$(FILE1).o $(BUILD_DIR)/$(FILE2).o

CC=gcc
CFLAGS=-std=c11 -Werror -Wall
SOURCE=$(FILE_MAIN).c $(FILE1).c $(FILE2).c
UNUSEDFUNC=--enable=unusedFunction


all: codecheck $(PS)

codecheck: $(SOURCE)
	cppcheck $(UNUSEDFUNC) --error-exitcode=1 $^

$(PS): $(O_FILES)
	@echo "Running compilation..."
	@$(CC) $(CFLAGS) $^ -lm -o $@
	@echo "Compilation is ready!"

$(BUILD_DIR)/$(FILE_MAIN).o: $(FILE_MAIN).c
	@echo "Building object file $(FILE_MAIN).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE_MAIN).o is ready!"

$(BUILD_DIR)/$(FILE1).o: $(FILE1).c
	@echo "Building object file $(FILE1).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE1).o is ready!"

$(BUILD_DIR)/$(FILE2).o: $(FILE2).c
	@echo "Building object file $(FILE2).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE2).o is ready!"

clean:
	@echo "File cleaning is in progress..."
	@rm $(O_FILES) $(PS)
	@echo "Files are cleared!"

