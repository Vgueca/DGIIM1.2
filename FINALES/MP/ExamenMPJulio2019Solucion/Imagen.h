/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imagen.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 2 de julio de 2019, 9:10
 */

#ifndef IMAGEN_H
#define IMAGEN_H

#include "Comentarios.h"
class Imagen;

class Imagen {
public:
    Imagen();
    Imagen(const Imagen& orig);
    virtual ~Imagen();
    Imagen& operator=(const Imagen& orig);
    Imagen(int nfil, int ncol, int v = 0);

    int getNumeroFilas() const {
        return filas;
    }; // Se supone implementado

    int getNumeroColumnas() const {
        return columnas;
    }; // Se supone implementado
    friend std::istream& operator>>(std::istream& flujo, Imagen& imagen);
    friend std::ostream& operator<<(std::ostream& flujo, const Imagen& imagen);
    void clear();
    Imagen(const char* nombreFichero);
    bool guardar(const char* nombreImagen) const;

    const int& operator()(int fil, int col) const;
    int& operator()(int fil, int col);
    friend Imagen operator*(const Imagen& imagen1, const Imagen& imagen2);
    Imagen operator!() const;

    Imagen subImagen(int filaInicial, int columnaInicial, int alto, int ancho) const;
    bool operator>(const Imagen& imagen) const;


    Imagen(int nfil, int ncol, const int* pixels);
    //friend Imagen crearImagenFromArrayPixels(const char* nombreFichero);
    static Imagen crearImagenFromArrayPixels(const char* nombreFichero);
    double calcularValorDistanciaFilas() const;
    
    bool vacia() const;
    const Comentarios & getComentarios () const; // Devuelve una referencia a los comentarios

private:
    int filas, columnas; // PRE: 0 <= filas,columnas 
    // PRE: 0 <= valores[i][j] <= 255 
    // PRE: 0 <= i < filas, 0 <= j < columnas
    int ** valores; // Valores de luminosidad
    Comentarios comentarios;

    void crearImagenVacia();
    void liberarMemoria();
    void reservarMemoria(int nFilas, int nColumnas);
    void copiar(const Imagen& otro);

    double valorMedio() const;
};

std::istream& operator>>(std::istream& flujo, Imagen& imagen);
std::ostream& operator<<(std::ostream& flujo, const Imagen& imagen);
Imagen operator*(const Imagen& imagen1, const Imagen& imagen2);

bool leerFicheroPixels(const char* nombreFichero, int* & arrayPixels, int& nPixels);
int calcularMejorNumeroFilas(const int* arrayPixels, int nPixels);

#endif /* IMAGEN_H */


