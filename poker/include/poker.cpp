#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

void Card::Print() {
	printf("%d %02d\n", Suit(), Number());
}

bool CmpCard(Card c1, Card c2) {
	return(c1.Number() < c2.Number());
}

int HandValue(Card cards[5]) {
	// 0-12 + 13*comb_type

	int nsuit[4], nnumber[13];
	std::fill_n(nsuit, 4, 0);
	std::fill_n(nnumber, 13, 0);
	for (int i = 0; i < 5; i++) {
		nsuit[cards[i].Suit()]++;
		nnumber[cards[i].Number()]++;
	}

	bool same_suit = nsuit[0] == 5 ||
					 nsuit[1] == 5 ||
					 nsuit[2] == 5 ||
					 nsuit[3] == 5;

	std::vector<int> seq_len, seq_head;
	int seq = 0;
	for (int i = 0; i < 13; i++) {
		seq++;

		if (nnumber[i] == 0) {
			seq_len.push_back(seq);
			seq_head.push_back(i);
			seq = 0;
		}
	}

	// cards_sort[0].Print();
	printf("%d %d\n", seq, seq_head);

	// straight flush

	return 0;
}