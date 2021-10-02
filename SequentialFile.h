#ifndef LABORATORIO2_BD2_SEQUENTIALFILE_H
#define LABORATORIO2_BD2_SEQUENTIALFILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Registro
{
    char codigo [5]{' '};
    char nombre [20]{' '};
    char carrera [15]{' '};
    int ciclo;
    int dir=-1;
    char file = 'd';

    void setData(){
        cout<<"Codigo: ";
        cin>>codigo;
        cout<<"Nombre: ";
        cin>>nombre;
        cout<<"Carrera: ";
        cin>>carrera;
        cout<<"Ciclo: ";
        cin>>ciclo;
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
        int num = numRecords(dataFile)-1;
        return (num == binarySearch(registro));
    }

    int numRecords(string file){
        size_t lengthRecord = sizeof(Registro)-2;
        ifstream inFile;
        inFile.open(file,ios::app|ios::binary);
        if(!inFile.is_open()){
            throw new exception(); /// Mejorar throw
        }
        inFile.seekg(0,ios::end);
        int byteEnd = inFile.tellg();
        int numRecords = byteEnd/ lengthRecord; //Obtenemos la cantidad total de registros
        inFile.close();
        return numRecords;
    }
    void write(string fileName, Registro record){
        ofstream outFile;
        string ciclo, dir;

        outFile.open(fileName,ios::app|ios::binary);

        if(!outFile.is_open()){
            throw new exception;
        }
        outFile.flush();
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
        outFile.flush();
        outFile.close();
    }

    void write(string fileName, int pos, Registro record){
        ofstream outFile;
        string ciclo, dir;
        size_t lengthRecord = sizeof(Registro)-2;

        outFile.open(fileName,ios::app|ios::binary);

        if(!outFile.is_open()){
            throw new exception;
        }

        outFile.flush();
        outFile.seekp(pos*lengthRecord);
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
        outFile.flush();
        outFile.close();
    }

public:
    SequentialFile(string file){
        this->dataFile=file;
    }

    void add(Registro record){

        int pos = binarySearch(record);
        size_t lengthRecord = sizeof(Registro)-2;

        if(numRecords(dataFile)==0){
           ofstream outFile(dataFile, ios::app|ios::binary);
           write(dataFile,record);
           outFile.close();
           return;
        }

        Registro registro;
        ifstream inFile(dataFile, ios::binary | ios::app);
        if(!inFile.is_open()){
            throw new exception;
        }

        inFile.seekg(pos*lengthRecord);
        inFile.read((char*)&registro.codigo, sizeof(registro.codigo));
        inFile.read((char*)&registro.nombre, sizeof(registro.nombre));
        inFile.read((char*)&registro.carrera, sizeof(registro.carrera));
        char ciclo[4], dir[4];
        inFile.read((char*)&ciclo, sizeof(registro.codigo));
        int byte = inFile.tellg();
        inFile.seekg(--byte);
        inFile.read((char*)&dir, sizeof(registro.dir));
        registro.ciclo = stoi(ciclo);
        registro.dir = (dir[0] =='-')?(-1):stoi(dir);
        inFile.read((char*)&registro.file, sizeof(char));
        inFile.close();

        ofstream outFile;
        bool isEndFileData = isEnd(record);
        string fileName;
        if(isEndFileData){ //Solo si debemos agregar el registro al final
            fileName = dataFile;
            record.dir = -1;
        }
        else{
            fileName = auxFileName;
            record.file = 'a';
            record.dir = registro.dir;
        }

        write(fileName, record);

        if(isEndFileData)
            registro.dir = numRecords(fileName);
        else
            registro.dir = numRecords(fileName)-1;

        write(dataFile,pos,registro);
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
                return num-1;
        }
    }

};

#endif //LABORATORIO2_BD2_SEQUENTIALFILE_H