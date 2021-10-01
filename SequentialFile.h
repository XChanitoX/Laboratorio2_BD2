#ifndef LABORATORIO2_BD2_SEQUENTIALFILE_H
#define LABORATORIO2_BD2_SEQUENTIALFILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Registro
{
    char codigo [5];
    char nombre [20];
    char carrera [15];
    int ciclo;
    int dir=-1;
    char file = 'd';

    void setData(){
        cout<<"Codigo: ";cin>>codigo;
        cout<<"Nombre: ";cin>>nombre;
        cout<<"Carrera: ";cin>>carrera;
        cout<<"Ciclo: ";cin>>ciclo;
    }

    void show() {
        cout << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Carrera: " << carrera << endl;
        cout << "Ciclo: " << ciclo << endl;
    }
};

class SequentialFile{
private:
    string dataFile;
    string auxFileName="aux.dat";

    int binarySearch(string codigo,int begin, int end){
        int medio = (end + begin)/2;
        size_t lengthRecord = sizeof(Registro)-2;
        /// Abrimos el file para leer y comparar si el codigo pertenece a uno de los extremos
        ifstream inFile;
        inFile.open(dataFile, ios::app | ios::binary);

        inFile.seekg(begin);

        Registro registro;
        inFile.seekg(medio*lengthRecord); //Nos posicionamos al inicio del registro que queremos leer
        inFile.read((char *)&registro.codigo, sizeof(registro.codigo)); //Leemos solo el key del registro
        string key = registro.codigo;
        inFile.close();

        if(medio == begin)
            return medio;

        if (key < codigo)
            return binarySearch(codigo, medio,end);

        else if(key > codigo)
            return binarySearch(codigo, begin, medio);

    }

    bool isEnd(Registro registro){
        int num = numRecords(dataFile);
        return (num == binarySearch(registro));
    }

    int numRecords(string file){
        size_t lengthRecord = sizeof(Registro)-2;
        ofstream outFile;
        outFile.open(file,ios::app|ios::binary);
        if(!outFile.is_open()){
            throw new exception(); /// Mejorar throw
        }
        int numRecords = outFile.tellp()/ lengthRecord; //Obtenemos la cantidad total de registros
        outFile.close();
        return numRecords;
    }

public:
    SequentialFile(string file){
        this->dataFile=file;
    }

    void add(Registro record){

        int pos = binarySearch(record);
        size_t lengthRecord = sizeof(Registro)-2;

        Registro registro;
        ifstream inFile(dataFile, ios::binary | ios::app);
        if(!inFile.is_open()){
            throw new exception;
        }
        if()
            inFile.seekg(pos*lengthRecord);
        inFile.read((char*)&registro.codigo, sizeof(registro.codigo));
        inFile.read((char*)&registro.carrera, sizeof(registro.nombre));
        inFile.read((char*)&registro.carrera, sizeof(registro.carrera));
        string ciclo, dir;
        inFile.read((char*)&ciclo, sizeof(int));
        inFile.read((char*)&dir, sizeof(int));
        registro.ciclo = atoi(ciclo.c_str());
        record.dir = atoi(dir.c_str());
        inFile.read((char*)&registro.file, sizeof(char));
        inFile.close();

        ofstream outFile;
        bool isEndFileData = isEnd(record);
        string file;
        if(isEndFileData){ //Solo si debemos agregar el registro al final
            file = dataFile;
        }
        else{
            file = auxFileName;
            record.file = 'a';
            record.dir = registro.dir;
        }

        outFile.open(file,ios::app|ios::binary);

        if(!outFile.is_open()){
            throw new exception;
        }


        int i = 0;
        while (record.codigo[i] != '\0') { outFile << record.codigo[i]; ++i;}
        for (; i < 5; i++) outFile << ' ';
        i = 0;
        while (record.nombre[i] != '\0') { outFile << record.nombre[i]; ++i;}
        for (; i < 20; i++) outFile << ' ' ;
        i = 0;
        while (record.carrera[i] != '\0') { outFile << record.carrera[i]; ++i;}
        for (; i < 15; i++) outFile << ' ';

        i = 0;
        ciclo = to_string(record.ciclo);
        while (ciclo[i] != '\0') { outFile << ciclo[i]; ++i;}
        for (; i < 4; i++) outFile << ' ';

        i = 0;
        dir = to_string(record.dir);
        while (dir[i] != '\0') { outFile << dir[i]; ++i;}
        for (; i < 4; i++) outFile << " ";

        outFile<<record.file;
        outFile<<'\n';
        outFile.close();

        if(isEndFileData)
            registro.dir = numRecords(file)+1;
        else
            registro.dir = numRecords(file);

        outFile.open(dataFile,ios::app|ios::binary);

        if(!outFile.is_open()){
            throw new exception;
        }

        outFile.seekp(pos*lengthRecord);
        i = 0;
        while (registro.codigo[i] != '\0') { outFile << registro.codigo[i]; ++i;}
        for (; i < 5; i++) outFile << ' ';
        i = 0;
        while (registro.nombre[i] != '\0') { outFile << registro.nombre[i]; ++i;}
        for (; i < 20; i++) outFile << ' ' ;
        i = 0;
        while (registro.carrera[i] != '\0') { outFile << registro.carrera[i]; ++i;}
        for (; i < 15; i++) outFile << ' ';

        i = 0;
        ciclo = to_string(registro.ciclo);
        while (ciclo[i] != '\0') { outFile << ciclo[i]; ++i;}
        for (; i < 4; i++) outFile << ' ';

        i = 0;
        dir = to_string(registro.dir);
        while (dir[i] != '\0') { outFile << dir[i]; ++i;}
        for (; i < 4; i++) outFile << " ";

        outFile<<registro.file;
        outFile<<'\n';
        outFile.close();

    }

    void load(){
        ifstream inFile;
        inFile.open(dataFile, ios::app | ios::binary);

        while(!inFile.eof()){
            Registro registro;
            inFile.read((char *) reinterpret_cast<const Registro *>(&registro), sizeof(Registro));
            registro.show();
        }
        inFile.close();
    }

    void ordenarRegistros(std::vector<Registro> &registros){
        for (int i = 0; i < registros.size()-1; i++) {
            for (int j = 0; j < registros.size()-i-1; j++) {
                if (registros[j].codigo < registros[i+1].codigo){
                    Registro aux;
                    aux = registros[j];
                    registros[j] = registros[j+1];
                    registros[j+1] = aux;
                }
            }
        }
    }

    int binarySearch(Registro record){
        string key = record.codigo; // LLave primaria del registro
        size_t lengthRecord = sizeof(Registro)-2; // Tamanho de un registro

        //Manejo de archivo
        int num = numRecords(dataFile);

        /// Abrimos el file para leer y comparar si el codigo pertenece a uno de los extremos
        ifstream inFile(dataFile, ios::app | ios::binary);
        if(!inFile.is_open()){
            throw new exception(); /// Mejorar throw
        }

        ///Comparando con el inicio
        char begin[5],end[5];
        inFile.seekg(0* lengthRecord); //Nos colocamos al inicio del archivo
        inFile.read((char*)&begin, sizeof(record.codigo)); //
        inFile.seekg((num-1)* lengthRecord);
        inFile.read((char*)&end, sizeof(record.codigo));

        inFile.close();

        if(begin<key&&end>key){
            return binarySearch(record.codigo,0,num-1);
        }
        else{
            if(begin>key)
                return -1;
            else
                return num;
        }
    }

};

#endif //LABORATORIO2_BD2_SEQUENTIALFILE_H