CC=gcc
CFLAGS= -Wall -O3 -fPIC -I../../include -I/usr/include/python2.7
LDFLAGS= -L../ -li2c_dev -ltools -lpython2.7
EXEC=libmotor.so
SRC = $(wildcard src/*.c) 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

libmotor.so: $(OBJ)
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

