#include "policy.h"

// the base constructor, creates the given 4x4 grid with rewards
policy::policy(){
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(3));
	stateSpace.push_back(state(10));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(5));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(60));
	stateSpace.push_back(state(5));
	stateSpace.push_back(state(10));
	stateSpace.push_back(state(5));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(45));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(0));
	stateSpace.push_back(state(5));
	width = 4;
	height = 4;
}

// custom constructor, didn't use it
policy::policy(vector<double> rewards, int w) {
	for (int i = 0; i < rewards.size(); i++) {
		state temp(rewards[i]);
		stateSpace.push_back(temp);
	}
	width = w;
	height = rewards.size() / w;
}

double policy::bellman() {
	return bellman(1);
}

// performs one iteration of the bellman equation
double policy::bellman(double discount) {
	double delta = 0;
	for (int i = 0; i < stateSpace.size(); i++) {	// sets all U to U'
		stateSpace[i].utility = stateSpace[i].uprime;
	}
	for (int i = 0; i < stateSpace.size(); i++) {
		double up, down, left, right, maximum;
		up = down = left = right = 0.1 * stateSpace[i].utility;	// finds values of all avaliable moves
		up += stateSpace[getUp(i)].utility * 0.7 + stateSpace[getDown(i)].utility * 0.2;
		down += stateSpace[getDown(i)].utility * 0.7 + stateSpace[getUp(i)].utility * 0.2;
		left += stateSpace[getLeft(i)].utility * 0.7 + stateSpace[getRight(i)].utility * 0.2;
		right += stateSpace[getRight(i)].utility * 0.7 + stateSpace[getLeft(i)].utility * 0.2;
		maximum = max(max(up, down), max(left, right));			// gets maximum
		stateSpace[i].pol[0] = (maximum == up);
		stateSpace[i].pol[1] = (maximum == down);	// these are to know which direction to point
		stateSpace[i].pol[2] = (maximum == left);
		stateSpace[i].pol[3] = (maximum == right);
		stateSpace[i].uprime = stateSpace[i].reward + discount * maximum;	// sets U'
		delta = max(stateSpace[i].uprime - stateSpace[i].utility, delta);	// sets delta
	}
	return delta;
}

// prints out the utility grid with values and the policy with arrows
void policy::printPolicy() {
	/*
	cout << "Rewards";
	for (int i = 0; i < stateSpace.size(); i++) {
		if (i%width == 0)
			cout << endl << "-----------------------------------------------------------------" << endl << "|\t";
		cout << stateSpace[i].reward << "\t|\t";
	}
	cout << endl << "-----------------------------------------------------------------" << endl << endl;
	*/	// this part prints out the reward, I removed it since it was redundant
	cout << "Utilities";
	for (int i = 0; i < stateSpace.size(); i++) {
		if (i%width == 0)
			cout << endl << "-----------------------------------------------------------------" << endl << "|\t";
		cout << stateSpace[i].utility << "\t|\t";
	}
	cout << endl << "-----------------------------------------------------------------" << endl << endl;

	cout << "Optimal Policy";
	for (int i = 0; i < stateSpace.size(); i++) {
		if (i%width == 0)
			cout << endl << "-----------------------------------------------------------------" << endl << "|\t";
		cout << stateSpace[i].getPol() << "\t|\t";
	}
	cout << endl << "-----------------------------------------------------------------" << endl << endl;
}

// the next four functions return the state that is in the respective direction, and if there is none, it returns itself
int policy::getUp(int s) {
	if (s - width >= 0)
		return s - width;
	return s;
}

int policy::getDown(int s) {
	if (s + width < stateSpace.size())
		return s + width;
	return s;
}

int policy::getLeft(int s) {
	if (s % width != 0)
		return s - 1;
	return s;
}

int policy::getRight(int s) {
	if ((s + 1) % width != 0)
		return s + 1;
	return s;
}