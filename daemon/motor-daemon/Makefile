CC=gcc
CFLAGS= -O3 -I../../include -D_REENTRANT
LDFLAGS= -lpthread -li2c_dev -lm -lc -ltools -D_REENTRANT
EXEC=motor_api_daemon_test
SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
INSTALL_PATH = /bin

all: $(EXEC)

motor_api_daemon_test: $(OBJ)
	@echo $@
	@$(CC) -o $@ $^ $(LDFLAGS)
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
