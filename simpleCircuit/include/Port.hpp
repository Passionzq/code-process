#pragma once
#include"Gate.hpp"

class Port :public Gate {
public:
	int state;

	Port() {
		set_name("Port");
		set_node();
	}

	~Port() { clear(get_node()); }

	virtual void set_port_state(int x) {
		state = x;
		get_node()->in[0] = state; 
		operate();
	}

	virtual void operate() {
		get_node()->out = get_node()->in[0];
		for (int i = 0; i < MAX_OUT; ++i) {
			if (get_node()->next[i] != NULL) {
				if (get_node()->next[i]->prev[0] == get_node() && get_node()->next[i]->prev[1] == get_node()) {
					get_node()->next[i]->in[0] = get_node()->next[i]->in[1] = get_node()->out;
				}
				else if (get_node()->next[i]->prev[0] == get_node() && get_node()->next[i]->prev[1] != get_node()) {
					get_node()->next[i]->in[0] = get_node()->out;
				}
				else if (get_node()->next[i]->prev[0] != get_node() && get_node()->next[i]->prev[1] == get_node()) {
					get_node()->next[i]->in[1] = get_node()->out;
				}
			}
		}
	 }
};