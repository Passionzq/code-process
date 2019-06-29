#include "../include/GA.hpp"

using namespace std;

GA::GA()
{
    this->max_fitness = INF;
    this->repeat_num = this->chromosome_num = 0;
    memset(this->key_node,-1,sizeof(this->key_node));
}

GA::~GA()
{
    ;
}

void GA::getRandomIndivisual(Individual& tmp)
{
    do {
        for (int i = 1; i <= chromosome_num; ++i) {
            if (-1 != key_node[i]) {
                tmp.chromosome[i] = key_node[i];
            
            } else {
                tmp.chromosome[i] = (randFloat() > 0.5 ? 1 : 0); 
            }
        }
    } while((graph.getSubGraph(tmp.chromosome)).getTotalWeight() == INF);
}

void GA::init()
{
    int sum = 0;

    for (int i = 1; i <= chromosome_num; ++i) {
        if (graph.degree[i] == 1) {
            if (!graph.isTerminal(i)) {
                key_node[i] = 0;
            
            } else {
                for (int j = 1; j <= chromosome_num; ++j) {
                    if (graph.matrix[i][j] != INF) {
                        key_node[j] = 1;
                        break;
                    }
                }
            }
        } else if (graph.degree[i] == 2 && !graph.isTerminal(i)) {  //slack opreation
            int tmp[2], k = 0;

            for (int j = 1; j <= chromosome_num; ++j) {
                if (graph.matrix[i][j] != INF) {
                    tmp[k++] = j;
                }
            }
            if (graph.matrix[tmp[0]][tmp[1]] != INF && graph.matrix[i][tmp[0]] + graph.matrix[i][tmp[1]] > graph.matrix[tmp[0]][tmp[1]]) {
                key_node[i] = 0;
            }
        }

        if (graph.isTerminal(i)) {
            key_node[i] = 1;
        }
    }

    Individual tmp_;
    for (int i = 1; i < POPUSIZE; ++i) {
        getRandomIndivisual(tmp_);
        population[i].copy(tmp_);
    }   
}

void GA::calculateFiness()
{
    for (int i = 1; i <= POPUSIZE; ++i) {
        population[i].fitness = graph.getSubGraph(population[i].chromosome).getTotalWeight();
    }
}

bool cmp(Individual a, Individual b)
{
    return a.fitness < b.fitness;
}
void GA::sortPopulation()
{
   sort(population+1, population+POPUSIZE - 1, cmp); 
}

Individual& GA::select()
{
    int index;
    int best_fit = INF + 1;

    for (int i = 1; i < TOURNAMENTSIZE; ++i) {
        int tmp = randInt(1, POPUSIZE - 1);
        
        if (population[tmp].fitness < best_fit) {
            index = tmp;
            best_fit = population[tmp].fitness;
        }
    }

    return population[index];
}

void GA::crossover(Individual& p1, Individual &p2, Individual& kid1, Individual& kid2)
{
    kid1.copy(p1), kid2.copy(p2);

    double tmp = randFloat();
    if (tmp > CROSSEROVER_RATE) {
        return;
    }

    int lo = randInt(1, chromosome_num - 2);
    int hi = randInt(1, chromosome_num - 2);

    if (hi < lo) {
        swap(lo, hi);
    }

    for (int i = 1; i < chromosome_num; ++i) {
        if (lo < i && i < hi) {
            continue;
        }
        kid1.chromosome[i] = p2.chromosome[i];
        kid2.chromosome[i] = p1.chromosome[i];
    }

    if (graph.getSubGraph(kid1.chromosome).getTotalWeight() == INF) {
        kid1.copy(p1);
    }

    if (graph.getSubGraph(kid2.chromosome).getTotalWeight() == INF) {
        kid2.copy(p2);
    }
}

void GA::mutate()
{
    double tmp;

    for (int i = ELITIS + 1; i < POPUSIZE; ++i) {
		Individual ind;
		ind.copy(next_population[i]);

        for (int j = 1; j <= chromosome_num; ++j) {
            if (graph.isTerminal(j)) {
                continue;
            }

            tmp = randFloat();
            if (tmp < MUTATION_RATE) {
                next_population[i].chromosome[j] ^= 1;
            }
        }

        if (graph.getSubGraph(next_population[i].chromosome).getTotalWeight() == INF) {
            next_population[i].copy(ind);
        }
    }
}

void GA::printResult()
{
    printf("The nodes: \n");
    for (int i = 1; i <= chromosome_num; ++i) {
        if (population[1].chromosome[i] == 1) {
            printf("%d ",i+1);
        }
    }
    printf("\nTime cost: %lf s\n",(double)(end - start) / CLOCKS_PER_SEC);
}

void GA::exec(std::string path)
{
    srand((unsigned int)time(NULL));
    
    int generation = 1;

    path = "../data/"+path+".stp";

    this->graph.readFile(path.c_str());
	this->chromosome_num = graph.node_num;

    start = clock();
    
    this->init();
    this->calculateFiness();
    this->sortPopulation();
    
    printf("The bestfit at first: %4d\n",population[1].fitness);
    max_fitness = population[1].fitness;
    repeat_num = 1;

    while (generation < MAXGENS && repeat_num <= MAX_REPEAT) {
        int i;
        
		for (i = ELITIS + 1; i + 1 < POPUSIZE; i += 2) {
			Individual p1, p2;
			p1.copy(select());
			p2.copy(select());
			crossover(p1, p2, next_population[i], next_population[i + 1]);
		}

        if (i < POPUSIZE) {
            next_population[i].copy(select());
        }

        this->mutate();

        for (int i = ELITIS + 1; i < POPUSIZE; ++i) {
            population[i].copy(next_population[i]);
        }

        this->calculateFiness();
        this->sortPopulation();

        generation++;

        if(population[1].fitness == max_fitness) {
            repeat_num++;
            
        } else {
            max_fitness = population[1].fitness;
            repeat_num = 1;
			printf("The bestfit has changed in generation %4d, and its values is %4d.\n", generation, max_fitness);
        }  
    }
	printf("\nThe last bestfit value is %4d.\n", max_fitness);
	end = clock();
    this->printResult();
}