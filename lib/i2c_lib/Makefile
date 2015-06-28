CC=gcc
CFLAGS= -Wall -O3 -fPIC -I../../include
LDFLAGS= -lc
EXEC=libi2c_dev.so
SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
INSTALL_PATH = /lib

all: $(EXEC)

libi2c_dev.so: $(OBJ)
	@echo $@
	@$(CC) -Wall -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

install:
	cp $(EXEC) $(INSTALL_PATH)

remove:
	rm -rf $(INSTALL_PATH)/$(EXEC)

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)


.PHONY: clean mrproper install remove
