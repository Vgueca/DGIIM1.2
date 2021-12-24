/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comentarios.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 2 de julio de 2019, 9:11
 */

#ifndef COMENTARIOS_H
#define COMENTARIOS_H

#include <string>

class Comentarios {
public:
    Comentarios(); 
    Comentarios(const Comentarios& orig);
    virtual ~Comentarios();
    Comentarios& operator=(const Comentarios& orig);
    
    int getNumeroComentarios() const {return numComentarios;}; // Se supone implementado
    
    
    const std::string& operator[](int index) const;
    std::string& operator[](int index);
    void redimensionar(int n);

    
    Comentarios& operator+=(const std::string& comentario);
    Comentarios& operator+=(const Comentarios& otros);

    void clear();
    
private:
    int numComentarios; // PRE: 0 <= num_comentarios
    std::string * losComentarios;
    
    void liberarMemoria();
    void reservarMemoriaDinamica(int n);
    void copiar(const Comentarios& otro);
    
    friend std::istream& operator>>(std::istream& flujo, Comentarios& comentarios);

};

std::ostream& operator<<(std::ostream& flujo, const Comentarios& comentarios);
std::istream& operator>>(std::istream& flujo, Comentarios& comentarios);

#endif /* COMENTARIOS_H */

