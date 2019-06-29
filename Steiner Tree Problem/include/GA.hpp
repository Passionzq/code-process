#ifndef GA_HPP
#define GA_HPP

#include "Graph.hpp"

#define CROSSEROVER_RATE 0.7
#define MUTATION_RATE 0.05
#define POPUSIZE 101	        //The size of the Individuals
#define TOURNAMENTSIZE 41       //The size of Eliminated Array
#define ELITIS 10               //The number of the Elitis
#define MAXGENS 1000            //The number of the max generations
#define MAX_REPEAT 300			//The number of the max bestfit to repeat 

struct Individual{
    int chromosome[MAX];
    int fitness;

    Individual()
    {
        memset(chromosome,0,sizeof(chromosome));
        fitness = INF;
    }

    void copy(Individual& tmp)
    {
        fitness = tmp.fitness;
        for (int i = 0; i < MAX; ++i) {
            chromosome[i] = tmp.chromosome[i];
        }
    }
};

class GA{
  public:
    /* 
        METHODS:
    */
    GA();
    ~GA();

    //Gnenrate the Indivisual that consist of the terminal.
    void getRandomIndivisual(Individual& tmp);

    //initialize the population
    void init();
    
    //calculate the finess of the population
    void calculateFiness();

    //sort the population according to the fitness
    void sortPopulation();

    //choose one Individual that will not to be eliminated
    Individual& select();

    void crossover(Individual& p1,Individual& p2, Individual& baby1, Individual& baby2);	
	void mutate();

    void printResult();
    void exec(std::string path);

    /* 
        MEMBER VARIABLES: 
    */
    Graph graph;
    int max_fitness;
    int repeat_num;
    int chromosome_num;
    int key_node[MAX];
    clock_t start, end;
    Individual population[POPUSIZE]; 
    Individual next_population[POPUSIZE];
};

#endif