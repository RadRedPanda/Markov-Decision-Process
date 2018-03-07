#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class state
{
public:
	friend class policy;
	state();
	state(double r);
	string getPol();
private:
	double reward;
	double utility;
	double uprime;
	string pol;
};