import gobject
gobject.threads_init()

from dbus import glib
glib.init_threads()

import dbus
import robotPy_systemd 

class NetworkMananger():
	def __init__(self):
		rsd = robotPy_systemd.RoboPy_systemd()
		
		self._bus = dbus.SystemBus()
		busPath= "/"+rsd.get_service_properties("NetworkManager.service",'BusName').replace('.',"/")
		busName= rsd.get_service_properties("NetworkManager.service",'BusName')
		# Create an object that will proxy for a particular remote object.
		self._NM = self._bus.get_object(busName,busPath)

		self._NM.introspectiv()






