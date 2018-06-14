#include "poker.h"

int Combination::Value() {
	return 0;
}

void Card::Print() {
	printf("%d %02d\n", Suit(), Number());
}

bool CmpCard(Card c1, Card c2) {
	return(c1.Number() < c2.Number());
}

Combination HandValue(std::vector<Card> cards) {
	// 0-12 + 13*comb_type

	int nsuit[4], nnumber[13], ncard[52];
	std::fill_n(nsuit, 4, 0);
	std::fill_n(nnumber, 13, 0);
	for (int i = 0; i < cards.size(); i++) {
		nsuit[cards[i].Suit()]++;
		nnumber[cards[i].Number()]++;
		ncard[cards[i].id]++;
	}

	int flush_suit;
	bool same_suit = nsuit[0] >= 5 ||
					 nsuit[1] >= 5 ||
					 nsuit[2] >= 5 ||
					 nsuit[3] >= 5;

	int seq_unsuited = -1;
	for (int i = 12; i >= 4; i--) {
		if (nnumber[i] && nnumber[i-1] && nnumber[i-2] &&
			nnumber[i-3] && nnumber[i-4]) {
			seq_unsuited = i;
			break;
		}
	}

	int str8flush_top = -1;
	for (int i = 0; i < 4; i++) {
		for (int j = 12; j >= 4; j--) {
			int cid = j + i*13;
			if (ncard[cid] && ncard[cid-1] && ncard[cid-2] &&
				ncard[cid-3] && ncard[cid-4])
				if (j > str8flush_top) {
					str8flush_top = j;
					flush_suit = i;
					break;
				}
		}
		int cid = i*13 + 3;
		if (ncard[cid] && ncard[cid-1] && ncard[cid-2] &&
			ncard[cid-3] && ncard[cid-4])
			if (3 > str8flush_top) {
				str8flush_top = 3;
				flush_suit = i;
			}
	}

	// cards_sort[0].Print();
	printf("%d %d\n", same_suit, seq_unsuited);

	// straight flush

	Combination combo;
	return combo;
}