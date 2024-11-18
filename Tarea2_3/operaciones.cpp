//#include <costos.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

// Definición de las matrices globales de costos usando vectores
vector<vector<int>> dp_1;
vector<vector<int>> costo_sustitucion(26, vector<int>(26));
vector<vector<int>> costo_transposicion(26, vector<int>(26));
vector<int> costo_insercion(26);
vector<int> costo_eliminacion(26);


// Función para cargar la matriz de sustitución desde el archivo
void cargar_costo_sustitucion() {
    ifstream archivo("output/cost_sub.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> costo_sustitucion[i][j];
        }
    }
    archivo.close();
}

// Función para cargar la matriz de transposición desde el archivo
void cargar_costo_transposicion() {
    ifstream archivo("output/cost_trans.txt");
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> costo_transposicion[i][j];
        }
    }
    archivo.close();
}

// Función para cargar el arreglo de inserción desde el archivo
void cargar_costo_insercion() {
    ifstream archivo("output/cost_ins.txt");
    for (int i = 0; i < 26; ++i) {
        archivo >> costo_insercion[i];
    }
    archivo.close();
}

// Función para cargar el arreglo de eliminación desde el archivo
void cargar_costo_eliminacion() {
    ifstream archivo("output/cost_del.txt");
    for (int i = 0; i < 26; ++i) {
        archivo >> costo_eliminacion[i];
    }
    archivo.close();
}



int costo_sub(char a, char b){
    int costo;
    int posicion_a = a - 'a';
    int posicion_b = b - 'a';
    //cout << "tuve que hacer sub de la letra " << a << " con la letra " << b << endl;
    costo = min(costo_sustitucion[posicion_b][posicion_a],costo_sustitucion[posicion_a][posicion_b]);   
    return costo;
}

int costo_ins(char b){
    int costo;
    int posicion_b = b - 'a';
    //cout << "tuve que hacer ins de la letra " << b << endl;
    costo = costo_insercion[posicion_b];
    return costo;
    //return 1;
}

int costo_del(char a){
    int costo;
    int posicion_a = a - 'a';
    //cout << "tuve que hacer del de la letra " << a << endl;
    costo = costo_eliminacion[posicion_a];
    return costo;
    //return 1;
}

int costo_trans(char a, char b){
    int costo;
    int posicion_a = a - 'a';
    int posicion_b = b - 'a';
    //cout << "tuve que hacer trans de la letra " << a << " con la letra " << b << endl;
    costo = min(costo_transposicion[posicion_b][posicion_a],costo_transposicion[posicion_a][posicion_b]);
    return costo;
}




// Función de fuerza bruta para Damerau-Levenshtein
int DP(int i, int j, string& s1, string& s2) {
    // Caso base: si una de las cadenas está vacía
    if (i == 0) {
        int costo_total = 0;
        for (int k = 0; k < j; ++k) {
            costo_total += costo_ins(s2[k]);
        }
        return costo_total;
    }

    if (j == 0) {
        int costo_total = 0;
        for (int k = 0; k < i; ++k) {
            costo_total += costo_del(s1[k]);
        }
        return costo_total;
    }

    // Si el resultado ya está calculado, lo devolvemos
    if (dp_1[i][j] != -1) return dp_1[i][j];

    // Calcular el costo mínimo entre las operaciones posibles
    int costo_min = INT_MAX;

    // Sustitución: Si los caracteres son diferentes, calcular el costo
    if (s1[i - 1] != s2[j - 1]) {
        costo_min = min(costo_min, DP(i - 1, j - 1, s1, s2) + costo_sub(s1[i - 1], s2[j - 1]));
    } else {
        costo_min = min(costo_min, DP(i - 1, j - 1, s1, s2));  // No hay costo si son iguales
    }

    // Inserción: Insertar el caracter de s2
    costo_min = min(costo_min, DP(i, j - 1, s1, s2) + costo_ins(s2[j - 1]));

    // Eliminación: Eliminar el caracter de s1
    costo_min = min(costo_min, DP(i - 1, j, s1, s2) + costo_del(s1[i - 1]));

    // Transposición: Verificar si los caracteres adyacentes pueden ser transpuestos
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        costo_min = min(costo_min, DP(i - 2, j - 2, s1, s2) + costo_trans(s1[i - 1], s2[j - 1]));
    }

    // Guardamos el resultado en dp_1 y lo devolvemos
    dp_1[i][j] = costo_min;
    return dp_1[i][j];
}

