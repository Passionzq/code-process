#pragma once
#include"display.hpp"
#include"Gate.hpp"
#include"And.hpp"
#include"Not.hpp"
#include"Port.hpp"
#include"Xor.hpp"
#include"Or.hpp"
#define MAX_GATE 64

class Test {
private:
	int number;
	Gate* hold[MAX_GATE];


public:

	Test() :number(0) {
		for (int i = 0; i < MAX_GATE; ++i) { hold[i] = NULL; }
	}
	~Test() { clear(); }

	void clear() {
		while (number) {
			delete hold[number - 1];
			--number;
		}
	}

	bool creat_port() {
		Gate* now = new Port;
		now->set_id(number);
		hold[number++] = now;
		return true;
	}

	bool creat_and() {
		Gate* now = new And;
		now->set_id(number);
		hold[number++] = now;
		return true;
	}

	bool creat_not() {
		Gate* now = new Not;
		now->set_id(number); 
		hold[number++] = now;
		return true;
	}

	bool creat_or() {
		Gate* now = new Or;
		now->set_id(number);
		hold[number++] = now;
		 return true;
	}

	bool creat_xor() {
		Gate* now = new Xor;
		now->set_id(number);
		hold[number++] = now;
		return true;
	}

	bool connect(int out_id, int in_id, int in_port) {
		if (hold[in_id]->get_name() == "Port") { return false; }
		else if (hold[in_id]->get_name() == "Not"&&hold[in_id]->get_node()->prev[0] != NULL) { return false; }
		else { return hold[out_id]->connect(hold[in_id], in_port); }
	}

	bool disconnect(int out_id, int in_id, int in_port) {
		return hold[out_id]->cancel(hold[in_id], in_port);
	}

	void setPort(int port_id, int state) {
		hold[port_id]->set_port_state(state);
	}

	void display_current_circuit() {
		bool judgement;
		if (number == 0) { cout << "No gate has been created." << endl; }
		else {
			cout << " The current circuit is as follows:" << endl
				<< "state: 0 == low   1 == high   -1==without connecting\n" << endl;
			for (int i = 0; i < number; ++i) {
				judgement = false;
				if (hold[i]->get_name() == "Not") {
					cout << " id: " << hold[i]->get_id() << endl
						<< " Kind: Not" << endl;
					if (hold[i]->get_node()->prev[0] == NULL) {
						cout << " previous gate's id: NULL";
					}
					else {
						cout << " previous gate's id: " << hold[i]->get_node()->prev[0]->Node_id;
					}
					cout << "\tInput state: " << hold[i]->get_node()->in[0] << endl;
					for (int j = 0; j < MAX_OUT; ++j) {
						if (hold[i]->get_node()->next[0] != NULL) { judgement = true; }
					}
					if (judgement) {
						for (int j = 0; j < MAX_OUT; ++j) {
							if (hold[i]->get_node()->next[j] != NULL) {
								cout << " next gate'sid: " << hold[i]->get_node()->next[j]->Node_id << "\t Output state: " << hold[i]->get_node()->out << endl;
							}
						}
					}
					else {
						cout << " next gate's id: NULL" << "\t Output state: " << hold[i]->get_node()->out << endl;
					}
				}
				else if (hold[i]->get_name() == "Port") {
					cout << " id: " << hold[i]->get_id() << endl
						<< "Kind: Port" << endl
						<< " previous gate's id: NULL" << "\tInput state: " << hold[i]->get_node()->in[0] << endl;
					for (int j = 0; j < MAX_OUT; ++j) {
						if (hold[i]->get_node()->next[0] != NULL) { judgement = true; }
					}
					if (judgement) {
						for (int j = 0; j < MAX_OUT; ++j) {
							if (hold[i]->get_node()->next[j] != NULL) {
								cout << "next gate's id: " << hold[i]->get_node()->next[j]->Node_id << "\t Output state: " << hold[i]->get_node()->out << endl;
							}
						}
					}
					else {
						cout << "next gate's id: NULL" << "\t Output state: " << hold[i]->get_node()->out << endl;
					}
				}
				else {
					cout << " id: " << hold[i]->get_id() << endl
						<< "Kind: " << hold[i]->get_name() << endl;
					for (int j = 0; j < 2; ++j) {
						if (hold[i]->get_node()->prev[j] != NULL) {
							cout << "previous gate's id: " << hold[i]->get_node()->prev[j]->Node_id << "\tInput state: " << hold[i]->get_node()->in[j] << endl;
						}
						else {
							cout << "previous gate's id: NULL" << "\tInput state: " << hold[i]->get_node()->in[j] << endl;
						}
					}
					for (int j = 0; j < MAX_OUT; ++j) {
						if (hold[i]->get_node()->next[0] != NULL) { judgement = true; }
					}
					if (judgement) {
						for (int j = 0; j < MAX_OUT; ++j) {
							if (hold[i]->get_node()->next[j] != NULL) {
								cout << "next gate's id: " << hold[i]->get_node()->next[j]->Node_id << "\t Output state: " << hold[i]->get_node()->out << endl;
							}
						}
					}
					else {
						cout << "next gate's id: NULL" << "\t Output state: " << hold[i]->get_node()->out << endl;
					}
				}
			}
			cout<<"\n";
		}
	}

