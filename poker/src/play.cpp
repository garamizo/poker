#include "poker.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	poker::Hand h1({
		{0, 12},
		{3, 6},
		{2, 9},
		{1, 12}});

	poker::Hand h2({
		{0, 11},
		{3, 11},
		{2, 9},
		{1, 11}});

	vector<poker::Hand> hands = {h1, h2};
	sort(hands.begin(), hands.end());

	cout << hands[1] << endl;

	return 0;
}