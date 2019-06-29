#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>


#define MAX 101
#define INF 100000

int randInt(int lw, int hi);
double randFloat();

struct Edge{
    int start, end, weight;

    Edge(int s, int e, int w)
    {
        start = s;
        end = e;
        weight = w;
    }
};

class Graph{
  public:
    /* 
        METHODS:
    */
    Graph();
    ~Graph();

    //load data from file to constuct the graph
    //@param filename: the path of the filename
    bool readFile(const  char* filename);

    //use prim algorithm to calculate the total weight
    //of the MST of the graph
    int getTotalWeight();

    //use the chromosome to constuct the new tree
    Graph getSubGraph(const int *chromosome) const;

    bool isTerminal(int node_id);
    
    /* 
        MEMBER VARIABLES: 
    */
    int node_num;
    int edge_num;
    int terminal_num;
    int matrix[MAX][MAX];
    int terminal[MAX];
    int degree[MAX];
    std::vector<Edge> edges; 
};

#endif