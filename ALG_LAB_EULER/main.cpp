#include"Graph.h"
#include<iostream>
#include<fstream>

int main()
{
    std::ifstream inputFile("graph.txt");

    if (!inputFile.is_open())
        std::cout << "File cannot be open!" << std::endl;
    else
    {
        int NumOfVer;
        inputFile >> NumOfVer;
        Graph graph(NumOfVer);

        int first, second;
        while (inputFile >> first >> second)
        {
            graph.addEdge(first, second);
        }
        std::cout << graph.getEulerianCycle().value_or("Has not eulerian cycle!") << std::endl;
    }

    return 0;
}