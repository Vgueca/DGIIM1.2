## EXAMEN PARCIAL 1: PRUEBA B

*Examen del Año 2018~2019. Temas: 1,2,3,4 (Módulo 1)*

#### 1. (8 puntos) Construya un script *examen1.sh* que cumpla lo siguiente:

* a) *./examen1.sh --c cadenaCaracteres* : Saca el numero y los nombres de los archivos del directorio de trabajo que contenga en su nombre la *cadenaCaracteres*.
* b) *./examen1.sh --f nombreArchivo1 nombreArchivo2* : Si no existe el archivo nombreArchivo2, copia el archivo *nombreArchivo1* en el archivo *nombreArchivo2*. Si ya existe el archivo *nombreArchivo2*, entonces se le añade al final del archivo *nombreArchivo2* el contenido del archivo *nombreArchivo1*.
* c) *./examen1.sh --b cadenaCaracteres nombreDirectorio* : Copia los archivos con la cadena en su nombre en el directorio *nombreDirectorio*.
* d) En cualquier otro caso que sea ejecutado el guión *./examen1.sh*, deberá imprimir sobre el terminal el texto que contiene los apartados (a) hasta el (d), que servirá de ayuda.

#### 2. (2 puntos) Cree un script *examen2.sh* que señale las palabras en rojo que contengan las secuencias de letras *ea* y *me* de todos los archivos terminados en .sh en el directorio que se ejecuta el guión.