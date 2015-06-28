CFLAGS= $(LCFLAGS) -I/usr/include/python2.7
LDFLAGS= $(LLDFLAGS) -li2c_dev -ltools -lpython2.7

EXEC=libmotor.so

SRC = $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)


all: $(EXEC)
	@mv $(EXEC) $(ROOT_DIR)$(BUILD_DIR)$(INSTALL_PATH)/$(EXEC)

libmotor.so: $(OBJ)
	@echo $@
	@$(CC) -Wall -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)
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
