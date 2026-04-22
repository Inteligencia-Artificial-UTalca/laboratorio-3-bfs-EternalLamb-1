#include "Search.h"
#include <queue>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <limits>


namespace std
{
    //this is needed to store a pair<int,int> in an associative container
    //such as unorered_set and unordered_map
	template<> struct hash<std::pair<int,int>>
	{
		std::size_t operator()( const std::pair<int,int> & p) const noexcept
		{
            hash<int> hasher;
			return hasher(p.first) ^ (hasher(p.second)<<1);

		}
	};
}

std::vector<std::pair<int,int>> Search::reconstruct(const std::unordered_map<std::pair<int,int>,std::pair<int,int>> &pathCache, const std::pair<int,int> &start){
	std::deque<std::pair<int,int>> nodes;
	auto node = start;//make copy

    //traverse path from goal to start
	while(true)
    {
        nodes.push_front(node);
        if(node == start) break;
        node = pathCache.at(node);            
	}

    //revert path and return it
    std::vector<std::pair<int,int>> vec;
    for(auto p:nodes){
        vec.push_back(p);
    }
    return vec;
}

std::vector<std::pair<int,int>> Search::BFS(const Map& map, std::pair<int,int> start, std::pair<int,int> goal){
    std::cout<<"===========================\nRunning BFS...\n";
	auto startTime = std::chrono::high_resolution_clock::now();

    //stores possible directions
    std::pair<int,int> dirs[]{{1,0},{-1,0},{0,1},{0,-1}};

    bool visited[map.h][map.w]{false};      //we'll just use a matrix og booleans to indicated if visited
    std::queue<std::pair<int,int>> OPEN;
    std::unordered_map<std::pair<int,int>,std::pair<int,int>> pathCache;    ////hashmap to reconstruct path: child -> parent

    //add firts node to open list
    // 4) Agregar el primer nodo y marcar visitado
    OPEN.push(start);
    visited[start.second][start.first] = true;

    while(!OPEN.empty())
    {
        //get node
        std::pair<int,int> pos = OPEN.front();
        OPEN.pop();

        //check if node is goal
		if(pos==goal){
			auto endTime = std::chrono::high_resolution_clock::now();
			int count=0;
            for(int i=0;i<map.h;i++){
                for(int j=0;j<map.w;j++){
                    if(visited[i][j])count++;
                }
            }
            std::cout<<"VISITED: "<<count<<std::endl;
			std::cout<<"OPEN: "<<OPEN.size()<<std::endl;
			std::cout<<"FOUND in "<<(endTime-startTime).count()/1000000.0<<"ms\n";
			return reconstruct(pathCache,pos);
		}

		
        for(auto dir : dirs)
        {
            std::pair<int,int> child = {pos.first + dir.first, pos.second + dir.second};
                if(map.isValid(child.first, child.second) && !map.isWall(child.first, child.second) && !visited[child.second][child.first])
                {
                    visited[child.second][child.first] = true; // marcar como visitado
                    OPEN.push(child);                          // agregar el hijo a la lista abierta
                    pathCache[child] = pos;                    // register path
                }
        }           
	}

	std::cout<<"NOT FOUND!!!!\n";
    
    //let's just return start and goal to draw them
    std::vector<std::pair<int,int>> path;
    path.push_back(start);
    path.push_back(goal);
    return path;
}
