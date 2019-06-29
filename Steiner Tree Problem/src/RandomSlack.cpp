#include "../include/RandomSlack.hpp"

using namespace std;

RandomSlack::RandomSlack()
{
    ;
}

RandomSlack::~RandomSlack()
{
    ;
}

void RandomSlack::slack()
{
    int terminal_id = randInt(1,this->graph.terminal_num);
    int node_id;
    do {
        node_id = randInt(1,this->graph.node_num);
    } while (graph.terminal[terminal_id] == node_id);

    if (this->graph.isTerminal(node_id)) {
        for (int i = 1; i <= graph.terminal_num; ++i) {
            if (graph.matrix[graph.terminal[terminal_id]][node_id] > graph.matrix[graph.terminal[terminal_id]][i] + graph.matrix[i][graph.terminal[terminal_id]]) {
                graph.matrix[graph.terminal[terminal_id]][node_id] = graph.matrix[graph.terminal[terminal_id]][i] + graph.matrix[i][graph.terminal[terminal_id]];
            }
        }
    } else {
        int node_id2;
        do {
            node_id2 = randInt(1,graph.node_num);
        } while (node_id2 == node_id || graph.terminal[terminal_id] == node_id2);

        for (int i = 1; i <= graph.node_num; ++i) {
            if (graph.matrix[graph.terminal[terminal_id]][node_id2] > graph.matrix[graph.terminal[terminal_id]][node_id] + graph.matrix[node_id][node_id2]) {
                graph.matrix[graph.terminal[terminal_id]][node_id2] = graph.matrix[graph.terminal[terminal_id]][node_id] + graph.matrix[node_id][node_id2];
            }
        }
    }
}

void RandomSlack::exec(string path)
{
    srand((unsigned int)time(NULL));
    
    path = "../data/"+path+".stp";

    this->graph.readFile(path.c_str());

    this->start = clock();

    graph.terminal_num = graph.node_num;
    for(int i = 1; i <= graph.node_num; ++i) {
        graph.terminal[i] = i;
    }

    printf("The initial MST's total weight is %d.\n",graph.getTotalWeight());
    for(int i = 0; i < SLACK_TIMES; ++i) {
        this->slack();
    }
    printf("After RandomSlack, the total weight is %d.\n",graph.getTotalWeight());
    
    end = clock();
    printf("\nTime cost: %lf s\n",(double)(end - start) / CLOCKS_PER_SEC);

}