#ifndef DEF_MAGN_API_DATA
#define DEF_MAGN_API_DATA

#define MAGN_MAP_PATH "/home/jief/robot_api/map/magn_api.map"

#include <robotPy_type.h>

struct magn_control{
	int state;
	int hoffman;
	int socketEnable;
	struct D3_data val;
	struct D3_data calA;
	struct D3_data calB;
};

#endif
