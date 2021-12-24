#!/bin/bash

# Cree un guión (script) para que saque por pantalla solamente aquellos ficheros en /etc que cumplan todas las siguientes condiciones:
# a) el propietario es el usuario root
# b) no fue modificado en las últimas 2 semanas
# c) el fichero no contiene la letra r, a y  p
# d) el fichero tiene permisos de lectura para otros

find /etc   -user "root"   -perm -o+r   -regex ".+/[^rpa]+$"   -not -mtime -14  2> /dev/null
