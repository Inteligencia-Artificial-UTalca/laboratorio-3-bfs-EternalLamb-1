#include "ColorMap.h"
#include <iostream>

ColorMap::ColorMap(const Map& rhs):Map(rhs),colors{37,34,32,31,33}{

}

void ColorMap::print() const{
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            std::cout<<"\033[1;" << colors[_map[i][j]] << "m"<<_map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\033[1;37m\n";
}
void ColorMap::print(std::vector<std::pair<int,int>> path) const{
    auto __map=_map;

     __map[path[0].second][path[0].first] = 2;

     for(int i = 1; i < (int)path.size() - 1; i++){
         __map[path[i].second][path[i].first] = 4;
    }
    
     __map[path[path.size()-1].first][path[path.size()-1].second]=3;

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){

            std::cout<<"\033[1;" << colors[__map[i][j]] << "m"<<__map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<< "\033[1;37m\n";
}