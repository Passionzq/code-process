/*This head file contains the monster class and map class*/

#ifndef MAP_HPP
#define MAP_HPP
#define Max_row 16
#include<iostream>
#include<cstring>
using namespace std;

struct position{    
	int floor = 0;
	int x = 0;
	int y = 0;
	int mon_hp = 0;
	int mon_power = 0;
};

class Player;
class Monster;

class Map {
private:
	int _floor;
	
public:
	friend class Player;
	friend class Monster;
	Map();
	char map[4][16][128];
	void genetate_map(char in[][16][128]);
	void printmap();
	void generate(int* ,Monster&);

};

class Monster {
private:
	position mon_pos[4][30];
public:
	Monster();
	friend class Map;
	friend class Player;
	void chase(Player&, Map&);
	void mon_attack(Player&);
	bool is_dead(Map&);
};
#endif 

