CC=gcc
CFLAGS=-std=c11 -Werror -Wall -Wconversion
SOURCE=cheesefactory.c mm.c isolation.c racer.c
UNUSEDFUNC=--enable=unusedFunction


all: codecheck cheesefactory mm isolation racer

codecheck: $(SOURCE)
	cppcheck $(UNUSEDFUNC) --error-exitcode=1 $^

cheesefactory: cheesefactory.c
	@echo "Making cheesefactory file..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "File cheesefactory is ready!"

mm: mm.c
	@echo "Making mm file..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "File mm is ready!"

isolation: isolation.c
	@echo "Making isolation file..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "File isolation is ready!"

racer: racer.c
	@echo "Making racer file..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "File racer is ready!"

clean:
	@echo "File cleaning is in progress..."
	@rm cheesefactory mm isolation racer
	@echo "Files are cleared!"
