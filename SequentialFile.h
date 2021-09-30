#ifndef LABORATORIO2_BD2_SEQUENTIALFILE_H
#define LABORATORIO2_BD2_SEQUENTIALFILE_H

#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

struct Registro{
    char codigo [40];
    char nombre [20];
    char carrera [15];
    int ciclo;

    Registro(string codigo_, string nombre_, string carrera_, int ciclo_){
        strcpy(codigo,codigo_.c_str());
        strcpy(nombre,nombre_.c_str());
        strcpy(carrera,carrera_.c_str());
        ciclo = ciclo_;
    }
};

class SequentialFile{
private:
    string fileName;
    vector<Registro> registros;
public:
    SequentialFile(string fileName_) {
        fileName = fileName_;
    }

    void insertAll(vector<Registro> registros){

    }
/*
    void add(Registro registro){
        ofstream fout(fileName, ios::app|ios::binary);
        if(!fout){
            cerr << "No se pudo abrir el archivo" << endl;
            exit(EXIT_FAILURE);
        }

        string lastRegister = registros.back().codigo;
        if(lastRegister){

        }

        fout << registro.codigo << ' ' << registro.nombre << registro.carrera << ' ' << registro.ciclo;
        fout.close();
    }

    Registro search(string key){
        Registro registro = Registro();

        return registro;
    }

    vector<Registro> rangeSearch(string begin, string end){

    }
*/
};

#endif //LABORATORIO2_BD2_SEQUENTIALFILE_H