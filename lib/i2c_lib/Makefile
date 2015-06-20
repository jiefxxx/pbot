CC=gcc
CFLAGS= -Wall -O3 -fPIC -I../../include 
LDFLAGS= -lc 
EXEC=libi2c_dev.so
SRC = $(wildcard src/*.c) 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

install:
	@cp *.so ../
	
libi2c_dev.so: $(OBJ)
	@echo $@
	@$(CC) -Wall -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)

