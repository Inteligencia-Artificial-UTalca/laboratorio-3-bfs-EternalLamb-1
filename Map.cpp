#include "Map.h"
#include <iostream>
#include <fstream>

Map::Map():h(0),w(0){

}

Map::Map(std::string filename){
    
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        h = 0; w = 0;
        return;
    }

    // 3) Cargar dimensiones y matriz del mapa elegido
    file >> h >> w;
    _map.resize(h, std::vector<int>(w));
 
   for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int valor; 
            if (file >> valor) {
                _map[i][j] = valor;
            } else {
                _map[i][j] = 1; // Muro 
            }
        }
    }
    file.close();
}   

Map::Map(const Map& rhs):h(rhs.h),w(rhs.w),_map(rhs._map){

}

Map::~Map(){
    
}

Map& Map::operator=(const Map& rhs){
    if(this==&rhs)return *this;
    h=rhs.h;
    w=rhs.w;
    _map=rhs._map;
    return *this;
}

bool Map::isValid(int x, int y) const {
    return (x >= 0 && x < w && y >= 0 && y < h);
}

bool Map::isWall(int x, int y) const {
    return _map[y][x] == 1;
}

void Map::print(std::vector<std::pair<int,int>> path) const{
      if (path.empty()) {
        std::cout << "No se encontró un camino para mostrar.\n";
        return;
    }

    // Creamos copia para no modificar el original
    std::vector<std::vector<int>> temp_map = _map;

    // CORRECCIÓN CLAVE: Usar [second][first] para [Y][X]
    // Primero marcamos todo el camino con 4
    for (size_t i = 0; i < path.size(); i++) {
        temp_map[path[i].second][path[i].first] = 4;
    }

    // Sobrescribimos Inicio (2) y Fin (3)
    temp_map[path[0].second][path[0].first] = 2;
    temp_map[path.back().second][path.back().first] = 3;

    // Impresión con espacios para legibilidad
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cout << temp_map[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool operator==(const Map& lhs, const Map& rhs){
    return lhs.h==rhs.h && lhs.w==rhs.w && lhs._map==rhs._map;
}