

all:
	$(MAKE) libs
	$(MAKE) daemons

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
