#!/bin/bash

TEST=`echo $1 | grep -E '([[:alpha:]]+\.)+[[:alpha:]]+'`;

#Verifica que el nombre de dominio escrito sea de hecho un nombre de dominio
if [ $TEST != $1 ]; then
	echo "Error. Wrong domain name"; 
	exit 1; 
fi



while (true) ; do 

	#hace ping al dominio solicitado, envia los resultados a un log y los almacena en una variable
	RESULT=`ping -q -c 5 -W 5 $1 | tee log_fallas.txt`;
	
	PACKET_LOSS=`echo $RESULT | grep "packet loss" | cut -d "," -f 3 | cut -d "%" -f 1 `;

	echo $PACKET_LOSS;
	#verfica que haya perdida de paquetes
	if [ $PACKET_LOSS -gt 0 ] ; then 
		echo -e "Perdida de paquetes.\n Enviando correo a administrador de dominio."; 
	
		#obtiene el correo del administrador del servidor DNS del dominio consultado
		FULL=`host -t SOA $1 | cut -d " " -f 6 `;
	
		UNAME=`echo $FULL | cut -d "." -f 1`;
		DOMAIN=`echo $FULL | cut -d "." -f 2-`; 
	
		echo -e	"To: $UNAME@$DOMAIN\n
			From: $USER@$HOSTNAME\n 
			Subject: Dominio caido \n
			Buenas, el dominio $1 esta caido" | sendmail -vt;
		exit 2 ; 
	fi
	
	exit 0; 
	
done; 

