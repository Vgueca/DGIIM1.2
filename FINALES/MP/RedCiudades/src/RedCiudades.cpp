/*
 * Examen Metodología de la Programación (Junio 2017)
 * Curso 2016/2017
 */

/* 
 * File:   RedCiudades.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 * 
 * Created on 12 de junio de 2017, 9:38
 */

#include <iostream>
#include <fstream>

#include <cstring>


#include "RedCiudades.h"


using namespace std;

// Ejercicio 1.1
RedCiudades::RedCiudades() {
    /*info = 0;
    num_ciudades = 0;
    distancia = 0;*/
    reservarMemoria(0);
}

bool RedCiudades::estaVacia() const{
    return num_ciudades==0;
}

void RedCiudades::liberarMemoria() {
    if (info) {
        for (int i = 0; i < num_ciudades; i++) {
            delete[] info[i].nombre;
        }
        delete[] info;
        info = 0;
    }
    if (distancia) {
        delete[] distancia[0];
        delete[] distancia;
        distancia = 0;
    }
    num_ciudades = 0;
}

// Ejercicio 1.1
RedCiudades::~RedCiudades() {
    liberarMemoria();
}

void RedCiudades::reservarMemoria(int n){
    if(n>0){
        num_ciudades = n;
        info = new InfoCiudad[n];
        for(int i=0; i<n; i++){
            info[i].nombre = 0;
            info[i].poblacion = 0;
        }
        distancia = new double*[n];
        distancia[0] = new double[n*n];
        for(int i=1;i<n; i++){
            distancia[i] = distancia[i-1]+n;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                distancia[i][j] = 0;
            }
        }
    }  
    else{
        info = 0;
        num_ciudades = 0;
        distancia = 0;
    }
}

void RedCiudades::copiar(const RedCiudades& otro){
    num_ciudades=otro.num_ciudades;
    for(int i=0; i<num_ciudades; i++){ // copiar info
        info[i].nombre = new char[strlen(otro.info[i].nombre)+1];
        strcpy(info[i].nombre,otro.info[i].nombre);
        info[i].poblacion = otro.info[i].poblacion;
    }
    for(int i=0; i<num_ciudades; i++){ // copiar distancias
        for(int j=0; j<num_ciudades; j++){
            distancia[i][j]=otro.distancia[i][j];
        }
    }   
}

// Ejercicio 1.2
RedCiudades::RedCiudades(const RedCiudades& orig) {
    reservarMemoria(orig.num_ciudades);
    copiar(orig);
}

// Ejercicio 1.2
RedCiudades& RedCiudades::operator=(const RedCiudades& orig){
    if(this != &orig){
        liberarMemoria();
        reservarMemoria(orig.num_ciudades);
        copiar(orig);
    }
    return *this;
}

//Ejercicio 2.1
std::ostream& operator<<(std::ostream& flujo, const RedCiudades &red){
    flujo << red.num_ciudades << endl;
    
    // Escribir info de ciudades
    for(int i=0; i<red.num_ciudades; i++){ 
        flujo << i+1 << " " << red.info[i].nombre << " " << red.info[i].poblacion 
                << endl;
    }
    
    // Escribir distancia (solo imprimimos las que hay sobre diagonal principal, 
    // pues la matriz es simétrica)
    for(int i=0; i<red.num_ciudades; i++){ 
        for(int j=i+1; j<red.num_ciudades; j++){
            if(red.distancia[i][j] > 0){
                flujo << i+1 << " " << j+1 <<  " " << red.distancia[i][j] << endl;
            }
        }
    }
    
    return flujo;
}

//Ejercicio 2.2
std::istream& operator>>(std::istream& flujo, RedCiudades& red){
    int n;
    const int MAX_CADENA = 100;
    char cadena[MAX_CADENA];
    int numCiudad, poblacion, index1, index2;
    double distancia;
    
    red.liberarMemoria();
	
    flujo >> n; // Leer num. ciudades
    
    red.reservarMemoria(n);

    for(int i=0; i<red.num_ciudades; i++){
        flujo >> numCiudad; 
        flujo >> cadena ;
        red.info[numCiudad-1].nombre = new char[strlen(cadena)+1];
        strcpy (red.info[numCiudad-1].nombre, cadena);
        flujo >> poblacion;
        red.info[numCiudad-1].poblacion=poblacion; 
    }
    
    while(flujo >> index1){
        flujo >> index2;
        flujo >> distancia;
        red.distancia[index1-1][index2-1]=red.distancia[index2-1][index1-1]=distancia;
    }
    
    //flujo.clear();
    
    return flujo;
}

//Ejercicio 3.1
RedCiudades::RedCiudades(const char* fichero): num_ciudades(0), info(0), distancia(0) {
    if(!leerRedCiudades(fichero)){
        cerr << "RedCiudades(const char* fichero): ERROR, no puede abrir " << fichero << endl;
        exit(1);
    }
}

//Ejercicio 3.2
bool RedCiudades::leerRedCiudades (const char* fichero){
    ifstream flujo(fichero);
    if(!flujo){
	return false;
    }
    const int MAX_CADENA = 100;
    char cadena[MAX_CADENA];
    flujo.getline(cadena, MAX_CADENA);	// Lectura cadena mágica

    if (!strcmp(cadena, "RED")) {
	flujo >> (*this);
    } 

    flujo.close();
    return true;
}

//Ejercicio 3.3
bool RedCiudades::escribirRedCiudades (const char* fichero) const{
    ofstream flujo(fichero);
    if(!flujo){
	return false; 
    }
    flujo << "Red" << endl;
    flujo << *this;
    if(flujo)
        return true;
    else
        return false;
}

// Ejercicio 4.1
int RedCiudades::ciudadMejorConectada() const{
    int max=-1;
    int contadorCiudadesConectadasActual, maxCiudadesConectas;
    for(int i=0; i<num_ciudades; i++){
        contadorCiudadesConectadasActual=0;
        for(int j=0; j<num_ciudades; j++){
            if(distancia[i][j]>0){
                contadorCiudadesConectadasActual++;
            }
        }
        if ((max<0) || (contadorCiudadesConectadasActual>maxCiudadesConectas)){
            max = i;
            maxCiudadesConectas = contadorCiudadesConectadasActual;
        }
    }
    return max+1;
}

// Ejercicio 4.2
int RedCiudades::mejorEscalaEntre(int i, int j) const{
    int dist1, dist2;
    double min_dist=-1;
    int mejorCiudad=-1;
    
    for(int z=0; z<num_ciudades; z++){
        dist1 = distancia[i-1][z];
        dist2 = distancia[z][j-1];
        if((dist1>0) && (dist2>0)){
            if((min_dist<0)||(dist1+dist2 < min_dist)){
                min_dist = dist1+dist2;
                mejorCiudad = z;
            }
        }
    }
    return mejorCiudad+1;
}



