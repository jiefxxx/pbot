CC=gcc
CFLAGS= -O3 -I../../include -D_REENTRANT
LDFLAGS= -lpthread -li2c_dev -lm -lc -ltools -D_REENTRANT
EXEC=magn_api_daemon
SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

magn_api_daemon: $(OBJ)
	@echo $@
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

install:
		@cp $(EXEC) /bin/

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)
