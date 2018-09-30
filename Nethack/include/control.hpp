#include"map.hpp"
#include"player.hpp"
#include<cstdlib>
#include<conio.h>
#define Sit_max 10

void rule() {
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tSimple  Nethack\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	system("pause");
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t抵制不良游戏，拒绝盗版游戏。" << endl;
	cout << "\t\t\t\t\t注意自我保护，谨防受骗上当。" << endl;
	cout << "\t\t\t\t\t适度游戏益脑，沉迷游戏伤身。" << endl;
	cout << "\t\t\t\t\t合理安排时间，享受健康生活。\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	system("pause");
	system("cls");
	cout << " \n\n\n\n\n\tWelcome to the simple nethack designed by Gou." << endl;
	cout << " \tThe followings are the rules: " << endl;
	cout << " \t1. 'X' is wall, '@' is player(you!), '.' is the road that u can move to," << endl;
	cout << "  \t  'D' is the door where u can enter next floor but cannot be back" << endl;
	cout << "  \t  (if u have ever read the novel 《龙族》,u will know what this means.)  \n" << endl;
	cout << " \t2. Enter q, w,e,a,d,z,x,c to move to different directions." << endl;
	cout << "   \t (note that both uppercase and lowercase is ok.)" << endl;
	cout << "    \tIf your hp is in dangerous level, u can enter 's' to sit(add 1 hp once but 10 times at most)." << endl;
	cout << "    \tIf u are on the door(when displays 'd' ), you can enter 's' to enter next floor.\n" << endl;
	cout << " \t3. 'M' is medicine that can recover u (add your hp)." << endl;
	cout << "  \t  'G' is gun that can strengthen u (add your power).\n" << endl;
	cout << " \t4. '*' is monster that can move trough wall to attack u." << endl;
	cout << "  \t  And of course u can kill them to level up to make yourself stronger." << endl;
	cout << "   \t (Note that u can only attack the monster on your right, left, up and down side.) \n" << endl;
	cout << " \t5. Your destination is on the fourth floor. Fight for it!\n\n\n\n\n" << endl;
	system("pause");
	system("cls");
}

void game() {
	Map game_map;
	Monster game_monster;
	Player game_player;
	system("cls");
	int in_x[4] = { 72,77,75,57 };//the max numbers of columns  of each floor
	static int count = 0;
	game_map.generate(in_x, game_monster);
	char ord, judgement = ' ';
	while (1) {
		game_map.printmap();
		game_player.printplayer();
		ord = _getch();
		if ((ord == 's' || ord == 'S') && count < 10) count++;
		if ((ord == 's' || ord == 'S') && count >= 10) ord = ' ';
		game_player.order(ord, game_map, game_monster);
		game_monster.mon_attack(game_player);
		game_monster.chase(game_player, game_map);
		if (game_monster.is_dead(game_map))  game_player.exp_add();
		game_player.level_change();
		if (game_player.is_alive() == 0) {
			system("cls");
			game_map.printmap();
			game_player.printplayer();
			cout << "\tUnfortuantely, you were killed by monster." << endl;
			break;
		}
		if (game_player.is_win()) {
			cout << "\tSo nice you are! You have completed the mission.";
			break;
		}
		system("cls");
	}
	cout << "\tHappy time is always short. Welcome to try again." << endl;
	system("pause");
}