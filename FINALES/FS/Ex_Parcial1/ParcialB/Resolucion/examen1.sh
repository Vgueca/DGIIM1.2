#!/bin/bash
# Autor: S. Villena
#
ayuda="\n Los modos de uso de examen1.sh son:\n
 1-> ./examen1.sh --c cadenaCaracteres. Saca el numero y los nombres de los archivos del directorio \n
	 de trabajo que contenga en su nombre la cadenaCaracteres, ó \n
 2-> ./examen1.sh --f nombreArchivo1 nombreArchivo2. Si no existe el archivo nombreArchivo2, \n copia el archivo nombreArchivo1 en el archivo nombreArchivo2. Si ya existe el archivo \n nombreArchivo2, entonces se le añade al final del archivo nombreArchivo2 el contenido del \n archivo nombrearchivo1, ó \n
 3-> ./examen1.sh --b cadenaCaracteres nombreDirectorio. Copia los archivos con la cadena en sumonbre en el  nombreDirectorio \n 
en el caso que no exista el directorio nombreDirectorio se creará.  
\n "

if [$# == 1]; then
	if [ $1 == "--h" ]; then
		echo -e $ayuda
	fi
fi

if [ $# == 2 ]; then
	if [ $1 == "--c" ]; then
		echo -e "\n El número de archivos con la cadena '$2' es de $(ls -d *$2* |wc -l) \n"
		echo .e " Los nombres son: $(ls -d *$2*) \n"
	else
		echo -e $ayuda
	fi
elif [ $# == 3 ] ; then
# Comprobamos los argumentos
	if [ $1 == "--b" ]; then
		if test -d $3 ; then 
			cp *$2* $3
			echo -e " \n Copiados los archivos: $(ls -d *$2*) en directorio $3 \n"
		else 
			mkdir $3
			echo -e " \n El directorio $3 no Existe, se crea \n"
			cp *$2* $3
			echo -e " \n Copiados los archivos: $(ls -d *$2*) en directorio $3 \n"
		fi
	elif [ $1 == "--f" ]; then
		if  test -f $2 ; then
			if test -f $3; then
					cat $2 >> $3
				echo -e " \n Añadido el archivo $2 al final del archivo $3 \n"
			else
				echo -e "\n El archivo $3 no existe se crea \n"
				cp $2 $3
			fi
		else
			echo -e "\n El archivo $2 no existe \n"
		fi
	else
		echo -e " \n Error en el uso de examen1.sh \n"
		echo -e $ayuda
	fi
else
		
			echo -e " \n Error en el uso de examen1.sh \n"
			echo -e $ayuda
fi
