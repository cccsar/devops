
BEGIN { 
	doc = "/*\n * --------------\n *\n *\n */\n" ;
	#FS = "\n";
	#RS = "";
	#OFS = "\n";
}

	 $0 ~ /^[void,int,off_t] ?{ ?$/ { print($i)i }  

END { print " hola " }
