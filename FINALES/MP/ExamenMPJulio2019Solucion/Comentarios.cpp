/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comentarios.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 2 de julio de 2019, 9:11
 */


#include <iostream>
#include <string>

#include "Comentarios.h"

using namespace std;

Comentarios::Comentarios() : losComentarios(nullptr), numComentarios(0) { // EXAMEN 1.1
}

Comentarios::~Comentarios() { // EXAMEN 1.1
    liberarMemoria();
}

Comentarios::Comentarios(const Comentarios& orig) { // Se supone implementado
    reservarMemoriaDinamica(orig.numComentarios);
    copiar(orig);
}

Comentarios& Comentarios::operator=(const Comentarios& orig) { // Se supone implementado
    if (this != &orig) {
        liberarMemoria();
        reservarMemoriaDinamica(orig.numComentarios);
        copiar(orig);
    }
    return *this;
}

void Comentarios::liberarMemoria() { // Se supone implementado
    //if (losComentarios) {
    delete[] losComentarios;
    losComentarios = nullptr;
    numComentarios = 0;
    //}
}

void Comentarios::reservarMemoriaDinamica(int n) { // Se supone implementado
    if (n > 0) {
        losComentarios = new string[n];
        numComentarios = n;
    } else {
        losComentarios = nullptr;
        numComentarios = 0;
    }
}

void Comentarios::copiar(const Comentarios& otro) { // Se supone implementado
    numComentarios = otro.numComentarios;
    for (int i = 0; i < otro.numComentarios; i++) {
        losComentarios[i] = otro.losComentarios[i];
    }
}

const string& Comentarios::operator[](int index) const { // Se supone implementado
    return losComentarios[index];
}

string& Comentarios::operator[](int index) { // Se supone implementado
    return losComentarios[index];
}

std::ostream& operator<<(std::ostream& flujo, const Comentarios& comentarios) { // Se supone implementado
    for (int i = 0; i < comentarios.getNumeroComentarios(); i++) {
        flujo << comentarios[i] << std::endl;
    }
    return flujo;
}

std::istream& operator>>(std::istream& flujo, Comentarios& comentarios) { // Se supone implementado
    char primerCaracter;
    int i = 0;

    comentarios.liberarMemoria();
    while (flujo && (primerCaracter = flujo.peek()) == '#') {
        comentarios.redimensionar(comentarios.numComentarios + 1);
        getline(flujo, comentarios[i]); //flujo >> comentarios[i];
        i++;
    }

    return flujo;
}

/**
 * 
 * @param n Nuevo tamaño del array de comentarios
 */
void Comentarios::redimensionar(int n) { // EXAMEN 1.2
    string* arrayAuxiliar;
    arrayAuxiliar = new string[n];
    for (int i = 0; i < n && i < numComentarios; i++) {
        arrayAuxiliar[i] = losComentarios[i];
    }
    // if(losComentarios) 
    delete[] losComentarios; // o bien liberarMemoria()
        
    losComentarios = arrayAuxiliar;
    numComentarios=n;
}

Comentarios& Comentarios::operator+=(const string& comentario) { // EXAMEN 1.2
    string nuevoComentario = comentario;
    redimensionar(numComentarios+1);
    if (nuevoComentario.size() > 0) {
        if (nuevoComentario[0] != '#')
            nuevoComentario = '#' + nuevoComentario;
    } else {
        nuevoComentario = "#";
    }
    losComentarios[numComentarios-1] = nuevoComentario; 

    return *this;
}

void Comentarios::clear() {
    liberarMemoria();
}

Comentarios& Comentarios::operator+=(const Comentarios& otros) { // EXAMEN 4.2
    int numeroComentariosAnterior = numComentarios;
    redimensionar(numComentarios+otros.numComentarios);

    for(int i=0; i<otros.numComentarios; i++){
        losComentarios[numeroComentariosAnterior+i] = otros.losComentarios[i];
    }
    return *this;
}