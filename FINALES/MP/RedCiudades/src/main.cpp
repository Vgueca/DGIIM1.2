/*
 * Examen Metodología de la Programación (Junio 2017)
 * Curso 2016/2017
 */

/* 
 * File:   main.cpp
 * Author: Andrés Cano Utrera <acu@decsai.ugr.es>
 *
 * Created on 12 de junio de 2017, 9:29
 */

#include <cstdlib>
#include "RedCiudades.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    RedCiudades red;
    
    if(argc<3){
        cerr<< "Error. Ejecutar con: main NombreFicheroRedEntrada NombreFicheroRedSalida < RedGranada.cin" ;
        exit(1);
    }
    
    cout << "RED VACÍA:" << endl;
    cout << red;
    
    // Probando operator>>
    cout << "INTRODUCE DATOS DE red:";
    cin >> red;
    
    // Probando operator<<
    cout << "\nRED LEÍDA DE cin:" << endl;
    cout << red;
    
    // Probando constructor de copia
    RedCiudades red4(red);
    cout << "\nRED CREADA CON CONSTRUCTOR COPIA "  << endl;  
    cout << red4;  
    
    // Probando operador asignación
    red4 = red;
    cout << "\nRED CREADA CON OPERADOR ASIGNACIÓN "  << endl;  
    cout << red4;  
    

    
    // Probando constructor RedCiudades(const char* fichero)
    RedCiudades red2(argv[1]);
    cout << "\nRED LEÍDA DE " << argv[1] << endl;  
    cout << red2;
    
    // Probando método LeerRedCiudades (const char* fichero)
    RedCiudades red3;
    red3.leerRedCiudades(argv[1]);
    cout << "\nRED LEÍDA DE " << argv[1] << " usando LeerRedCiudades()" << endl;  
    cout << red3;  
    
    // Probando método EscribirRedCiudades (const char* fichero)
    red3.escribirRedCiudades(argv[2]);
    cout << "\nRED SALVADA EN " << argv[2] << " usando EscribirRedCiudades()" << endl;  
    
    // Probando método CiudadMejorConectada())
    cout << "Indice de la ciudad mejor conectada " << red3.ciudadMejorConectada() << endl;
    
    // Probando método MejorEscalaEntre(int i, int j)
    cout << "Indice de la ciudad Mejor Escala Entre 2 y 5 (red ejemplo del examen): " << red.mejorEscalaEntre(2,5) << endl;
    
    
    // Ejercicio 5
    for(int i=1; i<=red2.getNumCiudades(); i++){
        for(int j=1; j<=red2.getNumCiudades(); j++){
            if(red2.getDistancia(i,j)==0 && i!=j){ // Si no están directamente conectadas
                int z=red2.mejorEscalaEntre(i,j);
                if(z>=0){
                    cout << "La mejor escala entre " << i << " y " << j << 
                            " es la ciudad " << z << endl;
                }
                else{
                    cout << "No hay escala de una sola ciudad entre " << i 
                            << " y " << j << endl;
                }
            }
        }
    }
        
    return 0;
}

