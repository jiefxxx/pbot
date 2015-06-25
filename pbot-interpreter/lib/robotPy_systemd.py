import gobject
gobject.threads_init()

from dbus import glib
glib.init_threads()

import dbus

class RoboPy_systemd():
	def __init__(self):
		self._bus = dbus.SystemBus()
		# Create an object that will proxy for a particular remote object.
		self._systemd1 = self._bus.get_object("org.freedesktop.systemd1","/org/freedesktop/systemd1")
		
	def reboot(self):
		self._systemd1.Reboot()

	def powerOff(self):
		self._systemd1.PowerOff()

	def reload_all(self):
		self._systemd1.Reload()

	def get_unit_properties(self,name,properties):
		proxy =self._bus.get_object('org.freedesktop.systemd1', str(self._systemd1.GetUnit(name)))
		return proxy.Get('org.freedesktop.systemd1.Unit',properties,
		        dbus_interface='org.freedesktop.DBus.Properties')

	def get_service_properties(self,name,properties):
		proxy = self._bus.get_object('org.freedesktop.systemd1', str(self._systemd1.GetUnit(name)))
		return proxy.Get('org.freedesktop.systemd1.Service',properties,
		        dbus_interface='org.freedesktop.DBus.Properties')
	
	def reStart(self,name):
		self._systemd1.RestartUnit(name,"replace")

	def start(self,name):
		self._systemd1.StartUnit(name,"replace")

	def stop(self,name):
		self._systemd1.StopUnit(name,"replace")

	def kill(self,name,sig):
		self._systemd1.KillUnit(nam,"all",sig)






