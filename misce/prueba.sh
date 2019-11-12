#!/bin/bash

root=$1

function traverse () { 
	temp=$root; 
	echo "root antes antes $root"

	for i in `ls -F $root` ; do 
		path=$temp$i;
		a=`stat --printf="%F\n" $path`; 
		if [ "$a" = "directorio" ] ; then 
			echo -e "\troot antes de llamada rec: $root"; 
			traverse; 
		else 
			echo `stat --printf="%n\n" $root$i`; 
		fi ; 

	done 

	root=$temp;
	echo -e "\troot despues de llamada rec: $root";

}

traverse;
