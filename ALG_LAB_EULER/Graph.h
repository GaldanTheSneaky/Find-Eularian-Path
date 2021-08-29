#pragma once
#include <list>
#include<vector>
#include<string>
#include<sstream>
#include<optional>

class Graph
{
    int numOfVer;    
    std::vector<std::list<int>> adjLists;
public:
    Graph(int numOfVer);
    ~Graph() = default; 
    Graph(const Graph&) = default;
    Graph(Graph&&) = default;

    bool isEulerian();
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    std::optional<std::string> getEulerianCycle();
    void getEulerianCycleFrom(int s, std::stringstream &path);
    int countOfReachable(int v, std::vector<bool>& isVisited);
    bool isValidNextEdge(int u, int v);
};