	void simulate() {
		for (int j = 0; j < number; j++) {
			for (int i = 0; i < MAX_GATE; i++) {
				if (hold[i] != NULL)
					hold[i]->operate();
			}
		}
	}

	void run() {
		int choice = 0, choice_ = 0, in1, in2, port, for_throw;
		Display print;
		print.display_load_page();
		print.clear_screen();
		print.display_warning_page();
		print.clear_screen();
		while (choice != 8) {
			for_throw = 1;
			print.display_base_page();
			cin >> choice;
			system("cls");
			switch (choice) {
			case 1:
				try {
					if (number >= MAX_GATE)
						throw for_throw;
					else {
						print.display_creat_page();
						cin >> choice_;
						switch (choice_) {
						case 1:
							if (creat_port())  cout << " Creat scuessfully." << endl;
							else cout << " Fail to creat." << endl;
							break;
						case 2:
							if (creat_not()) cout << " Creat scuessfully." << endl;
							else cout << " Fail to creat." << endl;
							break;
						case 3:
							if (creat_and()) cout << " Creat scuessfully." << endl;
							else cout << " Fail to creat." << endl;
							break;
						case 4:
							if (creat_or()) cout << " Creat scuessfully." << endl;
							else cout << " Fail to creat." << endl;
							break;
						case 5:
							if (creat_xor()) cout << " Creat scuessfully." << endl;
							else cout << " Fail to creat." << endl;
							break;
						default:
							cout << " Invaild input.Please enter again." << endl;
							break;
						}
					}
				}
				catch(int) { cout << "\n\n\tThe number of gates has achieved the top." << endl; }
				print.clear_screen();
				break;
			case 2:
				print.display_connect_page();
				cin >> in1;
				if (in1 == -1) { system("cls"); }
				else {
					cin >> in2 >> port;
					try {
						if (in1 != in2 && in1 >= 0 && in1 < number&&in2 >= 0 && in2 < number && (port == 0 || port == 1) && connect(in1, in2, port)) {
							cout << " Connect sucessfully." << endl;
						}
						else { throw for_throw; }
					}
					catch (int) { cout << "Invaild input.Please check again." << endl; }
					print.clear_screen();
				}
				break;
			case 3:
				print.display_disconnect_page();
				cin >> in1;
				if (in1 == -1) { system("cls"); }
				else {
					cin >> in2 >> port;
					try {
						if (in1 != in2 && in1 >= 0 && in1 < number&&in2 >= 0 && in2 < number && (port == 0 || port == 1) && disconnect(in1, in2, port)) {
							cout << " Disconnect sucessfully." << endl;
						}
						else throw for_throw;
					}
					catch (int) { cout << "Invaild input.Please check again." << endl; }
					print.clear_screen();
				}
				break;
			case 4:
				display_current_circuit();
				print.clear_screen();
				break;
			case 5:
				try {
					if (number > 0) {
						simulate();
						cout << "simulate successfully." << endl;
					}
					else { throw for_throw; }
				}
				catch (int) { cout << "Please creat at least one gate before simulating." << endl; }
				print.clear_screen();
				break;
			case 6:
				print.display_state_page();
				cin >> in1;
				if (in1 == -1) { system("cls"); }
				else {
					cin >> in2;
					try {
						if (in1 >= 0 && in1 < number && (in2 == 0 || in2 == 1) && hold[in1]->get_name() == "Port") {
							setPort(in1, in2);
						}
						else { throw for_throw; }
					}
					catch (int) { cout << "Invaild input.Please check again."; }
					print.clear_screen();
				}
				break;
			case 7:
				print.display_rewrite_page();
				cin >> in1;
				if (number != 0 && in1 == 1) { clear(); }
				print.clear_screen();
				break;
			case 8:
				return;
				break;
			default:
				cout << "Invaild input.Please enter again." << endl;
				break;
			}
		}
	}
};