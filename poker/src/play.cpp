#include "poker.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	Card cards[] = {
		Card(0, 5),
		Card(1, 4),
		Card(2, 1),
		Card(1, 3),
		Card(3, 2) };

	// card.Print();
	// printf("%d\n", HandValue(cards));
	HandValue(cards);

	return 0;
}