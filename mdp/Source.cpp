#include "policy.h"

using namespace std;

int main() {
	policy mdp, vsix;
	double error = 0.0001;
	double discount = 0.96;
	double delta = mdp.bellman();

	// V*
	cout << "V*" << endl;
	while (delta >= error*(1 - discount) / discount)	// loops until delta is negligible
		delta = mdp.bellman(discount);
	mdp.printPolicy();
	
	// V6
	cout << "V6" << endl;
	for(int i=0; i<6; i++)	// loops only 6 times
		vsix.bellman();
	vsix.printPolicy();
	
	system("PAUSE");
	return 0;
}