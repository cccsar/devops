#!/bin/bash


TEST=`echo $1 | grep -E '([[:alpha:]]+\.)+[[:alpha:]]+'`;

#Verifica que el nombre de dominio escrito sea de hecho un nombre de dominio
if [ $TEST != $1 ]; then
	echo "tarea.sh: Error, nombre de dominio invalido"; 
	exit 1; 
fi



while (true) ; do 

	#hace ping al dominio solicitado, envia los resultados a un 
	#log y los almacena en una variable
	RESULT="`ping -q -c 3 -W 5 -w 20 $1`";

	#Si ping muestra comportamiento inesperado, se asume problema
	#en la red
	if [ "`echo $RESULT | grep -oE '%'`" != "%" ] ; then 
		echo "tarea.sh: Error, condicion inesperada de red."; 
		exit 2; 
	fi
	
	PACKET_LOSS=`echo -e $RESULT | grep "packet loss" | cut -d "," -f 3 | cut -d "%" -f 1 `;

	#Si el porcentaje hallado no es un entero, se toma la parte entera.
	if [ "`echo $PACKET_LOSS | grep -oE '\.'`" == "." ] ; then
		PACKET_LOSS=`echo $PACKET_LOSS | cut -d "." -f 1`;
	fi

	#verifica que haya perdida de paquetes:

	#Si hay 100% de perdida de paquetes, el dominio se considera caido, 
	#se envia un correo al administrador de dominio y se registra la 
	#perdida de paquetes
	if [ $PACKET_LOSS -eq 100 ] ; then 
		echo -e "Dominio caido.\n Enviando correo a administrador de dominio."; 
	
		#obtiene el correo del administrador del servidor DNS 
		#del dominio consultado
		FULL=`host -t SOA $1 | cut -d " " -f 6 `;
		
		#verifica que de hecho se obtenga un registro SOA que 
		#utilizar para buscar el correo del administrador
		if [ "`echo $FULL | grep -oE "SOA"`" != "SOA" ] ; then
			echo "tarea.sh: Error, servidor de nombres no contesta";
			echo "Imposible obtener correo de administrador."; 
			exit 3; 
		fi
	
		UNAME=`echo $FULL | cut -d "." -f 1`;
		DOMAIN=`echo $FULL | cut -d "." -f 2-`; 
	
		echo -e	"To: $UNAME@$DOMAIN\n
			From: $USER@$HOSTNAME\n 
			Subject: Dominio caido \n
			Buenas, el dominio $1 esta caido" | sendmail -vt;


		echo $RESULT >> log_fallas.txt; 

		exit 4 ; 

	#Si la perdida de paquetes es menor a 100% pero mayor a 0% solo se registra 
	elif [ $PACKET_LOSS -gt 0 ]; then 
		echo -e $RESULT >> log_fallas.txt; 
	fi	

	sleep 60; 

done; 
