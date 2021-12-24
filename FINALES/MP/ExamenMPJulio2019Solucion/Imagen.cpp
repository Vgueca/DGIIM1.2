/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imagen.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 2 de julio de 2019, 9:10
 */

#include <fstream>
#include <iostream>
#include <cmath>
#include <cassert>

#include "Imagen.h"

using namespace std;

void Imagen::crearImagenVacia() {
    filas = 0;
    columnas = 0;
    valores = nullptr;
    comentarios += "Creada vacía";
}

/**
 * Método auxiliar usado para reservar memoria dinámica para la imagen
 * @param nFilas Número de filas
 * @param nColumnas Número de columnas
 */
void Imagen::reservarMemoria(int nFilas, int nColumnas) { // EXAMEN 2.1.c
    if (nFilas > 0)
        filas = nFilas;
    else {
        filas = 0;
    }
    if (nColumnas > 0) {
        columnas = nColumnas;
    } else {
        columnas = 0;
    }
    if (filas > 0) {
        valores = new int*[nFilas];
        if (columnas > 0) {
            valores[0] = new int[filas * columnas];
            for (int i = 1; i < filas; i++) {
                valores[i] = valores[i - 1] + columnas;
            }
        } else {
            for (int i = 0; i < filas; i++) {
                valores[i] = nullptr;
            }
        }

    } else {
        valores = nullptr;
    }
}

/**
 * Método auxiliar para liberar la memoria dinámica que fue reservada
 * explícitamente para este objeto en la Imagen
 */
void Imagen::liberarMemoria() { // EXAMEN 2.3
    if (valores) {
        delete[] valores[0];
        delete[] valores;
        valores = nullptr;
        filas = columnas = 0;
    }
}

/**
 * Método auxiliar usado para copiar el contenido del objeto Imagen otro en el
 * objeto actual
 * @param otro El objeto Imagen a partir del que se rellena el objeto actual
 */
void Imagen::copiar(const Imagen& otro) { // Se supone implementado
    comentarios = otro.comentarios;
    for (int fil = 0; fil < otro.filas; fil++) {
        for (int col = 0; col < otro.columnas; col++) {
            valores[fil][col] = otro.valores[fil][col];
        }
    }
}

/**
 * Constructor por defecto de la Imagen
 */
Imagen::Imagen() { // EXAMEN 2.1.a
    crearImagenVacia();
}

/**
 * Constructor de copia de la Imagen
 * @param orig Imagen usada para hacer la copia
 */
Imagen::Imagen(const Imagen& orig) { // Se supone implementado
    reservarMemoria(orig.filas, orig.columnas);
    copiar(orig);
}

/**
 * Constructor de Imagen, especificando número de filas, columnas, y valor para
 * todos los pixels 
 * @param nfil Número de filas 
 * @param ncol Número de columnas
 * @param valor Valor para todos los pixels de la imagen 
 */
Imagen::Imagen(int nfil, int ncol, int valor) { // EXAMEN 2.1.c
    reservarMemoria(nfil, ncol);
    for (int fil = 0; fil < filas; fil++) {
        for (int col = 0; col < columnas; col++) {
            valores[fil][col] = valor;
        }
    }
    string cadena = "Creada " + to_string(filas) + "x" + to_string(columnas)
            + " a valor " + to_string(valor);
    comentarios += cadena;
}

/**
 * Operador de asignación
 * @param orig Imagen usada para hacer la copia
 * @return El objeto Imagen actual tras asignarle la imagen orig
 */
Imagen& Imagen::operator=(const Imagen& orig) { // EXAMEN 2.2
    if (this != &orig) {
        liberarMemoria();
        reservarMemoria(orig.filas, orig.columnas);
        copiar(orig);
    }
    return *this;
}

/**
 * Destructor
 */
Imagen::~Imagen() { // EXAMEN 2.3
    liberarMemoria();
}

/**
 * Método que libera la memoria dinámica usada por el objeto actual, tanto la
 * que fue reservada expĺícitamente por la clase Imagen, como la que reservó
 * la clase Comentarios
 */
void Imagen::clear() { // EXAMEN 3.1
    comentarios.clear();
    liberarMemoria();
}

/**
 * Operador de extracción de un flujo para la clase Imagen
 * @param flujo El flujo fuente de donde se extraen datos
 * @param imagen Imagen destino donde se insertan los datos de la imagen
 * @return El flujo fuente de donde se extraen datos
 */
