/*
 * Examen Metodología de la Programación (Junio 2017)
 * Curso 2016/2017
 */

/* 
 * File:   RedCiudades.h
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 12 de junio de 2017, 9:38
 */

#ifndef REDCIUDADES_H
#define REDCIUDADES_H

#include <iostream>

struct InfoCiudad{
    char* nombre; // Nombre
    int poblacion; // Num. habs.
};

class RedCiudades {
    int num_ciudades;
    InfoCiudad* info;
    double** distancia;
    
    void liberarMemoria();
    void reservarMemoria(int n);
    void copiar(const RedCiudades & otro);
    
public:
    RedCiudades();
    RedCiudades(const RedCiudades& orig);
    RedCiudades(const char* fichero);
    virtual ~RedCiudades();
    RedCiudades& operator=(const RedCiudades& orig);
    bool estaVacia() const;
    friend std::ostream& operator<<(std::ostream& flujo, const RedCiudades &red);
    friend std::istream& operator>>(std::istream& flujo, RedCiudades &red);
    bool leerRedCiudades(const char* fichero);
    bool escribirRedCiudades(const char* fichero) const;
    int ciudadMejorConectada() const;
    int mejorEscalaEntre(int i, int j) const;
    int getNumCiudades() const {return num_ciudades;};
    double getDistancia(int index1, int index2) const {
        return distancia[index1-1][index2-1];};

private:

};

#endif /* REDCIUDADES_H */

