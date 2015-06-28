CC=gcc
CFLAGS= -O3 -I../../include -D_REENTRANT
LDFLAGS= -lpthread -lm -lc -ltools -D_REENTRANT
EXEC=pbot_com_daemon
SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

pbot_com_daemon: $(OBJ)
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
