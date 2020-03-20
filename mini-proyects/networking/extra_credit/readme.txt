cliente: 
	shell_remoto_cli -i <dir-ip> -l <puerto_svr> 

	-requiere parser.
	-requiere validador de dirs ip. 

	-creara interfaz interactiva con prompt :">" que recibira alguno
	de los comandos enlistados al final.
	-El punto es que los comandos se ejecuten en el servidor y el output
	se **redireccione** a esta terminal. <-- que pasa si el output es ctte
	p.e.: ping
	-Manejador de senales para que cuando se interrumpan comandos 
	como ping no termine la ejecucion del comando. 

servidor:  ( AQUI HAY PARALELISMO ) 
	shell_remoto_svr -l <puerto_svr> 

	hilos manejaran cada comunicacion entrante -> como muchos comandos
	pueden ejecutarse en paralelo, asociar un fd de salida por cada
	conexion entrante


cmdlist:  ( NO TODOS SON EJECUTABLES CON PRIVILEGIOS NORMALES )  < - se
asumira root

a) $ echo $HOSTNAME
b) $ cat /etc/network/interfaces
c) $ cat /etc/resolv.conf
d) $ cat /etc/protocols
e) $ cat /etc/services
f) $ ifconfig eth0 192.120.67.200 netmask 255.255.255.0 up
1
g) $ iwconfig eth1 essid “red local privada 1”
h) $ nestat -a
i) $ netstat -s
j) $ route
k) $ route add default gw 192.168.110.3 eth0
l) $ ping www.google.com
m) $ traceroute 202.176.87.35 , traceroute google.com
n) $ arp -a , arp -n
o) $ nslookup usb.ve
