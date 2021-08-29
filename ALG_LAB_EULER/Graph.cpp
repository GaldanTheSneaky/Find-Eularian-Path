#include "Graph.h"
#include<iostream>
#include<sstream>

Graph::Graph(int numOfVer)
{
    this->numOfVer = numOfVer;
    std::vector<std::list<int>> listBuffer(numOfVer);
    adjLists = listBuffer;
}

bool Graph::isEulerian()
{
    for (int i = 0; i < numOfVer; i++)
        if (adjLists[i].size() % 2 == 1) return false;

    return true;
}

std::optional<std::string> Graph::getEulerianCycle()
{
    if (!isEulerian()) return {};

    std::stringstream path;
    getEulerianCycleFrom(0, path);
    return path.str();
}

void Graph::getEulerianCycleFrom(int ver, std::stringstream &path)
{
    std::list<int>::iterator i;
    for (i = adjLists[ver].begin(); i != adjLists[ver].end(); ++i)
    {
        int adjVer = *i;

        if (adjVer != -1 && isValidNextEdge(ver, adjVer))
        {
            path << ver << "-" << adjVer << "  ";
            removeEdge(ver, adjVer);
            getEulerianCycleFrom(adjVer, path);
        }
    }
}

bool Graph::isValidNextEdge(int first, int second)
{
    int count = 0;  
    std::list<int>::iterator i;
    for (i = adjLists[first].begin(); i != adjLists[first].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;

    std::vector<bool> isVisited1(numOfVer);
    int count1 = countOfReachable(first, isVisited1);

    removeEdge(first, second);
    std::vector<bool> isVisited2(numOfVer);

    int count2 = countOfReachable(first, isVisited2);
    addEdge(first, second);

    return (count1 > count2) ? false : true;
}

void Graph::addEdge(int first, int second)
{ 
    adjLists[first].push_back(second);
    adjLists[second].push_back(first);
}

void Graph::removeEdge(int first, int second)
{
    std::list<int>::iterator iv = find(adjLists[first].begin(), adjLists[first].end(), second);
    *iv = -1;

    std::list<int>::iterator iu = find(adjLists[second].begin(), adjLists[second].end(), first);
    *iu = -1;

}

int Graph::countOfReachable(int v, std::vector<bool> &isVisited)
{
    isVisited[v] = true;
    int count = 1;

    std::list<int>::iterator i;
    for (i = adjLists[v].begin(); i != adjLists[v].end(); ++i)
        if (*i != -1 && !isVisited[*i])
            count += countOfReachable(*i, isVisited);

    return count;
}