// Función recursiva de fuerza bruta para calcular el costo mínimo
int fuerza_bruta(int i, int j, string& s1, string& s2) {
    if (i == 0 && j == 0) return 0;
    
    // Caso base: si una de las cadenas está vacía, el costo es insertar o eliminar los caracteres restantes
    if (i == 0) {
        int costo_total = 0;
        for (int k = 0; k < j; ++k) {
            costo_total += costo_ins(s2[k]);  // Insertar los caracteres restantes de s2
        }
        return costo_total;
    }

    if (j == 0) {
        int costo_total = 0;
        for (int k = 0; k < i; ++k) {
            costo_total += costo_del(s1[k]);  // Eliminar los caracteres restantes de s1
        }
        return costo_total;
    }

    // Costo de sustitución si los caracteres son diferentes
    int costo_sustitucion;
    if (s1[i - 1] == s2[j - 1]) {
        costo_sustitucion = 0;
    } else {
        costo_sustitucion = costo_sub(s1[i - 1], s2[j - 1]);
    }
    // Calcular el costo mínimo entre las operaciones posibles
    int costo_min = INT_MAX;

    // Sustitución
    costo_min = min(costo_min, fuerza_bruta(i - 1, j - 1, s1, s2) + costo_sustitucion);

    // Inserción
    costo_min = min(costo_min, fuerza_bruta(i, j - 1, s1, s2) + costo_ins(s2[j - 1]));

    // Eliminación
    costo_min = min(costo_min, fuerza_bruta(i - 1, j, s1, s2) + costo_del(s1[i - 1]));

    // Transposición (si hay al menos dos caracteres en ambas cadenas para hacer el intercambio)
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
        costo_min = min(costo_min, fuerza_bruta(i - 2, j - 2, s1, s2) + costo_trans(s1[i - 2], s1[i - 1]));
    }

    return costo_min;
}


int main(){
    srand(time(nullptr));
    cargar_costo_sustitucion();
    cargar_costo_eliminacion();
    cargar_costo_insercion();
    cargar_costo_transposicion();
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            cout << costo_transposicion[i][j] << " ";
        }
        cout << "\n";
    }   
    string entrada1 = "nfcmaoisetainse";
    string entrada2 = "manifestaciones";
/*
hola, aloh
estas, staes
prueba, ebrapu
salidas, adsilas
palabras, arsbalpa
sencillos, nliossecs
resultados, dtreasosul
fotografias, otfasrigfoa
profesionales, aeslonspoeirf
skibiditoilets, ttilsioikeibds
manifestaciones, nfcmaoisetainse
*/

    dp_1.assign(entrada1.size() + 1, vector<int>(entrada2.size() + 1, -1));
    
    auto start_fuerza_bruta = chrono::high_resolution_clock::now();
    //cout << fuerza_bruta(entrada1.size(), entrada2.size(), entrada1, entrada2) << " fuerza bruta\n";
    auto end_fuerza_bruta = chrono::high_resolution_clock::now();

    auto duration_fuerza_bruta = chrono::duration_cast<chrono::nanoseconds>(end_fuerza_bruta - start_fuerza_bruta);
    cout << "Tiempo de ejecucion fuerza_bruta: " << duration_fuerza_bruta.count() << " ns\n";

    auto start_DP = chrono::high_resolution_clock::now();
    cout << DP(entrada1.size(), entrada2.size(), entrada1, entrada2) << " DP\n";
    auto end_DP = chrono::high_resolution_clock::now();

    auto duration_DP = chrono::duration_cast<chrono::nanoseconds>(end_DP - start_DP);
    cout << "Tiempo de ejecucion DP: " << duration_DP.count() << " ns\n";

    return 0;

    
}   