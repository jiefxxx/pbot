# pbot

#Description
pbot is a standardized API integration for controling robot;

| Path | Description          |
| ------------- | ----------- |
| /build                    | Store exe in compilation time |
| /daemon                   | Store src of daemon |
| /daemon/pbot-com-daemon   | Net controller |
| /daemon/pbot-motor-daemon | Motor controller |
| /daemon/pbot-magn-daemon  | Magn controller |
| /data                     | Store memory map and local socket file (need to be remap in file system)|
| /include                  | Include dir |
| /lib                      | Store src of lib |
| /lib/tools                | Useful fct |
| /lib/i2c_dev              | pseudo driver for all i2c devices |
| /pbot-interpreter         | interpreter python (working on) |

#Dependences:
  *lib i2c and driver i2c*
  *pthreads*
  *(wiring pi)(currently not implenmeted)*

  work on fedora, pidora, debian, raspbian.

#install:
  make
  make install
