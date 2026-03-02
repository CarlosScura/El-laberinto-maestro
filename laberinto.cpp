#include <iostream>
#include <vector>
#include <chrono>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// Creamos las cosntrantes para el laberinto.

const char MURO = '#';
const char CAMINO = '*';
const char SOLUCION = 'o';

// creamos la funcion para inicializar el labertinto y lo llenamos de muros.

void ini_laberinto(vector<vector<char>>& laberinto){
    for(int i = 0; i < laberinto.size(); i++){
    
        for(int j = 0; j < laberinto[i].size(); j++){
            laberinto[i][j] = MURO;
        }
    }
}

// creamos la fucnion para mostrar el laberitno en la terminal.

void mostrar_laberinto(const vector<vector<char>>& laberinto){
    for(int i = 0; i < laberinto.size(); i++){
    
        for(int j = 0; j < laberinto[i].size(); j++){
            cout << laberinto[i][j] << ' '; // si no se pone el espacio sale feo :(
        }
        cout << endl;
    }
}

// creamos la funcion para generar el laberinto.

void generar_laberinto(vector<vector<char>>& laberinto,int fila, int columna){
    laberinto[fila][columna] = CAMINO;

    // creamos el array     arriba,  abajo,  izq,   derecha 
    int direcciones[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    // generamos el camino con un for.
    for(int i = 0; i < 4; i++) {
        int r = rand() % 4; // numero al azar del 0 al 3
        
        int nf = fila + direcciones[r][0];
        int nc = columna + direcciones[r][1];

        if (nf >= 0 && nf < laberinto.size() &&
            nc >= 0 && nc < laberinto[0].size()) {

            if (laberinto[nf][nc] == MURO) {
                generar_laberinto(laberinto,nf,nc);
            }
        }
    }
}

/*
// Nodo para BFS.
struct Nodo{int fila; int columna;};
*/

// Iniciamos la funcion main

int main(){
    // Iniciamos la aleatoriedad.
    srand(time(0));

    int fila = 10;
    int columna = 10;

    vector<vector<char>> laberinto(fila, vector<char>(columna));

    ini_laberinto(laberinto);

    generar_laberinto(laberinto, 0,0);

    mostrar_laberinto(laberinto);

    //return 0;
}