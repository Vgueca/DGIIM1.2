#!/bin/bash
# Autor: S. Villena
#
ayuda="\n Los modos de uso de examen1.sh son:\n
 1-> ./examen1.sh cadenaCaracteres. Saca todos los archivos del directorio \n
	 de trabajo que contenga en su nombre la cadenaCaracteres, ó \n
 2-> ./examen1.sh  nombreArchivo1 nombreArchivo2. Si no existe el archivo nombreArchivo2, \n copia el archivo nombreArchivo1 en el archivo nombreArchivo2. Si ya existe el archivo \n nombreArchivo2, entonces se le añade al final del archivo nombreArchivo2 el contenido del \n archivo nombrearchivo1, ó \n
 3-> ./examen1.sh  nombrearchivo1 nombreDirectorio. Copia el archivo nombreArchivo1 \n 
en el directorio nombreDirectorio.  ó	\n 
 4->d. En cualquier otro caso que sea ejecutado el guión ./examen1.sh, Deberá imprimir \n
 sobre el terminal el texto que contiene los apartados (a) hasta el (d), que servirá de ayuda.
\n "
# Si el guión (script) se ejecuta sin argumentos o con un número \n erróneo de argumentos o un tipo de argumento no esperado. \n" 
# (si se esperan archivos y son directorios o viceversa) dependiendo \n de la opciones #seleccionadas, el script mostrará la ayuda."


if [ $# == 1 ]; then
	ls -d *$1*
#	exit 1
elif [ $# == 2 ] ; then
# Comprobamos los argumentos
	if test -f $1 ; then 
		if  test -f $2 ; then
				cat $1 >> $2
				echo -e " \n Añadido el archivo $1 al final del archivo $2 \n"
#				exit 0
			elif test -d $2 ; then
				cp $1 $2
				echo -e " \n Copiado el archivo $1 en el directorio $2\n"
			else
				echo -e "\n El archivo: $2 no  existe , se crea \n
un archivo plano y se copia el archivo $1\n"
				cp $1 $2
#				exit 0
			fi
	else
		echo -e "\n No se puede ejecutar $0 porque el archivo $1 no existe \n"
		echo -e $ayuda 
	fi
else
		
			echo -e " \n Error en el uso de examen1.sh \n"
			echo -e $ayuda
#			exit -1
fi



