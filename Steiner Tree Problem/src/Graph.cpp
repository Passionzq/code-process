#include "../include/Graph.hpp"

using namespace std;

int randInt(int begin, int end) {
	return rand() % (end - begin) + begin + 1;
}

double randFloat() {
	return rand() / double(RAND_MAX);
}

Graph::Graph()
{
    this->edge_num = this->terminal_num = 0;
    
    for (int i = 0; i < MAX ; ++i) {
        for (int j = 0; j < MAX; ++j) {
            this->matrix[i][j] = INF;
        }
        this->terminal[i] = 0;
        this->degree[i] = 0;
    }
}

Graph::~Graph()
{
    ;
}

bool Graph::readFile(const char* filename)
{
    string str;
	ifstream data(filename);
	int count = 1, state = 0;
	int x, y, z;

	if (!data.is_open()) {
		printf("Error: File cannot open.\n");
		return false;

	} else {
		while (getline(data, str)) {
			if ("SECTION Graph" == str) {
				state = 1;

			} else if ("SECTION Terminals" == str || "Section Terminals" == str) {
				state = 2;

			} else if ("END" == str || "End" == str) {
				state = 0;
				count = 1;

			} else if (1 == state) {
				string tmp = str.substr(6);
				stringstream hold;
				hold << tmp;
				hold >> this->node_num;
				state = 3;

			} else if (2 == state) {
				string tmp = str.substr(10);
				stringstream hold;
				hold << tmp;
				hold >> this->terminal_num;
				state = 4;

			} else if (3 == state) {
				string tmp = str.substr(6);
				stringstream hold;
				hold << tmp;
				hold >> this->edge_num;
				state = 5;

			} else if (4 == state) {
				string tmp = str.substr(2);
				stringstream hold;
				hold << tmp;
				hold >> terminal[count++];

			} else if (5 == state && str != "") {
				string tmp = str.substr(2);
				for (int i = 0; i < tmp.length(); ++i) {
					if (tmp[i] == ' ') {
						stringstream hold;
						hold << tmp.substr(0, i);
						hold >> x;
						tmp = tmp.substr(i + 1);
						hold.clear();
						break;
					}
				}
				for (int i = 0; i < tmp.length(); ++i) {
					if (tmp[i] == ' ') {
						stringstream hold;
						hold << tmp.substr(0, i);
						hold >> y;
						tmp = tmp.substr(i + 1);
						hold.clear();
						break;
					}
				}
				stringstream hold;
				hold << tmp;
				hold >> z;
				matrix[x][y] = matrix[y][x] = z;
                this->edges.push_back(Edge(x,y,z));
				this->degree[x]++;
				this->degree[y]++;
			}
		}
	}

	data.close();
	/* 
    printf("Matrix:\n");
    for (int i = 1; i <= this->node_num; ++i) {
        for (int j = 1; j <= this->node_num; ++j) {
            printf("%6d ",this->matrix[i][j]);
        }
        printf("\n");
    }
	*/
    printf("Terminals of the data:\n");
    for(int i = 1; i <= this->terminal_num; ++i) {
        printf("%3d ",terminal[i]);
    }
    printf("\n");
	data.close();

	return true;
}

int Graph::getTotalWeight()
{
    int sum = 0;
	int min_cost, index;
	int cost[MAX];
    bool visited[MAX];

	for (int i = 1; i <= this->node_num; ++i) {
		visited[i] = false;
        cost[i] = INF;
    }
	
	for (int i = 1; i <= this->node_num; ++i) {
		int p = terminal[i];
		cost[p] = matrix[terminal[1]][p];
	}
	cost[terminal[1]] = 0;
	visited[1] = true;

	for (int i = 2; i <= this->terminal_num; ++i) {
		index = -1;
		min_cost = INF;
		for (int j = 2; j <= this->terminal_num; ++j) {
			if (!visited[terminal[j]] && cost[terminal[j]] < min_cost) {
				index = j;
				min_cost = cost[terminal[j]];
			}
		}

		if (-1 == index || min_cost == INF) {
			return INF;
		}

		sum += min_cost;
		cost[terminal[index]] = 0;	
		visited[terminal[index]] = 1;

		for (int j = 2; j <= this->terminal_num; ++j) {
			if (!visited[terminal[j]] && this->matrix[terminal[index]][terminal[j]] < cost[terminal[j]]) {
				cost[terminal[j]] = matrix[terminal[index]][terminal[j]];
			}
		}
	}
	return sum;
}

Graph Graph::getSubGraph(const int *chromosome) const
{
    Graph subGraph;
    subGraph.node_num = this->node_num;
    int count = 1;
	for (int i = 1; i <= this->node_num; ++i) {
        if (1 == chromosome[i]) {
            subGraph.terminal[count++] = i;
            subGraph.terminal_num++;
            subGraph.degree[i] = this->degree[i];

            for (int j = 1; j <= this->node_num; ++j) {
                if(this->matrix[i][j] != INF && subGraph.matrix[i][j] == INF) {
                    subGraph.matrix[i][j] = subGraph.matrix[j][i] = this->matrix[i][j];
                    subGraph.edge_num++;
                    subGraph.edges.push_back(Edge(i,j,this->matrix[i][j]));                    
                }
            }
        }
    }
	return subGraph;
}

bool Graph::isTerminal(int id)
{
	for (int i = 1; i <= terminal_num; ++i) {
		if (id == terminal[i]) {
			return true;
		}
	}
	return false;
}