#pragma once
#include "state.h"

using namespace std;

class policy
{
public:
	policy();
	policy(vector<double> rewards, int width);
	void printPolicy();
	double bellman();
	double bellman(double disc);
	int getUp(int s);
	int getDown(int s);
	int getLeft(int s);
	int getRight(int s);
private:
	vector<state> stateSpace;
	int height;
	int width;
};

