
all: libtools libi2c

libtools:
	cd lib/tools/ && $(MAKE)
	
libi2c:
	cd lib
