CC = gcc

ROOT_DIR = $(shell pwd)
BUILD_DIR = /build

DAEMON_INSTALL_PATH = /bin
LIB_INSTALL_PATH = /lib

MCFLAGS = -Wall -O3 -I../../include -D_REENTRANT
MLDFLAGS = -L$(ROOT_DIR)$(BUILD_DIR)$(LIB_INSTALL_PATH) -D_REENTRANT

export cc
export ROOT_DIR BUILD_DIR
export LIB_INSTALL_PATH DAEMON_INSTALL_PATH
export MCFLAGS MLDFLAGS

all:
	$(MAKE) libs
	$(MAKE) daemons

install:
	sudo $(MAKE) install_libs
	sudo $(MAKE) install_daemons

test:
	echo $(root_dir)

libs:
	@cd ./lib && $(MAKE)
	@echo "################################# COMPIL LIB COMPLETE ###################"

daemons:
	@cd ./daemon && $(MAKE)
	@echo "################################# COMPIL DAEMON COMPLETE ###################"

install_libs:
	@cd ./lib && $(MAKE) install
	@echo "################################# INSTALL LIB COMPLETE ###################"

install_daemons:
	@cd ./daemon && $(MAKE) install
	@echo "################################# INSTALL DAEMON COMPLETE ###################"

clean:
	@cd ./daemon && $(MAKE) clean
	@cd ./lib && $(MAKE) clean

mrproper:
	@cd ./daemon && $(MAKE) mrproper
	@cd ./lib && $(MAKE) mrproper

remove:
	@cd ./daemon && $(MAKE) remove
	@cd ./lib && $(MAKE) remove

.PHONY: clean mrproper install remove install_daemons install_libs daemons libs
