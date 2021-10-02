#include <iostream>
#include "SequentialFile.h"
using namespace std;

int main(){
    SequentialFile sequentialFile = SequentialFile("datos.dat");
    Registro registro;
    registro.setData();
    sequentialFile.add(registro);
    return 0;
}