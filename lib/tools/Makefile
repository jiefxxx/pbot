CC=gcc
CFLAGS= -Wall -O3 -fPIC -I../../include 
LDFLAGS= -lc 
EXEC=libtools.so
SRC = $(wildcard src/*.c) 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

install:
	@cp *.so ../
	
libtools.so: $(OBJ)
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

