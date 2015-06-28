CFLAGS= $(DCFLAGS)
LDFLAGS= $(DLDFLAGS) -lpthread -li2c_dev
EXEC=magn_api_daemon

SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)


all: $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC)
	@echo "END-->"$(EXEC)

$(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC): $(OBJ)
	@echo "->"$@
	@@$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	@echo "-->"$@
	@$(CC) -o $@ -c $< $(CFLAGS)

install:
	cp $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC) $(INSTALL_PATH)

remove:
	rm -rf $(INSTALL_PATH)/$(EXEC)

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC)


.PHONY: clean mrproper install remove
