CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion
SOURCE=main.c k.c ui.c hof.c
UNUSEDFUNC=--enable=unusedFunction


all: codecheck ps2

codecheck: $(SOURCE)
	cppcheck $(UNUSEDFUNC) --error-exitcode=1 $^

ps2: main.o k.o ui.o hof.o
	@echo "Running compilation..."
	@$(CC) $(CFLAGS) $^ -lm -o $@
	@echo "Compilation is ready!"

main.o: main.c
	@echo "Building object file main.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File main.o is ready!"

k.o: k.c
	@echo "Building object file k.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File k.o is ready!"

ui.o: ui.c
	@echo "Building object file ui.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File ui.o is ready!"

hof.o: hof.c
	@echo "Building object file hof.o..."
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo "File hof.o is ready!"

clean:
	@echo "File cleaning is in progress..."
	@rm *.o ps2
	@echo "Files are cleared!"
