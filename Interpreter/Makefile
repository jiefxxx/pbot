CC=gcc
CFLAGS= -I../include -I/usr/include/python2.7 -D_REENTRANT
LDFLAGS=-lpthread -lpython2.7 -ldl -D_REENTRANT
EXEC=robotPy
SRC+= $(wildcard src/*.c) 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

robotPy: $(OBJ)
	@echo $@
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)

