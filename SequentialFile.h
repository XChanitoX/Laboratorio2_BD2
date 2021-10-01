#ifndef LABORATORIO2_BD2_SEQUENTIALFILE_H
#define LABORATORIO2_BD2_SEQUENTIALFILE_H

#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

struct Registro{
    char codigo [5];
    char nombre [20];
    char carrera [15];
    int ciclo;

    void ingresarDatosRegistro() {
        std::string nombre_, codigo_, carrera_, ciclo_;
        std::cout << "Agregando un registro..." << std::endl;
        std::cout << "Ingrese el codigo: \n";
        std::cin >> codigo_;
        strcpy(codigo,codigo_.c_str());
        std::cout << "Ingrese el nombre: \n";
        std::cin >> nombre_;
        strcpy(nombre,nombre_.c_str());
        std::cout << "Ingrese la carrera: \n";
        std::cin >> carrera_;
        strcpy(carrera,carrera_.c_str());
        std::cout << "Ingrese el ciclo: \n";
        std::cin >> ciclo;
    }

    void imprimirDatosRegistro(){
        std::cout << "Imprimiendo registro: \n";
        std::cout << "Codigo: " << codigo << "\n";
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Carrera: " << carrera << "\n";
        std::cout << "Ciclo: " << ciclo << "\n";
    }

};

class SequentialFile{
private:
    std::string fileName;
    std::string auxFileName;
    //std::vector<Registro> registros;
public:
    SequentialFile(std::string fileName_) {
        fileName = fileName_;
        auxFileName = "aux.dat";
    }

    void ordenarRegistros(std::vector<Registro> &registros){
        for (int i = 0; i < registros.size()-1; i++) {
            for (int j = 0; j < registros.size()-i-1; j++) {
                if (registros[j].nombre < registros[i+1].nombre){
                    Registro aux = Registro();
                    aux = registros[j];
                    registros[j] = registros[j+1];
                    registros[j+1] = aux;
                }
            }
        }
    }

    void insertAll(std::vector<Registro> registros){
        std::fstream FileOut;
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