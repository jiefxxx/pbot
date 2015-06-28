


all:
	cd ./i2c_lib && $(MAKE)
	#cd ./motor_lib && $(MAKE)
	cd ./tools && $(MAKE)

install:
	cd ./i2c_lib && $(MAKE) install
	#cd ./motor_lib && $(MAKE) install
	cd ./tools && $(MAKE) install

mrproper:
	cd ./i2c_lib && $(MAKE) mrproper
	cd ./motor_lib && $(MAKE) mrproper
	cd ./tools && $(MAKE) mrproper

clean:
	cd ./i2c_lib && $(MAKE) clean
	cd ./motor_lib && $(MAKE) clean
	cd ./tools && $(MAKE) clean

remove:
	cd ./i2c_lib && $(MAKE) remove
	cd ./motor_lib && $(MAKE) remove
	cd ./tools && $(MAKE) remove

.PHONY: clean mrproper install remove
