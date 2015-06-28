# pbot

pbot is a standardized API integration for controling robot;

Path Tree

/

-->/build -->where all  exe are build

-->/daemon -->where all  daemon source are
  -->pbot_com_daemon --> daemon communication net
  -->pbot_motor_daemon --> daemon control/flux(working on) motor
  -->pbot_magn_daemon --> daemon flux magn

-->/data --> keep memory map and local socket file and parametre((need to be remap in /etc/pbot or /var/pbot)

-->/include contain all the .h file

-->/lib --> where the lib src are store
  -->libi2c_dev.so --> pseudo driver for all i2c_dev
  -->libtools.so --> useful fonctions
  -->libpbot_api.so --> API fonctions with integrated ipc

-->/pbot-interpreter interpreter python (working on)

dependences:
  lib i2c and driver i2c
  --> i2c-tools and ... (lol)

  pthreads

  (wiring pi)(currently not implenmeted)

  work on fedora,pidora,debian,raspbian.

install:
  make
  make install
