INSTALL_PATH = $(DAEMON_INSTALL_PATH)

DCFLAGS= $(MCFLAGS) -Wall -O3 -I../../include -D_REENTRANT
DLDFLAGS= $(MLDFLAGS) -L$(ROOT_DIR)$(BUILD_DIR)$(LIB_INSTALL_PATH) -lm -lc -ltools -D_REENTRANT


export DCFLAGS DLDFLAGS INSTALL_PATH

all:
	#cd ./accel-daemon && $(MAKE)
	cd ./com-daemon && $(MAKE)
	cd ./com-daemon-test && $(MAKE)
	#cd ./gyro-daemon && $(MAKE)
	cd ./magn-daemon && $(MAKE)
	cd ./motor-daemon && $(MAKE)

install:
	#cd ./accel-daemon && $(MAKE) install
	cd ./com-daemon && $(MAKE) install
	cd ./com-daemon-test && $(MAKE) install
	#cd ./gyro-daemon && $(MAKE) install
	cd ./magn-daemon && $(MAKE) install
	cd ./motor-daemon && $(MAKE) install

mrproper:
	#cd./accel-daemon && $(MAKE) mrproper
	cd ./com-daemon && $(MAKE) mrproper
	cd ./com-daemon-test && $(MAKE) mrproper
	#cd ./gyro-daemon && $(MAKE) mrproper
	cd ./magn-daemon && $(MAKE) mrproper
	cd ./motor-daemon && $(MAKE) mrproper

clean:
	#cd ./accel-daemon && $(MAKE) clean
	cd ./com-daemon && $(MAKE) clean
	cd ./com-daemon-test && $(MAKE) clean
	#cd ./gyro-daemon && $(MAKE) clean
	cd ./magn-daemon && $(MAKE) clean
	cd ./motor-daemon && $(MAKE) clean

remove:
	#cd ./accel-daemon && $(MAKE) remove
	cd ./com-daemon && $(MAKE) remove
	cd ./com-daemon-test && $(MAKE) remove
	#cd ./gyro-daemon && $(MAKE) remove
	cd ./magn-daemon && $(MAKE) remove
	cd ./motor-daemon && $(MAKE) remove

.PHONY: clean mrproper install remove
