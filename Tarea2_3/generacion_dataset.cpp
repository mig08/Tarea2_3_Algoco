#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>


using namespace std;
// Función para generar un costo aleatorio entre 1 y 5
int generar_costo() {
    return rand() % 5 + 1;
}

// Función para generar y guardar la matriz de sustitución en un archivo
void guardar_costo_sustitucion() {
    ofstream archivo("cost_sub.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            int costo = (i == j) ? 0 : generar_costo();
            archivo << costo << " ";
        }
        archivo << "\n";
    }
    archivo.close();
}

// Función para generar y guardar la matriz de transposición en un archivo
void guardar_costo_transposicion() {
    ofstream archivo("cost_trans.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            int costo = (i == j) ? 0 : generar_costo();
            archivo << costo << " ";
        }
        archivo << "\n";
    }
    archivo.close();
}

// Función para generar y guardar el arreglo de inserción en un archivo
void guardar_costo_insercion() {
    ofstream archivo("cost_ins.txt");
    for (int i = 0; i < 26; ++i) {
        int costo = generar_costo();
        archivo << costo << " ";
    }
    archivo << "\n";
    archivo.close();
}

// Función para generar y guardar el arreglo de eliminación en un archivo
void guardar_costo_eliminacion() {
    ofstream archivo("cost_del.txt");
    for (int i = 0; i < 26; ++i) {
        int costo = generar_costo();
        archivo << costo << " ";
    }
    archivo << "\n";
    archivo.close();
}

void palabras() {
    ofstream archivo("palabras.txt");
    archivo << "hola, aloh"<< endl;
    archivo << "estas, staes"<< endl;
    archivo << "prueba, ebrapu"<< endl;
    archivo << "salidas, adsilas"<< endl;
    archivo << "palabras, arsbalpa"<< endl;
    archivo << "sencillos, nliossecs"<< endl;
    archivo << "resultados, dtreasosul"<< endl;
    archivo << "fotografias, otfasrigfoa"<< endl;
    archivo << "profesionales, aeslonspoeirf"<< endl;
    archivo << "skibiditoilets, ttilsioikeibds"<< endl;
    archivo << "manifestaciones, nfcmaoisetainse"<< endl;
    archivo.close();
}


int main(){
    srand(time(nullptr));
    guardar_costo_sustitucion();
    guardar_costo_eliminacion();
    guardar_costo_insercion();
    guardar_costo_transposicion();
    palabras();
    return 0;
}