CC=gcc
CFLAGS=-o
TARGETS=shell
all: $(TARGETS)
.PHONY: all
%:
	$(CC) -g -o $@ $@.c 
       
clean:
	rm $(TARGETS)
