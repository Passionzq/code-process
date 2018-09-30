#pragma once
#include"Gate.hpp"

class Not :public Gate {
public:
	
	Not() {
		set_name("Not");
		set_node();
	}

	~Not() { clear(get_node()); }

	virtual void set_port_state(int x) {}

	virtual void operate() {
		if (get_node()->in[0] == -1 || get_node()->in[0] == 1) { get_node()->out = 0; }
		else if (get_node()->in[0] == 0) { get_node()->out = 1; }
		for (int i = 0; i < MAX_OUT; ++i) {
			if (get_node()->next[i] != NULL) {
				if (get_node()->next[i]->prev[0] == get_node() && get_node()->next[i]->prev[1] == get_node()){
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