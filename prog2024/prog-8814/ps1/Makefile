CC=gcc
CFLAGS=-std=c11 -Wall -Werror
SOURCE=main.c bmp.c playfair.c
UNUSEDFUNC=--enable=unusedFunction

all: codecheck ps1

codecheck: $(SOURCE)
	cppcheck $(UNUSEDFUNC) --error-exitcode=1 $^

ps1: main.o bmp.o playfair.o
	@echo "Running compilation..."
	@$(CC) $(CFLAGS) $^ -lm -o $@
	@echo "Compilation is ready!"

main.o: main.c
	@echo "Building object file main.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File main.o is ready!"

bmp.o: bmp.c
	@echo "Building object file bmp.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File bmp.o is ready!"

playfair.o: playfair.c
	@echo "Building object file playfair.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File playfair.o is ready!"

clean:
	@echo "File cleaning is in progress..."
	@rm *.o ps1
	@echo "Files are cleared!"
