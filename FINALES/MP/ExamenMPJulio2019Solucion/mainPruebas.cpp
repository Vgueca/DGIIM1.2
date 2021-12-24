/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainPruebas.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 2 de julio de 2019, 9:10
 */

#include <iostream>
#include <cstdlib>

#include "Imagen.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Imagen imagen; // Probar constructor por defecto Imagen::Imagen()

    cout << "PROBANDO operator<< con imagen vacía" << endl;
    cout << imagen; // Probar operator<< de Imagen

    cout << "PROBANDO operator= y constructor Imagen::Imagen(5,3,0)" << endl;
    imagen = Imagen(5, 3, 0); // Probar Imagen::operator= y constructor Imagen::Imagen(filas,columnas,valor)
    cout << imagen;

    cout << "PROBANDO constructor copia " << endl;
    Imagen imagen2(imagen); // Probar constructor de copia
    cout << imagen2;

    cout << "PROBANDO constructor Imagen(\"Imagenes/vacas.pgm\")" << endl;
    Imagen imagenVacas("Imagenes/vacas.pgm"); // Probar constructor Imagen::Imagen(const char* nombreFichero) 
    //cout << endl << imagenVacas;

    cout << "PROBANDO imagenVacas.guardar(\"Imagenes/Resultados/vacasCopia.pgm\")" << endl;
    imagenVacas.guardar("Imagenes/Resultados/vacasCopia.pgm"); // Probar Imagen::guardar(const char* nombreFichero)

    cout << "PROBANDO operator* (ENMASCARAR)" << endl;
    Imagen imagenMascaraP2("Imagenes/mascaraP2.pgm");
    Imagen imagen3 = imagenVacas * imagenMascaraP2; // Probar operator* de Imagen
    imagen3.guardar("Imagenes/Resultados/vacasMascaraP2.pgm");

    cout << "PROBANDO operator! (NEGATIVO)" << endl;
    imagen3 = !imagen3; // Probar operator! de Imagen 
    imagen3.guardar("Imagenes/Resultados/vacasMascaraP2Negativo.pgm");

    cout << "PROBANDO subImagen()" << endl;
    Imagen subIm=imagenVacas.subImagen(10, 60, 100, 100);
    subIm.guardar("Imagenes/Resultados/subImagenVacas.pgm");
    
    cout << "PROBANDO operator>" << endl;
    if(imagenVacas > subIm){
        cout << "     imgenenVacas>subIm" << endl;
    }
    else{
        cout << "     imgenenVacas<=subIm" << endl;
    }
    
    cout << "PROBANDO CREAR IMAGEN DESDE ARRAY PIXELS" << endl;
    Imagen imagen4 = Imagen::crearImagenFromArrayPixels("Imagenes/imagen1");
    if (imagen4.getNumeroFilas() > 0 && imagen4.getNumeroColumnas() > 0) {
        imagen4.guardar("Imagenes/Resultados/imagen1.pgm");
    } else {
        cout << "Fichero " << "Imagenes/imagen1 " << " no pudo convertirse a PGM" << endl;
    }

    return 0;
}

