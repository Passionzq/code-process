#pragma once
#include<iostream>
#include<windows.h>
using namespace std;

class Display {
public:
	Display() {}
	~Display() {}

	void display_load_page() {
		string str;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\tWelcome come to the simplest proteus." << endl
			<< "\n\t\t\t\t\t\tProgrammer:Zhang Qi"<<endl
			<<"\t\t\t\t\t\tSchool id: 17343153"
			<< "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	}

	void display_warning_page() {
		cout << "\n\n\t\t\t\t\tUser instructions" << endl
			<< "\n\n\t\t1. The protduct contain five kinds of gate: Port, And, Not, Or, Xor." << endl
			<< "\n\n\t\t2. The circuit must start at Port (which can set the state)." << endl
			<< "\n\n\t\t3. For port's ouput is equal to input. And it has only one input, so does Not gate." << endl
			<< "\t\t   For the other kinds of gates, they have two inputs." << endl
			<< "\n\n\t\t4. Every kinds of gates own sixteen outputs to connect other gates." << endl
			<< "\n\n\t\t5. The maximum number of gates in the circuit is 64." << endl
			<< "\n\n\t\t6. All the relations of inputs and outputs are the same with proteus." << endl
			<< "\n\n\t\t7. More details will be shown in the program. Best wishes to u!" << endl;
		cout << "\n\n\n\n\n\n\n";
	}

	void display_base_page() {
		cout << "\n To do next:" << endl
			<< " 1. Creat a gate." << endl
			<< " 2. Connect two gates." << endl
			<< " 3. Disconnect two gates." << endl
			<< " 4. Show the current circuit." << endl
			<< " 5. Start circuit simulation." << endl
			<< " 6. Set the in_port's state." << endl
			<< " 7. Rewite the circuit." << endl
			<< " 8. Quit." << endl
			<< "\n\n ATTENTION: SIMULATE AND SEE THE CURRENT CIRCUIT." << endl
			<<" Please enter your choice:  ";
	}

	void display_creat_page() {
		cout << "\n Which kind of gate u want to creat:" << endl
			<< " 1. Port. " << endl
			<< " 2. Not gate." << endl
			<< " 3. And gate." << endl
			<< " 4. Or gate." << endl
			<< " 5. XOr gate. " << endl
			<< "\n\n Pleaset enter your choice:  ";
	}

	void display_connect_page() {
		cout << "\n For example: 2 8 0" << endl
			<< " (which means the gate-2's output connects with gate-8's first input.)" << endl
			<< "\n Please enter the id of two gates and which in_port(0 or 1) you want to connect:" << endl
			<< " (-1 to return the main page)" << endl;
	}

	void display_disconnect_page() {
		cout << "\n For example: 5 1 1" << endl
			<< " (which means the gate-5's output disconnects with gate-1's second input.)" << endl
			<< "\n Please enter the id of two gates and which in_port(0 or 1) you want to connect:" << endl;
		cout << " (-1 to return the main page)" << endl;
	}

	void display_rewrite_page() {
		cout << "\n\n Are u sure to do this?" << endl
			<< " 1 to continue, 0 to cancel :   " << endl;
	}

	void display_state_page() {
		cout << "\n For example:  12  1" << endl
			<< " (which means the gate-12(port)'s state turn to high.)" << endl
			<< "\n Please the gate(port) id and the state(0 for low, 1 for high)." << endl;
		cout << " (-1 to return the main page)" << endl;
	}

	void clear_screen() {
		system("pause");
		system("cls");
	}
};