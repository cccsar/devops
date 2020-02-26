#!/bin/bash

TEST=`echo $1 | grep -E '([[:alpha:]]+\.)+[[:alpha:]]+'`

#Verifica que el nombre de dominio escrito sea de hecho un nombre de dominio
if [ $TEST != $1 ]; then
	echo "Error. Wrong domain name"; 
	exit 1; 
fi


#hace ping al dominio solicitado, envia los resultados a un log y los almacena en una variable
RESULT=`ping -q -c 4 -W 5 $1 | tee log_fallas.txt`;


#verfica que haya perdida de paquetes
if [ `echo $RESULT | grep "packet loss" | cut -d "," -f 3 | cut -d "%" -f 1 ` -lt 100 ] ; then 
	echo -e "Package loss.\nSending mail to administrator..." ; 

	#obtiene el correo del administrador del servidor DNS del dominio consultado
	FULL=`host -t SOA $1 | cut -d " " -f 6 `;

	UNAME=`echo $FULL | cut -d "." -f 1`;
	DOMAIN=`echo $FULL | cut -d "." -f 2-`; 

	echo "$UNAME@$DOMAIN";
	echo 	"To: $UNAME@$DOMAIN\n
		From: \n 
		Subject: Dominio caido \n
		Buenas, el dominio $1 esta caido" | sendmail -vt;
	exit 2 ; 
fi

