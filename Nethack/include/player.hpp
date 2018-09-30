#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<iostream>
#include"map.hpp"
using namespace std;

class Player {
private:
	char name[16];
	int hp;
	int HP[10] = { 0,15,25,35,45,55,65,75,85,95 };
	int exp;
	int EXP[10] = { 0,3,7,12,20,27,36,48,59,100 };
	int power;
	int level;
	position pos_player;

public:
	Player();
	bool is_alive();
	void printplayer();
	void exp_add();
	void order(char in, Map &,Monster&);
	void level_change();
	bool is_win();
	int getfloor() { return pos_player.floor; }
	friend class Monster;
	friend class Map;
};
#endif

