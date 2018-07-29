#include "poker.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	// Card cards[] = {
	// 	Card(0, 5),
	// 	Card(1, 4),
	// 	Card(2, 1),
	// 	Card(1, 3),
	// 	Card(3, 2) };
	std::vector<Card> cards({
		Card(0, 5),
		Card(3, 10),
		Card(2, 6),
		Card(3, 6),
		Card(3, 7),
		Card(3, 8),
		Card(3, 9) });

	// card.Print();
	// printf("%d\n", HandValue(cards));
	// EvalHand(cards);
	// std::cout << cards[0] << std::endl;
	Hand hand = EvalHand(cards);
	cout << hand << endl;

	return 0;
}