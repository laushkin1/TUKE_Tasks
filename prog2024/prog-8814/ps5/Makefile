PROG_NAME = game

FILE_MAIN = main
FILE1 = backpack
FILE2 = command
FILE3 = container
FILE4 = game
FILE5 = item
FILE6 = parser
FILE7 = room
FILE8 = world

BUILD_DIR := ./build
O_FILES = $(BUILD_DIR)/$(FILE_MAIN).o $(BUILD_DIR)/$(FILE1).o $(BUILD_DIR)/$(FILE2).o $(BUILD_DIR)/$(FILE3).o $(BUILD_DIR)/$(FILE4).o $(BUILD_DIR)/$(FILE5).o $(BUILD_DIR)/$(FILE6).o $(BUILD_DIR)/$(FILE7).o $(BUILD_DIR)/$(FILE8).o

CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion
SOURCE=$(FILE_MAIN).c $(FILE1).c $(FILE2).c
UNUSEDFUNC=--enable=unusedFunction


all: codecheck $(PROG_NAME)

codecheck: $(SOURCE)
	cppcheck $(UNUSEDFUNC) --error-exitcode=1 $^

$(PROG_NAME): $(O_FILES)
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

$(BUILD_DIR)/$(FILE3).o: $(FILE3).c
	@echo "Building object file $(FILE3).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE3).o is ready!"
	
$(BUILD_DIR)/$(FILE4).o: $(FILE4).c
	@echo "Building object file $(FILE4).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE4).o is ready!"

$(BUILD_DIR)/$(FILE5).o: $(FILE5).c
	@echo "Building object file $(FILE5).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE5).o is ready!"
	
$(BUILD_DIR)/$(FILE6).o: $(FILE6).c
	@echo "Building object file $(FILE6).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE6).o is ready!"

$(BUILD_DIR)/$(FILE7).o: $(FILE7).c
	@echo "Building object file $(FILE7).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE7).o is ready!"
	
$(BUILD_DIR)/$(FILE8).o: $(FILE8).c
	@echo "Building object file $(FILE8).o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File $(FILE8).o is ready!"

clean:
	@echo "File cleaning is in progress..."
	@rm $(O_FILES) $(PROG_NAME)
	@echo "Files are cleared!"

