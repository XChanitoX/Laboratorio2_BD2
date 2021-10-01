#include <iostream>
#include "SequentialFile.h"
using namespace std;

int main(){
    SequentialFile sequentialFile = SequentialFile("datos.dat");

    cout << "------------ Pregunta 1: Sequential File ------------" << endl;

    Registro registro = Registro();
    registro.ingresarDatosRegistro();
    registro.imprimirDatosRegistro();

    return 0;
}