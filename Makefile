

all:
	@(cd ./lib && $(MAKE) )
		@(echo "################################# COMPIL LIB COMPLETE ###################")
	@(cd ./lib && $(MAKE) install)
	@(echo "install lib complete")
	@(cd ./daemon && $(MAKE) )
	@(echo "################################# COMPIL DAEMON COMPLETE ###################")
	@(cd ./daemon && $(MAKE) install)
	@(echo "install daemon complete")

libs:
	@(cd ./lib && $(MAKE) )
	@(echo "################################# COMPIL LIB COMPLETE ###################")

daemons:
	@(cd ./lib && $(MAKE) )
	@(echo "################################# COMPIL DAEMON COMPLETE ###################")

install_lib:
	@(cd ./lib && $(MAKE) install)
	@(echo "install lib complete")

clean:
	(cd ./daemon && $(MAKE) clean)
	(cd ./lib && $(MAKE) clean)

mrproper:
	(cd ./daemon && $(MAKE) mrproper)
	(cd ./lib && $(MAKE) mrproper)
