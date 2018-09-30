#include"map.hpp"
#include"player.hpp"
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define medicine_max 10 // there are 15 medicine each floor (except floor 4) for u to recover the hp.
using namespace std;


Map::Map() {
	_floor = 0;
	genetate_map(map);
}/* note that 'X' is wall, '@' is player(you!), '.' is the road that u can move to,
	'D' is the door where u can enter next floor but cannot be back( if u have ever read the novel ¡¶Áú×å¡·,
	u will know what this means.*/

void Map::genetate_map(char in[][16][128]) {
	//floor 1
	strcpy(in[0][0], "         XXXXXXXXXX          XXXXX                                     ");
	strcpy(in[0][1], "         X....@...X         XX...XXX                           XXXXXXXX");
	strcpy(in[0][2], "       XXX.XX.....X        XX......X                           X......X");
	strcpy(in[0][3], "XXXXXXXX...XX.....XXXX     X.......X       XXXXXXXXXXXXXXXXXXXXX......X");
	strcpy(in[0][4], "X..........XX........X     X.X...X.X      XX..........................X");
	strcpy(in[0][5], "X...XX...XXXX......X.X     X.XXXXX.X    XX................X.XXXX......X");
	strcpy(in[0][6], "X...XX.XXX  X......X.X     X...X X.X   X...X................XXXXXXX.XX");
	strcpy(in[0][7], "X......X    XXXXXXXX.X     XXX.X X.X XXX.XXX..............X.XXXXX X..X");
	strcpy(in[0][8], "X...XXXXXXXXXXXXXXXX.XXXXXXXXX.X X.XXX...XXXXXXXXX.X.XXXXXX......XXX.X");
	strcpy(in[0][9], "X........................................X       X.X.X    XXXXXXXXXX.X");
	strcpy(in[0][10], "XXXXXXXXXXXXXXXXXXXXX.XXXXXXXXX.XXX....XXX       X...X      X...D....X");
	strcpy(in[0][11], "                    X.XX      X.X X..XXXXXXXXXXXXX.XX       XXXX.....X");
	strcpy(in[0][12], "                    X...XXXXXXX.XXX.................X          XXXXXXX");
	strcpy(in[0][13], "                    X....X    X.X...................X");
	strcpy(in[0][14], "                    XXXXXX    X.....................X");
	strcpy(in[0][15], "                              XXXXXXXXXXXXXXXXXXXXXXX");
	//floor 2
	strcpy(in[1][0], "                      XXXXXXXXXXX       XXXXXX     XXXXXXXXXXXXXXXXXXX");
	strcpy(in[1][1], "                      X..........X      X....X    X..................X");
	strcpy(in[1][2], "                      X........X.X     XX....X    X.X.....X.XX.XX....X");
	strcpy(in[1][3], "                      X..........X    X......X    X.X.....X.XX.......X");
	strcpy(in[1][4], "XXXXXXX               X........X.X    X.X....X   XX.......X.X XXX....X");
	strcpy(in[1][5], "X..@..X               X.XXXXXXXX.X    X.X....X  X...X.....X.X   X.XXXX");
	strcpy(in[1][6], "X.....XXXX            X.XX     X.X XXXX.XX.XXXXX...XXXXXXXX.X   X....X");
	strcpy(in[1][7], "X.....X...X           X...X    X.XX.........................X    XXX.XX");
	strcpy(in[1][8], "X.........XX           XX.X    X....XXX.XX.XXXX..XXXXXXXXXXXX      X...X");
	strcpy(in[1][9], "XXXXXXXXX...X           X.X    X...XX X.XX.XX....X                  XX.XX");
	strcpy(in[1][10], "         XX.XX   XXXXXXXX.XX  XX.....XX.XX....XX.X                   X...X");
	strcpy(in[1][11], "          X...X  X.........X X...................X                    XX.X");
	strcpy(in[1][12], "           XX.XX X.........XXX..XXXXXXX.X..X.XXXXX                  XXXX.X");
	strcpy(in[1][13], "            X...XX....................X.X......X                   X.....X");
	strcpy(in[1][14], "             XX............XXXX.......X......XX                    X.D...X");
	strcpy(in[1][15], "              XXXXXXXXXXXXXX   XXXXXXXXXXXXXXX                      XXXXXX  ");
	//floor 3
	strcpy(in[2][0], "       XXXXXXXXX                             XXXXXXXX    XXXXXXXXXXXX");
	strcpy(in[2][1], "       X...@...X                           XX......XXX  X..........X");
	strcpy(in[2][2], "       X.......X                           XX......XXX  X..........X");
	strcpy(in[2][3], "       X.....X.X                          X...........X X..........X");
	strcpy(in[2][4], "       X.....X.X                          X.X......XX.X X..........X");
	strcpy(in[2][5], "       X.....X.X                          X.XXXX.XXXX..............X");
	strcpy(in[2][6], "       XXX.XXX.X                          X.X  X...X XX.XXXXXXXXX.XXXXX");
	strcpy(in[2][7], "        XX.X X.X                          X.X   XX.XX X...X     X......X");
	strcpy(in[2][8], "       X...X X.X                          X.X    X...X XX.X      XXXXX.XX");
	strcpy(in[2][9], "      X...X  X.X   XXXXX                  X.X     XX.X  X.X          X...X");
	strcpy(in[2][10], "     X...X   X.XX  X...XXXXXXXXX          X.X    XXX.XXXX.X           XX.X");
	strcpy(in[2][11], "    X..XX    X...X X............XXXXXXXXXXX.X    X......X.X   XXXXXXXXXX.X");
	strcpy(in[2][12], "XXXXX.XXXXXX  XX.X X....................................X.X   X..........X");
	strcpy(in[2][13], "X..........X   X...XXXXX.XXXXXX...XXXXXXXX..X    X........X   X..XXXXX...X");
	strcpy(in[2][14], "X..........X     X.......X     XX...........X    XXXXXXXXXX   X....D.....X");
	strcpy(in[2][15], "XXXXXXXXXXXX      XXXXXXX        XXXXXXXXXXX                   XXXXXXXXXX ");
	//floor 4: the last floor 
	strcpy(in[3][0], " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	strcpy(in[3][1], " X@....................................................X");
	strcpy(in[3][2], " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX..X");
	strcpy(in[3][3], " X.....................................................X");
	strcpy(in[3][4], " X..XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	strcpy(in[3][5], " X.....................................................X");
	strcpy(in[3][6], " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX..X");
	strcpy(in[3][7], " X.....................................................X");
	strcpy(in[3][8], " X..XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	strcpy(in[3][9], " X.....................................................X");
	strcpy(in[3][10], " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX..X");
	strcpy(in[3][11], " X.....................................................X");
	strcpy(in[3][12], " X..XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	strcpy(in[3][13], " X.....................................................X");
	strcpy(in[3][14], " X..................................................D..X");
	strcpy(in[3][15], " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
}

void Map::generate(int* in_x,Monster& in) {
	srand(time(NULL));
	int count = 0 , x, y, i, j;
	for (count = 0; count < 3; count++) {
		for (i = 0; i < 8;i++) {
			x = rand() % in_x[count], y = rand() % 15;
			if (map[count][y][x] == '.') map[count][y][x] = 'M';
		}
			for (j = 0; j < 20;j++){
			x = rand() % in_x[count], y = rand() % 15;
			if (map[count][y][x] == '.') {
				map[count][y][x] = '*';
				in.mon_pos[count][j].x = x, in.mon_pos[count][j].y = y, in.mon_pos[count][j].floor = count;
			}
			else { in.mon_pos[count][j].x = 0, in.mon_pos[count][j].y = 0; }
		}
		for (i = 0; i < 5;i++){
			x = rand() % in_x[count], y = rand() % 15;
			if (map[count][y][x] == '.')  map[count][y][x] = 'G'; 
		}
	}
	for (i = 0; i < 5;i++) {
			x = rand() % in_x[count], y = rand() % 15;
			if (map[count][y][x] == '.') map[count][y][x] = 'M';
	}
	for (j = 0; j < 30;j++) {
		x = rand() % in_x[count], y = rand() % 15;
		if (map[count][y][x] == '.') {
			map[count][y][x] = '*';
			in.mon_pos[count][j].x = x, in.mon_pos[count][j].y = y, in.mon_pos[count][j].floor = count;
		}
		else { in.mon_pos[count][j].x = 0, in.mon_pos[count][j].y = 0; }
	}
}//generate the medicine(add hp), gun(add power) and monsters.

void Map::printmap() {
	cout << "\n\n\n\n\n" << endl;
	for (int i = 0; i < Max_row; i++) 
		cout << "\t\t\t"<<map[_floor][i]<<endl;
}

Monster::Monster() {
	for (int i = 0; i < 20; i++) {
		this->mon_pos[0][i].mon_hp = 3 + rand() % 2; 
		this->mon_pos[0][i].mon_power = 2 + rand() % 2;
	}
	for (int i = 0; i < 20; i++) {
		this->mon_pos[1][i].mon_hp = 6 + rand() % 2;
		this->mon_pos[1][i].mon_power = 4 + rand() % 2;
	}
	for (int i = 0; i < 20; i++) {
		this->mon_pos[2][i].mon_hp = 8 + rand() % 2;
		this->mon_pos[2][i].mon_power = 5 + rand() % 2;
	}
	for (int i = 0; i < 30; i++) {
		this->mon_pos[3][i].mon_hp = 10 + rand() % 2;
		this->mon_pos[3][i].mon_power = 4 + rand() % 2;
	}
}//make sure the character of every monster

void Monster::chase(Player& you,Map& in) {
	int x = you.pos_player.x, y = you.pos_player.y,f = you.pos_player.floor;
	int i;
	char hold[4][16][128];
	in.genetate_map(hold);
	for (i = 0; i < 30; i++) {
		if ((mon_pos[f][i].x != 0 && mon_pos[f][i].y != 0)
			&& ((abs(y - mon_pos[f][i].y) + abs(x - mon_pos[f][i].x)) <= 15
				&& (abs(y - mon_pos[f][i].y) + abs(x - mon_pos[f][i].x)) > 1))
		{
			if (((abs(y - mon_pos[f][i].y) < abs(x - mon_pos[f][i].x)) && y != mon_pos[f][i].y)
				|| ((abs(y - mon_pos[f][i].y) >= abs(x - mon_pos[f][i].x)) && x == mon_pos[f][i].x))
			{
				if (y < mon_pos[f][i].y) {
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = hold[f][mon_pos[f][i].y][mon_pos[f][i].x];
					mon_pos[f][i].y--;
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = '*';
				}
				else if (y > mon_pos[f][i].y) {
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = hold[f][mon_pos[f][i].y][mon_pos[f][i].x];
					mon_pos[f][i].y++;
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = '*';
				}
			}
			else {
				if (x < mon_pos[f][i].x) {
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = hold[f][mon_pos[f][i].y][mon_pos[f][i].x];
					mon_pos[f][i].x--;
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = '*';
				}
				else if (x > mon_pos[f][i].x) {
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = hold[f][mon_pos[f][i].y][mon_pos[f][i].x];
					mon_pos[f][i].x++;
					in.map[f][mon_pos[f][i].y][mon_pos[f][i].x] = '*';
				}
			}
		}
	}
}

void Monster::mon_attack(Player& in) {
	int m , n;
	for (int i = 0; i < 30; i++) {
		m = in.pos_player.y - mon_pos[in.pos_player.floor][i].y;
		n = in.pos_player.x - mon_pos[in.pos_player.floor][i].x;
		if ((abs(m) + abs(n)==1)&& mon_pos[in.pos_player.floor][i].mon_hp>0)
			in.hp -= mon_pos[in.pos_player.floor][i].mon_power;
	}
}

bool Monster::is_dead(Map& in) {
	char hold[4][16][128];
	int i, m, n;
	in.genetate_map(hold);
	for (i = 0; i < 30; i++) {
		m = mon_pos[in._floor][i].y, n = mon_pos[in._floor][i].x;
		if (mon_pos[in._floor][i].mon_hp <= 0 && (m != 0 && n != 0)) {
			in.map[in._floor][m][n] = hold[in._floor][m][n];
			mon_pos[in._floor][i].y = mon_pos[in._floor][i].x = 0;
			return 1;
		}
	}
	if (i == 30) return 0;
}
