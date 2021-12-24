/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Text2PGM.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 9 de julio de 2019, 14:09
 */

#include <fstream>
#include <iostream>

#include "Imagen.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Error: número de argumentos erróneo. Los argumentos deben ser:"
                << " nombreFicheroTextoConNombresFicherosPixels" << endl;
        exit(1);
    }
    ifstream flujo;
    string nombreFichero;
    int nFicherosCorrectos=0;

    flujo.open(argv[1]);
    if (!flujo) {
        cerr << "No se pudo abrir el fichero " << argv[1] << endl;
        exit(1);
    }
    while (flujo) { // Leemos líneas con nombres de fichero de imagen
        getline(flujo, nombreFichero);
        cout << "LEIDO " << nombreFichero << endl;
        if (flujo) {
            Imagen imagen = Imagen::crearImagenFromArrayPixels(nombreFichero.c_str());
            if (imagen.vacia()) {
                cerr << "Fichero " << nombreFichero <<
                        " no existe, o la imagen leída está vacía" << endl;
            }
            else{
                string nombreFicheroSalida=nombreFichero+".pgm";
                
                nFicherosCorrectos++;
                if(!imagen.guardar(nombreFicheroSalida.c_str())){
                        cerr << "No pudo guardarse la imagen en el fichero " <<
                                nombreFicheroSalida << endl;
                }
            }
        }
    } // end while
    cout << "Número de ficheros correctamente transformados: " << 
            nFicherosCorrectos << endl;

    return 0;
}