std::istream& operator>>(std::istream& flujo, Imagen& imagen) { // EXAMEN 3.1
    int nfil, ncol, maxLuminosidad;
    imagen.clear();
    flujo >> imagen.comentarios;

    flujo >> ncol >> nfil >> maxLuminosidad;
    imagen.reservarMemoria(nfil, ncol);

    for (int fil = 0; fil < nfil; fil++) {
        for (int col = 0; col < ncol; col++) {
            flujo >> imagen.valores[fil][col];
        }
    }
    return flujo;
}

/**
 * Constructor que crea un objeto Imagen leyéndolo de un fichero de texto en
 * formato PGM P2. En caso de que la imagen no pueda ser leída del fichero, o 
 * bien el fichero no contenga una imagen PGM P2, crea una imagen vacía
 * @param nombreFichero Nombre del fichero de texto que contiene la imagen
 * PGM P2
 */
Imagen::Imagen(const char* nombreFichero) { // EXAMEN 3.2
    ifstream flujo;
    string cadena;

    crearImagenVacia();
    flujo.open(nombreFichero);
    if (flujo) {
        getline(flujo, cadena); // Leer P2 //flujo >> cadena; no sirve pues queda el \n sin leer
        if (cadena == "P2") {
            flujo >> *this;
        }
        flujo.close();
    } else {
        std::cerr << "Error, fichero " << nombreFichero << " no ha podido ser abierto" << std::endl;
    }
}

/**
 * Guarda este objeto Imagen en un fichero de texto en formato PGM P2
 * @param nombreFichero Nombre del fichero de texto donde se guardará la imagen
 * @return true si pudo guardarse el fichero. false en otro caso.
 */
bool Imagen::guardar(const char* nombreFichero) const { // EXAMEN 3.3 y examen prácticas
    ofstream flujo;
    flujo.open(nombreFichero);
    if (flujo) {
        flujo << "P2" << std::endl;
        flujo << *this;
        flujo.close();
        return true;
    }
    return false;
}

/**
 * Operador de inserción en flujos para objetos Imagen
 * @param flujo Flujo destino donde se insertará el objeto Imagen
 * @param imagen El objeto Imagen a insertar en el flujo destino
 * @return El flujo destino 
 */
std::ostream& operator<<(std::ostream& flujo, const Imagen& imagen) { // EXAMEN 3.3
    flujo << imagen.comentarios;
    flujo << imagen.columnas << " " << imagen.filas << " " << std::endl << 255 << std::endl;

    for (int fil = 0; fil < imagen.filas; fil++) {
        for (int col = 0; col < imagen.columnas; col++) {
            flujo << imagen.valores[fil][col] << " ";
        }
        flujo << std::endl;
    }

    return flujo;
}

/**
 * Operador () usado para recuperar como rvalue el pixel de la posición fila=fil,
 * columna=col
 * @param fil Número de fila. Se supone 1<=fil<=filas
 * @param col Número de columna. Se supone 1<=col<=columnas
 * @return El valor de pixel que hay en la posición fila=fil, columna=col
 */
const int& Imagen::operator()(int fil, int col) const { // EXAMEN 4.1
    assert(fil >= 1 && col >= 1 && fil <= filas && col <= columnas);
    return valores[fil - 1][col - 1];
}

/**
 * Operador () usado para recuperar como lvalue el pixel de la posición fila=fil,
 * columna=col
 * @param fil Número de fila
 * @param col Número de columna
 * @return El valor de pixel que hay en la posición fila=fil, columna=col
 */
int& Imagen::operator()(int fil, int col) { // EXAMEN 4.1
    assert(fil >= 1 && col >= 1 && fil <= filas && col <= columnas);
    return valores[fil - 1][col - 1];
}

/**
 * Operador * usado para aplicar una máscara (imagen2) a otra imagen (imagen1)
 * @param imagen1 Imagen a la que se aplicará la máscara
 * @param imagen2 Imagen usada como máscara
 * @return Imagen resultante de aplicar la máscara
 */
Imagen operator*(const Imagen& imagen1, const Imagen& imagen2) { // EXAMEN 4.2
    Imagen imagen;

    if (imagen1.filas == imagen2.filas && imagen1.columnas == imagen2.columnas) {
        imagen = Imagen(imagen1.filas, imagen1.columnas);
        for (int fil = 1; fil <= imagen.filas; fil++) {
            for (int col = 1; col <= imagen.columnas; col++) {
                if (imagen2(fil, col) == 0) {
                    imagen(fil, col) = imagen1(fil, col);
                } else {
                    imagen(fil, col) = imagen2(fil, col);
                }
            }
        }
        imagen.comentarios = imagen1.comentarios;
        imagen.comentarios += "----------";
        imagen.comentarios += imagen2.comentarios;
        imagen.comentarios += "----------";
        imagen.comentarios += "Creada por: ENMASCARAMIENTO";
    }
    return imagen;
}

