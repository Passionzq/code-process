#ifndef RANDOMSLACK_HPP
#define RANDOMSLACK_HPP

#include "Graph.hpp"
#include <unistd.h>

#define SLACK_TIMES 1000000

class RandomSlack{
  public:
    /* 
        METHODS:
    */
    RandomSlack();
    ~RandomSlack();

    //Select two or thre nodes to slack. 
    //If successfully, replace the distance of the nodes.
    void slack();
    void exec(std::string path);

    /* 
        MEMBER VARIABLES: 
    */
    Graph graph;
    clock_t start, end;
};

#endif