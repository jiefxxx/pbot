CC=gcc
CFLAGS= -Wall -O3 -fPIC -I../../include
LDFLAGS= -lc
EXEC=libtools.so
SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
INSTALL_PATH = /lib

all: $(EXEC)

libtools.so: $(OBJ)
	@echo $@
	@$(CC) -Wall -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

install:
	cp $(EXEC) $(INSTALL_PATH)

remove:
	rm -rf $(INSTALL_PATH)/$(EXEC)

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)


.PHONY: clean mrproper install remove
