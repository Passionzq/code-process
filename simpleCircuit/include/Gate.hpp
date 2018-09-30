#pragma once
#include<iostream>
#include<string>
#define MAX_OUT 16
using namespace std;

struct Node{
	int in[2], out;
	int Node_id;
	Node* prev[2], *next[MAX_OUT];
	Node(int input0, int input1, int output, Node* pre0, Node* pre1) {
		in[0] = input0;
		in[1] = input1;
		out = output;
		prev[0] = pre0;
		prev[1] = pre1;
	}
};

class Gate {
private:
	Node * gate;
	string name;
public:
	virtual void operate() = 0;

	virtual void set_name(string str) { name = str; }

	virtual string get_name() { return name; }

	virtual void set_port_state(int x) = 0;

	virtual void set_id(int x) { gate->Node_id = x; }

	virtual int get_id() { return gate->Node_id; }

	virtual void set_node() {
		gate = new Node(-1, -1, -1, NULL, NULL);
		for (int i = 0; i < MAX_OUT; ++i) {
			gate->next[i] = NULL;
		}
	}

	virtual Node* get_node() { return gate; }

	void clear(Node* gate) { delete gate; }

	virtual int get_free_port_num() {
		for (int i = 0; i < MAX_OUT; ++i) {
			if (gate->next[i] == NULL)
				return i;
		}
		return -1;
	}

	virtual bool connect(Gate* other, int other_num) {
		if (other != this) {
			if (get_free_port_num() != -1 && other->get_node()->prev[other_num] == NULL) {
				gate->next[get_free_port_num()] = other->get_node();
				other->get_node()->prev[other_num] = this->gate;
				return true;
			}
			else if (get_free_port_num() == -1) {
				cout << " No any port in this one any more." << endl;
				return false;
			}
			else if (other->get_node()->prev[other_num] != NULL) {
				cout << " Invaild operation." << endl;
				return false;
			}
		}
		else { 
			cout << "Invaild opreation."<<endl; 
			return false;
		}
	}

	virtual bool cancel(Gate* other, int other_num) {
		bool judgement = 0;
		if (other->get_node()->prev[other_num] != NULL) {
			for (int i = 0; i < MAX_OUT; ++i) {
				if (this->gate->next[i] == other->get_node()->prev[other_num]) {
					this->gate->next[i] = NULL;
					judgement = true;
					break;
				}
			}
			if (judgement) {
				other->get_node()->prev[other_num] = NULL;
				return true;
			}
			else { return false; }
		}
		else { 
			cout << "Sorry, this port doesn't connect any port. Pleaset check again." << endl;
			return false;
		}
	}

	bool operator+(Gate* other) {
		int port;
		cin >> port;
		return connect(other, port);
	}
};

