#include "Map.h"
#include "Search.h"
#include "ColorMap.h"
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]){

    if (argc !=6)
    {
        std::cout << "Error, la cantidad de argumentos es invalida" << std::endl;
        return 1;
    }

    // Validar que las coordenadas sean números antes de usarlas
    for(int i = 2; i < 6; i++) {
        std::string arg = argv[i];
        for(char c : arg) {
            if(!isdigit(c)) {
                std::cout << "Error: El argumento " << i << " no es un numero valido" << std::endl;
                return 1;
            }
        }
    }

    //Load map with class Map
    Map map(argv[1]);

    int x1 = std::atoi(argv[2]);
    int y1 = std::atoi(argv[3]);
    int x2 = std::atoi(argv[4]);
    int y2 = std::atoi(argv[5]);

    if (!map.isValid(x1, y1) || !map.isValid(x2, y2)) {
        std::cout << "Error: Coordenadas fuera de los limites del mapa" << std::endl;
        return 1;
    }

    ColorMap colorMap(map);

    colorMap.print();

    auto path = Search::BFS(map,{atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5])}); 
    colorMap.print(path);
    
    return 0;
}