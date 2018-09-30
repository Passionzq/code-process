#include"player.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;

Player::Player() {
	exp = 0, level = 1, power = 3;
	hp = HP[level];
	pos_player.floor = 0, pos_player.x = 14, pos_player.y = 1;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tGive it a nice name: (NO more than 16 words.)" << endl;
	cout << "\t\t\t\t\t";
	cin >> name;
}

void Player::order(char input, Map&in,Monster& mon) {
	int x = pos_player.x, y = pos_player.y, f = pos_player.floor;
	switch (input) {
	case'a':
	case'A':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y][x - 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y][x - 1] = '@';
				--pos_player.x;
			}
			else if (in.map[f][y][x - 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y][x - 1] = '@';
				--pos_player.x;
				power += 2;
			}
			else if (in.map[f][y][x - 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y][x - 1] = '@';
				--pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y][x - 1] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x - 1 && mon.mon_pos[in._floor][i].y == y)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		else {
			if (in.map[f][y][x - 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y][x - 1] = '@';
				--pos_player.x;
			}
			else if (in.map[f][y][x - 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y][x - 1] = '@';
				--pos_player.x;
				power += 2;
			}
			else if (in.map[f][y][x - 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y][x - 1] = '@';
				--pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y][x - 1] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y][x - 1] = 'd';
				--pos_player.x;
			}
			else if (in.map[f][y][x - 1] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x - 1 && mon.mon_pos[in._floor][i].y == y) 
						mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		break;
	case'd':
	case'D':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y][x + 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y][x + 1] = '@';
				++pos_player.x;
			}
			else if (in.map[f][y][x + 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y][x + 1] = '@';
				++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y][x + 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y][x + 1] = '@';
				++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y][x + 1] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x + 1 && mon.mon_pos[in._floor][i].y == y)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		else {
			if (in.map[f][y][x + 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y][x + 1] = '@';
				++pos_player.x;
			}
			else if (in.map[f][y][x + 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y][x + 1] = '@';
				++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y][x + 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y][x + 1] = '@';
				++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y][x + 1] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y][x + 1] = 'd';
				++pos_player.x;
			}
			else if (in.map[f][y][x + 1] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x + 1 && mon.mon_pos[in._floor][i].y == y)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		break;
	case'w':
	case'W':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y - 1][x] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x] = '@';
				--pos_player.y;
			}
			else if (in.map[f][y - 1][x] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x] = '@';
			    --pos_player.y;
				power += 2;
			}
			else if (in.map[f][y - 1][x] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y -1][x] = '@';
				--pos_player.y;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y - 1][x] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x && mon.mon_pos[in._floor][i].y == y - 1)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		else {
			if (in.map[f][y - 1][x] == '.') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x] = '@';
				--pos_player.y;
			}
			else if (in.map[f][y - 1][x] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x] = '@';
				--pos_player.y;
				power += 2;
			}
			else if (in.map[f][y - 1][x] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x] = '@';
				--pos_player.y;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y - 1][x] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x] = 'd';
				--pos_player.y;
			}
			else if (in.map[f][y - 1][x] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x && mon.mon_pos[in._floor][i].y == y - 1)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		break;
	case'x':
	case'X':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y + 1][x] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x] = '@';
				++pos_player.y;
			}
			else if (in.map[f][y + 1][x] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x] = '@';
				++pos_player.y;
				power += 2;
			}
			else if (in.map[f][y + 1][x] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x] = '@';
				++pos_player.y;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y + 1][x] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x && mon.mon_pos[in._floor][i].y == y + 1)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		else {
			if (in.map[f][y + 1][x] == '.') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x] = '@';
				++pos_player.y;
			}
			else if (in.map[f][y + 1][x] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x] = '@';
				++pos_player.y;
				power += 2;
			}
			else if (in.map[f][y + 1][x] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x] = '@';
				++pos_player.y;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y + 1][x] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x] = 'd';
				++pos_player.y;
			}
			else if (in.map[f][y + 1][x] == '*') {
				for (int i = 0; i < 20; i++) {
					if (mon.mon_pos[in._floor][i].x == x && mon.mon_pos[in._floor][i].y == y + 1)  mon.mon_pos[in._floor][i].mon_hp -= power;
				}
			}
		}
		break;
	case'z':
	case'Z':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y + 1][x - 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x - 1] = '@';
				++pos_player.y, --pos_player.x;
			}
			else if (in.map[f][y + 1][x - 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x - 1] = '@';
				++pos_player.y, --pos_player.x;
				power += 2;
			}
			else if (in.map[f][y + 1][x - 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x - 1] = '@';
				++pos_player.y, --pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
		}
		else {
			if (in.map[f][y + 1][x - 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x - 1]= '@';
				++pos_player.y, --pos_player.x;
			}
			else if (in.map[f][y + 1][x - 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x - 1] = '@';
				++pos_player.y, --pos_player.x;
				power += 2;
			}
			else if (in.map[f][y + 1][x - 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x - 1] = '@';
				++pos_player.y, --pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y + 1][x - 1] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x - 1] = 'd';
				++pos_player.y, --pos_player.x;
			}
		}
		break;
	case'c':
	case'C':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y + 1][x + 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
			}
			else if (in.map[f][y + 1][x + 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y + 1][x + 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
		}
		else {
			if (in.map[f][y + 1][x + 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
			}
			else if (in.map[f][y + 1][x + 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y + 1][x + 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x + 1] = '@';
				++pos_player.y, ++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y + 1][x + 1] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y + 1][x + 1] = 'd';
				++pos_player.y, ++pos_player.x;
			}
		}
		break;
	case'q':
	case'Q':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y - 1][x - 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x - 1] = '@';
				--pos_player.y, --pos_player.x;
			}
			else if (in.map[f][y - 1][x - 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x - 1] = '@';
				--pos_player.y, --pos_player.x;
				power += 2;
			}
			else if (in.map[f][y - 1][x - 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x - 1] = '@';
				--pos_player.y, --pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
		}
		else {
			if (in.map[f][y - 1][x - 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x - 1] = '@';
				--pos_player.y, --pos_player.x;
			}
			else if (in.map[f][y - 1][x - 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x - 1] ='@';
				--pos_player.y, --pos_player.x;
				power += 2;
			}
			else if (in.map[f][y - 1][x - 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x - 1] = '@';
				--pos_player.y, --pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y - 1][x - 1] == 'D') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x - 1] = 'd';
				--pos_player.y, --pos_player.x;
			}
		}
		break;
	case'e':
	case'E':
		if (in.map[f][y][x] == 'd') {
			if (in.map[f][y - 1][x + 1] == '.') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x + 1] = '@';
				--pos_player.y, ++pos_player.x;
			}
			else if (in.map[f][y - 1][x + 1] == 'G') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x + 1] = '@';
				--pos_player.y, ++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y - 1][x + 1] == 'M') {
				in.map[f][y][x] = 'D', in.map[f][y - 1][x + 1] = '@';
				--pos_player.y, ++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
		}
		else {
			if (in.map[f][y - 1][x + 1] == '.') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x + 1] = '@';
				--pos_player.y, ++pos_player.x;
			}
			else if (in.map[f][y - 1][x + 1] == 'G') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x + 1] ='@';
				--pos_player.y, ++pos_player.x;
				power += 2;
			}
			else if (in.map[f][y - 1][x + 1] == 'M') {
				in.map[f][y][x] = '.', in.map[f][y - 1][x + 1] = '@';
				--pos_player.y, ++pos_player.x;
				hp + 2 > HP[level] ? hp = HP[level] : hp += 2;
			}
			else if (in.map[f][y - 1][x + 1] == 'D') {
				in.map[f][y][x] =='.', in.map[f][y - 1][x + 1] = 'd';
				--pos_player.y, ++pos_player.x;
			}
		}
		break;
	case's':
	case'S':
		if (in.map[f][y][x] == 'd') {
			++in._floor, ++pos_player.floor;
			if (pos_player.floor == 1) { pos_player.x = 3, pos_player.y = 5; }
			else if (pos_player.floor == 2) { pos_player.x = 11, pos_player.y = 1; }
			else if (pos_player.floor == 3) { pos_player.x = 2, pos_player.y = 1; }
		}
		else { if(hp+1<=HP[level])++hp; }
		break;
	case' ':
		if (in.map[f][y][x] == 'd') {
			++in._floor, ++pos_player.floor;
			if (pos_player.floor == 1) { pos_player.x = 3, pos_player.y = 5; }
			else if (pos_player.floor == 2) { pos_player.x = 11, pos_player.y = 1; }
			else if (pos_player.floor == 3) { pos_player.x = 2, pos_player.y = 1; }
		}
		break;
	default:
		break;
	}
	if (pos_player.floor == 0 && in.map[pos_player.floor][1][14] == '@'&&pos_player.x != 14 && pos_player.y != 1) in.map[pos_player.floor][1][14] = '.';
	if (pos_player.floor == 1 && in.map[pos_player.floor][5][3] == '@'&&pos_player.x != 3 && pos_player.y != 5) in.map[pos_player.floor][5][3] = '.';
	if (pos_player.floor == 2 && in.map[pos_player.floor][1][11] == '@'&&pos_player.x != 11 && pos_player.y != 1) in.map[pos_player.floor][1][11] = '.';
	if (pos_player.floor == 3 && in.map[pos_player.floor][1][2] == '@'&&pos_player.x != 2 && pos_player.y != 1) in.map[pos_player.floor][1][2] = '.';
} 

void Player::level_change() {
	if (exp >= EXP[level]) { 
		exp -= EXP[level], ++level, hp +=8, power += 1;
	}
}// judge if player needs to level up

void Player::printplayer() {
	if (is_alive()) {
		cout << "\t\t\tPlayer: " << name << endl;
		cout << "\t\t\t\tLevel: " << level << "\tExp: " << exp << " / " << EXP[level] << endl;
		cout << "\t\t\t\tHP: " << hp << " / " << HP[level] << "\tPower: " << power << "\tPosition: " << pos_player.floor + 1 << " / 4 floor(s)" << endl;
	}
} // print the character of player

void Player::exp_add() {
	srand(time(NULL));
	exp +=  1+rand() % 2;
}

bool Player::is_alive() { return(hp <= 0 ? 0 : 1); }//judge if player is alive or not

bool Player::is_win() { return(pos_player.floor == 3 && pos_player.x == 54 && pos_player.y == 14 ? 1 : 0); }