/**
 * Operador ! usado para obtener el negativo de la imagen actual
 * @return La nueva imagen creada con el negativo de la imagen actua
 */
Imagen Imagen::operator!() const { // EXAMEN 4.3
    Imagen imagen(*this);

    for (int fil = 0; fil < imagen.filas; fil++) {
        for (int col = 0; col < imagen.columnas; col++) {
            imagen.valores[fil][col] = 255 - imagen.valores[fil][col];
        }
    }
    imagen.comentarios += "----------";
    imagen.comentarios += "Creada por: NEGATIVO";
    return imagen;
}

/**
 * Obtiene una subimagen de la imagen actual especifiando las coordenadas de 
 * la esquina superior izquierda, el alto y ancho de la subimagen. Este método
 * no hace ninguna comprobación sobre la corrección de las coordenadas de la 
 * esquina superior izquierda y del ancho y alto de la subimagen. Resultados inesperados
 * pueden ocurrir si no son correctos
 * @param filaInicial Fila inicial de la imagen actual 
 * @param columnaInicial Columna inicial de la imagen actual
 * @param alto Número de filas de la subimagen
 * @param ancho  Número de columnas de la subimagen
 * @return La subimagen obtenida como resultado
 */
Imagen Imagen::subImagen(int filaInicial, int columnaInicial, int alto, int ancho) const { // EXAMEN 5.1
    Imagen imagen(alto, ancho);
    for (int fila = filaInicial; fila < (filaInicial + alto); fila++) {
        for (int columna = columnaInicial; columna < (columnaInicial + ancho); columna++) {
            imagen.valores[fila - filaInicial][columna - columnaInicial] = this->valores[fila][columna];
        }
    }
    imagen.comentarios = comentarios;
    imagen.comentarios += "----------";
    string cadena;
    imagen.comentarios += "Subimagen desde: " + to_string(filaInicial) + ", " + to_string(columnaInicial)
            + " de dimensiones " + to_string(alto) + " x " + to_string(ancho);

    return imagen;
}

/**
 * Calcula el valor medio de los pixels de la imagen actual
 * @return El valor medio de los pixels de la imagen actual
 */
double Imagen::valorMedio() const { // EXAMEN 5.2
    double valorM = 0.0;
    for (int fil = 0; fil < this->filas; fil++) {
        for (int col = 0; col < this->columnas; col++) {
            valorM += this->valores[fil][col];
        }
    }
    return valorM / (filas * columnas);
}

/**
 * Operador > para comparar la imagen actual con la Imagen imagen. La comparación se
 * basa en el uso del método valorMedio()
 * @param imagen El segundo operando de la comparación
 * @return true si la Imagen actual es mayor a la Imagen imagen. false en otro
 * caso.
 */
bool Imagen::operator>(const Imagen& imagen) const { // EXAMEN 5.3
    if (this->valorMedio() > imagen.valorMedio()) {
        return true;
    } else {
        return false;
    }
}

const Comentarios & Imagen::getComentarios() const { // Se supone implementado
    return comentarios;
}

