#include <iostream>
#include <vector>
#include <chrono>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// Creamos las cosntrantes para el laberinto

const char MURO = '#';
const char CAMINO = '*';
const char SOLUCION = '.';

// creamos la funcion para inicializar el labertinto y lo llenamos de muros

void ini_laberinto(vector<vector<char>>& laberinto){
    for(int i = 0; i < laberinto.size(); i++){
    
        for(int j = 0; j < laberinto[i].size(); j++){
            laberinto[i][j] = MURO;
        }
    }
}

// creamos la fucnion para mostrar el laberitno en la terminal

void mostrar_laberinto(const vector<vector<char>>& laberinto){
    for(int i = 0; i < laberinto.size(); i++){
    
        for(int j = 0; j < laberinto[i].size(); j++){
            cout << laberinto[i][j] << ' '; // si no se pone el espacio sale feo :(
        }
        cout << endl;
    }
}

// creamos la funcion para generar el laberinto

void generar_laberinto(vector<vector<char>>& laberinto,int fila, int columna){
    laberinto[fila][columna] = CAMINO;

    // creamos el array     arriba,  abajo,  izq,   derecha 
    // tenemos direcciones de 2 en 2 para los saltos al romper los muros.
    int direcciones[4][2] = {{-2,0}, {2,0}, {0,-2}, {0,2}};
    
    // generamos el camino con un for.
    for(int i = 0; i < 4; i++) {
        int r = rand() % 4; // numero al azar del 0 al 3
        swap(direcciones[i], direcciones[r]); // intercambia las direcciones
    }

    for(int i = 0; i < 4; i++){
        int nf = fila + direcciones[i][0];
        int nc = columna + direcciones[i][1];

        if (nf >= 0 && nf < laberinto.size() -1 &&
            nc >= 0 && nc < laberinto[0].size() -1) {

            if (laberinto[nf][nc] == MURO) {
                int muro_f = fila + direcciones[i][0]/2;
                int muro_c = columna + direcciones[i][1]/2;
                laberinto[muro_f][muro_c] = CAMINO;
                generar_laberinto(laberinto,nf,nc);
            }
        }
    }
}

// creamos un nodo para BFS
struct Nodo{int fila; int columna;};

// creamos la funcion resolver laberinto

bool resolver_laberinto(vector<vector<char>>& laberinto){
    // creamos la cola de control para el BFS
    queue<Nodo> cola;

    // creamos el vertor de visitados
    vector<vector<bool>> visitados(
        laberinto.size(),
        vector<bool>(laberinto[0].size(),false)
    );

    // creamos el vector de padres
    vector<vector<Nodo>> padre( 
        laberinto.size(), 
        vector<Nodo>(laberinto[0].size())
    );

    // creamos el array     arriba,  abajo,  izq,   derecha 
    int direcciones[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    // iniciamos el BFS (busqueda en amplitud)
    cola.push({1,1});
    visitados[1][1] = 1;

    // mientras la cola no esté vacia
    while (!cola.empty()){
        // tomamos el nodo actual
        Nodo actual = cola.front();
        cola.pop();
        
        // si es la salida reconstruimos el camino de vuelta y termina
        if (actual.fila == laberinto.size() -2 && actual.columna == laberinto[0].size() -2 ){
            
            int f = actual.fila;
            int c = actual.columna;

            while (!(f == 1 && c == 1)){
                laberinto[f][c] = SOLUCION;
                Nodo p = padre[f][c];
                f= p.fila;
                c= p.columna;
            }

            laberinto [1][1] = SOLUCION;
            return 1;
        }

        // controlamos todas las casillas vecinas
        for(int i = 0; i < 4; i++) {
        
            int nf = actual.fila + direcciones[i][0];
            int nc = actual.columna + direcciones[i][1];
            // si está dentro del mapa
            if (nf >= 0 && nf < laberinto.size() &&
                nc >= 0 && nc < laberinto[0].size()) {
                // si no fue visitado y no es camino lo agregamos a la cola de visitados
                if (!visitados[nf][nc] && laberinto[nf][nc] == CAMINO) {
                    visitados[nf][nc] = 1;
                    padre[nf][nc] = actual; // el padre del siguiente es el actual
                    cola.push({nf,nc});
                }
            }
        }
    }
    return 0;
}

// Iniciamos la funcion main

int main(){
    // Iniciamos la aleatoriedad
    srand(time(0));

    int fila =0 , columna;
    
    while (fila < 10){
        cout << "Ingresa el tamano del laberinto por favor, minimo 10: \n";
        cin >> fila;
    }
    
    // lo hacemos impar
    if (fila % 2 == 0) fila++;
    
    columna = fila;

    // creamos el vector bidimensional char.
    vector<vector<char>> laberinto(fila, vector<char>(columna));

    ini_laberinto(laberinto);

    generar_laberinto(laberinto, 1,1);

    // transformamos la entrada y la salida en caminos
    laberinto[1][1] = CAMINO;
    laberinto[fila-2][columna-2] = CAMINO;

    // si la salida se queda aislada
    if (laberinto[fila-2][columna-3] == MURO){  
        laberinto[fila-2][columna-3] = CAMINO;
    }

    cout << "\nLaberinto generado.\n";
    mostrar_laberinto(laberinto);

    // iniciamos el chronometro
    auto inicio = chrono::high_resolution_clock::now();

    if (resolver_laberinto(laberinto)){
        cout << "Salida encontrada\n";
    } else { 
        cout << "No hay salida\n";
    }

    // finalizamos el cronometro.
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duracion = fin - inicio;

    cout << "\nTiempo: " << duracion.count() << " ms\n";
    
    laberinto[1][1] = 'E';
    laberinto[fila-2][columna-2] = 'S';

    cout << "\nSolucion.\n";
    mostrar_laberinto(laberinto);
}