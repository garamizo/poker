#include "poker.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	vector<poker::Hand> hands = {
		poker::Hand({{0, 1},
					 {3, 6},
					 {2, 9},
					 {1, 12}}),

		poker::Hand({{0, 12},
					 {3, 7},
					 {2, 9},
					 {1, 12}}),

		poker::Hand({{0, 12},
					 {3, 12},
					 {2, 12},
					 {1, 12}}),

		poker::Hand({{0, 12},
					 {3, 12},
					 {2, 12},
					 {1, 11}})
	};

	sort(hands.begin(), hands.end());
	for (int i = hands.size() - 1; i >= 0; i--)
		cout << hands[i] << endl << endl;

	return 0;
}