bool Imagen::vacia() const {
    if (filas == 0 || columnas == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Calcula un valor de distancia entre las filas de una imagen. Ver enunciado del 
 * examen para más detalles. Un valor pequeño indica que hay poca diferencia 
 * entre filas consecutivas.
 * @return El valor de distancia calculado.
 */
double Imagen::calcularValorDistanciaFilas() const { // EXAMEN de Prácticas
    double similitudTotal = 0.0, similitudFila;

   for (int fila = 1; fila < this->getNumeroFilas(); fila++) {
        similitudFila = 0;
        for (int columna = 1; columna < this->getNumeroColumnas(); columna++) {
            similitudFila += pow((*this)(fila, columna) - (*this)(fila + 1, columna), 2);
        }
        similitudFila = similitudFila / this->getNumeroColumnas();
        similitudTotal += similitudFila;
    }

    similitudTotal = similitudTotal / (this->getNumeroFilas() - 1);

    return similitudTotal;
}

/**
 * Lee un fichero de texto que contiene únicamente valores de pixels separados por
 * blancos. La lista de pixels será almacenada en el array dinámico arrayPixels 
 * (reservado dentro de esta función). El número de pixels será almacenado en 
 * nPixels.
 * @param nombreFichero Nombre del fichero de texto que contiene los pixels
 * @param arrayPixels El array de pixels que almacenará los pixels del fichero
 * de texto
 * @param nPixels Número de pixels que se han leído del fichero
 * @return true si el flujo pudo leerse, false en caso contrario
 */
bool leerFicheroPixels(const char* nombreFichero, int* & arrayPixels, int& nPixels) { // EXAMEN de Prácticas
    ifstream flujo;
    bool errorEnFlujo = true;
    int pixel;

    nPixels = 0;
    flujo.open(nombreFichero);
    if (flujo) {
        while (flujo) { // Contamos número de pixels
            flujo >> pixel;
            if (flujo) {
                nPixels++;
            }
        }
        errorEnFlujo = false;
        flujo.close();

        arrayPixels = new int[nPixels];
        flujo.open(nombreFichero);
        if (flujo) {
            int i = 0;
            while (flujo) { // Leemos y guardamos pixels
                flujo >> pixel;
                if (flujo) {
                    arrayPixels[i] = pixel;
                    i++;
                }
            }
        }
        flujo.close();
    }
    return !errorEnFlujo;
}

/**
 * Constructor de Imagen a partir de un array de pixels. Los pixels de la nueva
 * imagen serán una copia de los contenidos en el array de pixels
 * @param nfil Número de filas de la imagen a crear
 * @param ncol Número de columnas de la imagen a crear
 * @param arrayPixels El array de pixels usado para crear la imagen
 */
Imagen::Imagen(int nfil, int ncol, const int* arrayPixels) { // EXAMEN de Prácticas
    int i = 0;
    reservarMemoria(nfil, ncol);
    for (int fil = 0; fil < nfil; fil++) {
        for (int col = 0; col < ncol; col++) {
            valores[fil][col] = arrayPixels[i];
            i++;
        }
    }
}

/**
 * Calcula la mejor configuración filas, columnas para la imagen contenida en
 * el array de pixels
 * @param arrayPixels El array de pixels de la imagen
 * @param nPixels Número de pixels de la imagen
 * @return El número de filas de la mejor configuración (número filas y columnas)
 * correspondiente a la imagen que mejor (menor) valor de distancia proporcione.
 * Devuelve -1 si no hay ningúna configuración adecuada al ser nPixels un número 
 * primo o número impar.
 */
int calcularMejorNumeroFilas(const int* arrayPixels, int nPixels) { // EXAMEN de Prácticas
    int mejorNFilas = -1;
    int nColumnas;
    double mejorValor, valor;

    for (int nFilas = 2; nFilas < (nPixels / 2); nFilas++) {
        if (nPixels % nFilas == 0) {
            nColumnas = nPixels / nFilas;
            Imagen imagen = Imagen(nFilas, nColumnas, arrayPixels);
            valor = imagen.calcularValorDistanciaFilas();

            if (mejorNFilas == -1 || (mejorNFilas != -1 && valor < mejorValor)) {
                mejorValor = valor;
                mejorNFilas = nFilas;
            }
        }
    }
    return mejorNFilas;
}

/**
 * 
 * @param nombreFichero El nombre del fichero que contiene una lista de pixels de 
 * una imagen
 * @return La imagen que mejor se adapta a la lista de pixels leídos del fichero
 * cuyo nombre se pasa como parámetro a esta función (nombreFichero)
 */
Imagen Imagen::crearImagenFromArrayPixels(const char* nombreFichero) { 
    // EXAMEN de Prácticas. En el examen se pedía un constructor
    // pero ya había un constructor con un string como parámetro en 
    // examen de teoría
    int* arrayPixels = nullptr;
    int nPixels;
    Imagen imagen;
    string comentario;

    if (leerFicheroPixels(nombreFichero, arrayPixels, nPixels)) {

        int mejorNumeroFilas = calcularMejorNumeroFilas(arrayPixels, nPixels);

        if (mejorNumeroFilas != -1) {
            imagen = Imagen(mejorNumeroFilas, nPixels / mejorNumeroFilas, arrayPixels);
            imagen.comentarios += "Creada por: ESTIMACION DE DIMENSIONES";
            comentario = comentario + "Fichero de datos: " + nombreFichero;
            imagen.comentarios += comentario;
        }
    }
    if (arrayPixels)
        delete[] arrayPixels;

    return imagen;
}
