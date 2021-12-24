/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pregunta6Teoria.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 9 de julio de 2019, 11:50
 */

#include <iostream>
#include "Imagen.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) { // EXAMEN 6
    if (argc != 7) {
        cerr << "Error: número de argumentos erróneo. Los argumentos deben ser:"
                << " filaInicial columnaInicial"
                << " alto ancho ficheroImagen1 ficheroImagen2" << endl;
        exit(1);
    }
    
    int fil = atoi(argv[1]), col = atoi(argv[2]),
            alto = atoi(argv[3]), ancho = atoi(argv[4]);
    Imagen imagen1(argv[5]), imagen2(argv[6]);
    Imagen subimagen1, subimagen2;

    if (imagen1.vacia()) {
        cerr << "Imagen " << argv[5] << " no existe, o está vacía" << endl;
        exit(1);
    } else if (imagen2.vacia()) {
        cerr << "Imagen " << argv[6] << " no existe, o está vacía" << endl;
        exit(1);
    } else {
        if (fil < 0 || fil + alto > imagen1.getNumeroFilas() ||
                fil + alto > imagen2.getNumeroFilas() ||
                col < 0 || col + ancho > imagen1.getNumeroColumnas() ||
                col + alto > imagen2.getNumeroColumnas()) {
            cerr << "Error en dimensiones proporcionadas para la subimagen" << endl;
            exit(1);
        } else {
            string nombre_mayor;
            Imagen* mayorImagen;
            subimagen1 = imagen1.subImagen(fil, col, alto, ancho);
            subimagen2 = imagen2.subImagen(fil, col, alto, ancho);
            if (subimagen1 > subimagen2) {
                nombre_mayor = argv[5];
                mayorImagen = &subimagen1;
            } else {
                nombre_mayor = argv[6];
                mayorImagen = &subimagen2;
            }
            //string nombre_mayor = (subimagen1 > subimagen2 ? argv[5] : argv[6]);
            cout << "COMENTARIOS DE LA MAYOR SUBIMAGEN" << endl;
            cout << mayorImagen->getComentarios();
            cout << "La mayor subimagen es la extraída de " << nombre_mayor << endl;
        }
    }

    return 0;
}

