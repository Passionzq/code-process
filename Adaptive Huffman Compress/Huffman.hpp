#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#include <queue>
#include <ctime>

#define SYMBOL 256
#define NUMBER 512

struct node{
	unsigned char symbol; // symbol
	int weight,           // weight
		number;           // number
	node*parent,         // parent
		*left,           // left child
		*right;          // right child    
};

typedef std::pair<int, node*> my_pair;

void create_node(node **leaf, unsigned char symbol, bool is_nyt);
void merge_node(node **tree, node *left, node *right);
void delete_tree(node **tree);
void search_higher_block(node **tree, int weight, int *number, int parent_number, node **position, char *l_r);
void switch_node(node *tree, char *l_r, node *sibling, char *l_r_sibling);
void queueing_node(node **tree, std::vector<my_pair> *queue, int deep);
void increment_weight(node **tree);
void find_external_symbol(node **tree, unsigned char symbol, node **position);
bool my_sort(my_pair p, my_pair q);
void update(node **tree, unsigned char symbol, unsigned char *dictionary, node **nyt);
void get_the_code(node **tree, unsigned char symbol, char *do_code, std::queue<char> *code_write);
void get_nyt_code(node **tree, char *do_code, std::queue<char> *code_write);
void get_standard_code(unsigned char symbol, std::queue<char> *code_write);
void write_to_file(std::ofstream *file, std::queue<char> *code_write);
void encode(node **tree, unsigned char symbol, unsigned char *dictionary, std::queue<char> *code_write, std::ofstream *file, node **nyt);
bool read_from_file(std::ifstream *file, std::queue<char> *code_read);
void get_char_from_code(std::queue<char> *code_read, unsigned char *character);
void write_to_file_instantly(std::ofstream *file, unsigned char symbol);
void decode(node **tree, unsigned char *dictionary, std::queue<char> *code_read, std::ifstream *file, std::ofstream *out_file, node **nyt, bool *oke, short offset);
bool read_from_file_instantly(std::ifstream *file, unsigned char *symbol);
void compress(std::ifstream *in, std::ofstream *out);
void decompress(std::ifstream *in, std::ofstream *out);