CFLAGS= $(DCFLAGS)
LDFLAGS= $(DLDFLAGS) -lpthread -li2c_dev

EXEC=pbot_com_daemon

SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)


all: $(EXEC)
	@mv $(EXEC) $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC)

pbot_com_daemon: $(OBJ)
	@echo $@
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "****END***"

%.o: %.c
	@echo $@
	@$(CC) -o $@ -c $< $(CFLAGS)

install:
	cp $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC) $(INSTALL_PATH)

remove:
	rm -rf $(INSTALL_PATH)/$(EXEC)

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC)


.PHONY: clean mrproper install remove
