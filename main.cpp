#include <iostream>
#include "SequentialFile.h"
using namespace std;

int main(){
    SequentialFile sequentialFile = SequentialFile("datos.dat");
    string codigo, nombre, carrera;
    int ciclo;
    cout << "------------ Pregunta 1: Sequential File ------------" << endl;
    cout << "Agregar un registro" << endl;
    cout << "Ingrese el codigo: ";
    cin >> codigo;
    cout << "Ingrese el nombre: ";
    cin >> nombre;
    cout << "Ingrese la carrera: ";
    cin >> carrera;
    cout << "Ingrese el ciclo: ";
    cin >> ciclo;
    Registro registro = Registro(codigo, nombre, carrera, ciclo);
    cout << registro.codigo << endl;

    //sequentialFile.add(registro);
    return 0;
}