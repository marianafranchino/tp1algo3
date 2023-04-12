#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

vector<int> seleccionActividades(vector<tuple<int,int,int>> actividades ){

    int n = actividades.size();
    //ordeno las acividades según el tiempo en que termina cada una, usando bucket sort
    vector<vector<tuple<int, int, int>>> ordenadas(2*n);

    for (const auto& actividad : actividades) {
        //agrego la actividad a donde corresponde según cuando termina
        int termina = get<1>(actividad);
        if (termina < ordenadas.size()) {
            ordenadas[termina].push_back(actividad);
        }
    }

    //ahora que ya las tengo ordenadas según cuándo terminan voy agarrandolas y si se superponen no las agrego
    vector<tuple<int, int, int>> seleccionadas;
    int final = 0;
    for(const auto& activ: ordenadas){
        for(const auto& actividad: activ){
            int tiempoInicial = get<0>(actividad);

            if(tiempoInicial >= final){
                final = get<1>(actividad);
                seleccionadas.push_back(actividad);
            }
        }
    }

    //de seleccionadas me quedo con el número de actividad
    vector<int> numeros;
    for (const auto& actividad : seleccionadas){
        //agrego la actividad a donde corresponde según cuando termina
        int num = get<2>(actividad);
        numeros.push_back(num);
    }

    return numeros;
}

bool operaciones(vector<int> v, int i, int m, int r, int resparcial) {
    if (i == v.size()) {
        return (resparcial % m == r);
    } else {
        int suma = operaciones(v, i + 1, m, r, resparcial + v[i]);
        int resta = operaciones(v, i + 1, m, r, resparcial - v[i]);
        int multiplicacion = operaciones(v, i + 1, m, r, resparcial * v[i]);
        int potencia = operaciones(v, i + 1, m, r, static_cast<int>(pow(resparcial, v[i])));
        return (suma || resta || multiplicacion || potencia);
    }
}


int main() {
    // Define and initialize the vector
    std::vector<int> v = {7, 10, 10,50};

    // Call the operaciones() function with the given parameters
    int i = 1; // Start from index 0
    int r = 10;
    int m = 100000;
    int resparcial = v[0]; // Start with the first element of the vector

    bool result = operaciones(v, i, m, r, resparcial);

    // Print the result
    std::cout << "Result: " << (result ? "true" : "false") << std::endl;

    // Input activities as tuples
    vector<tuple<int, int, int>> actividades = {
            make_tuple(6, 7, 1),
            make_tuple(1, 4, 2),
            make_tuple(0, 3, 3),
            make_tuple(4, 10, 4),
            make_tuple(3, 6, 5)
    };

    // Call the function and store the selected activities
    vector<int> selectedActivities = seleccionActividades(actividades);

    // Print the selected activities
    cout << "Selected Activities: ";
    for (int i = 0; i < selectedActivities.size(); i++) {
        cout << selectedActivities[i] << " ";
    }
    cout << endl;
}


