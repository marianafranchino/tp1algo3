#include <iostream>
#include<vector>
using namespace std;

bool chequearDiag(vector<vector<int>> M, int magico){
    int n=M.size();
    int i=0;
    int suma1=0;
    int suma2=0;
    while(i<n){
        suma1=suma1+M[i][i];
        suma2=suma2+M[i][n-1-i];
        i++;
    }
    return((suma1==magico)&&(suma2==magico));
}

bool filaMagica(vector<vector<int>> M,int fila, int magico, int n){
    int suma = 0;
    for(int k = 0; k < n; k++){
        suma = suma + M[fila][k];
    }
    return(suma == magico);
}

bool columnaMagica(vector<vector<int>> M,int columna, int magico, int n){
    int suma = 0;
    for(int k = 0; k < n; k++){
        suma = suma + M[k][columna];
    }
    return(suma == magico);
}

bool filaNoSeExcede(vector<vector<int>> M,int fila, int magico, int columna){
    int suma = 0;
    for(int k = 0; k < columna; k++){
        suma = suma + M[fila][k];
    }
    return(suma < magico);
}

bool columnaNoSeExcede(vector<vector<int>> M,int columna, int magico, int fila){
    int suma = 0;
    for(int k = 0; k < fila; k++){
        suma = suma + M[k][columna];
    }
    return(suma < magico);
}

int cuantosMagicos(int n, vector<vector<int>> M, int i, int j, vector<int> restantes) {

    int magico = (n * (n * n + 1)) / 2;

    if ((i == n) && (j == n)) {//cuando llegué al final, chequeo las diagonales
        if (chequearDiag(M,magico) && filaMagica(M,i-1,magico,n) && columnaMagica(M,j-1,magico,n)){
            return 1;
        } else {
            return 0;
        }
    } else {
        //si estamos al final de una fila pero no al final de una columna
        int suma = 0;
        if (i == n - 1 && j != n - 1) {
            //ponemos el ultimo del renglon
            //chequeamos si la fila es mágica y columnas no se excede
            //si es mágica llamamos a la funcion
            for (int k = 0; k<restantes.size(); k++) {
                //pongo el restante
                int restante = restantes[k];
                vector<vector<int>> matrizActual = M;
                matrizActual[i][j] = restante;
                //chequeo si la fila es Mágica
                if (filaMagica(matrizActual, i, magico,n) && columnaNoSeExcede(matrizActual, j, magico,i)) {
                    vector<int> restantesAux = restantes;
                    restantesAux.erase(restantesAux.begin() + k);
                    suma = suma + cuantosMagicos(n, matrizActual, i + 1, 0, restantesAux);
                }
            }
        }
            //si estamos al final de una columna pero no al final de la fila
        else if (j == n - 1 && i != n - 1 ) {
            //ponemos un restante
            //vemos si la columna es mágica y si la fila no se excede
            //si se cumplen las dos cosas llamo a la function
            for (int k = 0; k<restantes.size(); k++) {
                //pongo el restante
                int restante = restantes[k];
                vector<vector<int>> matrizActual = M;
                matrizActual[i][j] = restante;
                if (columnaMagica(matrizActual, j, magico,n) && filaNoSeExcede(matrizActual, i, magico,j)) {
                    vector<int> restantesAux = restantes;
                    restantesAux.erase(restantesAux.begin() + k);
                    suma = suma + cuantosMagicos(n, matrizActual, i, j+1, restantesAux);
                }
            }
        }
            // si estamos al final detodo
        else if (i == n - 1 && j == n - 1) {
            //ponemos el restante que queda y despues la recursion se ocupa de chequear si funciona o no
            vector<vector<int>> matrizActual = M;
            matrizActual[i][j] = restantes[0];
            suma = suma + cuantosMagicos(n, matrizActual, n, n, restantes);
            //no hace falta modificar restantes porque de todas maneras no lo voy a usar

        }
            //estamos "en el medio"
        else {
            for (int k = 0; k<restantes.size(); k++) {
                //pongo el restante
                int restante = restantes[k];
                vector<vector<int>> matrizActual = M;
                matrizActual[i][j] = restante;
                //chequeo si la fila es Mágica
                if (filaNoSeExcede(matrizActual, i, magico,j) && columnaNoSeExcede(matrizActual, j, magico,i)) {
                    vector<int> restantesAux = restantes;
                    restantesAux.erase(restantesAux.begin() + k);
                    suma = suma + cuantosMagicos(n, matrizActual, i, j + 1, restantesAux);
                }

            }
        }

        return (suma);
    }
}

int main() {
    int n = 3;  // Input for n
    int nummagico = (n * (n * n + 1)) / 2 ;
    vector<vector<int>> matriz = {
            {1, 4, 9},
            {0, 0, 0},
            {0, 0, 0}
    };

    vector<int> restantes = {2,3,5,6,7,8};

    int res = cuantosMagicos(3,matriz,1,0,restantes);

    std::cout << "The value of res is: " << res << std::endl;

    return 0;
}
