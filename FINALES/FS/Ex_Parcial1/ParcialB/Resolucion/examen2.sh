#!/bin/bash
# Señala las palabras en rojo que contengan las secuencias de letras ea y me de todos los archivos terminados en .sh  en el directorio que se ejecuta el guión.
 grep -n --color=always "[e][a]\|[m][e]" *.sh
