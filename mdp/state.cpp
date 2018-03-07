#include "state.h"

state::state(){
	reward = 0;
	utility = 0;
	uprime = 0;
	pol = "0000";
}

state::state(double r) {
	reward = r;
	utility = 0;
	uprime = 0;
	pol = "0000";
}

string state::getPol() {
	string temp = "";
	if (pol[0])
		temp += "^";
	if (pol[1])
		temp += "v";
	if (pol[2])
		temp += "<";
	if (pol[3])
		temp += ">";
	return temp;
}