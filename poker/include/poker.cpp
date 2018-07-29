#include "poker.h"


std::ostream& operator<<(std::ostream& os, const Card& c)  
{  
    os << "(" << c.Suit() << ' ' << c.Number() << ")";  
    return os;  
}

bool operator> (const Hand& h1, const Hand & h2)
{
	// TODO fill in tie criteria
    return  h1.combo > h2.combo;
}



Hand EvalHand(std::vector<Card> cards)
{
	Hand hand;

	// build inverted lists
	int nsuit[4], nnumber[13], ncard[52];
	std::fill_n(nsuit, 4, 0);
	std::fill_n(nnumber, 13, 0);
	std::fill_n(ncard, 52, 0);
	for (int i = 0; i < cards.size(); i++) {
		nsuit[cards[i].Suit()]++;
		nnumber[cards[i].Number()]++;
		ncard[cards[i].id]++;
	}

	int seq_top = -1;
	int flush_suit;

	// straight flush
	for (int i = 0; i < 4; i++) {  // for each suit
		for (int j = 12; j >= 4; j--) {  // for each number
			int card_id = j + i*13;
			if (ncard[card_id] && ncard[card_id-1] && ncard[card_id-2] &&
				ncard[card_id-3] && ncard[card_id-4] && j > seq_top)
			{
				seq_top = j;
				flush_suit = i;
				break;
			}
		}
		int cid = 3 + i*13;
		if (ncard[cid] && ncard[cid-1] && ncard[cid-2] &&
			ncard[cid-3] && ncard[cid+12] && 3 > seq_top)
		{
			seq_top = 3;
			flush_suit = i;
		}
	}
	if (seq_top >= 0) {
		hand.combo = STR8FLUSH;
		for (int i = 0; i < 4; i++)
			hand.card.push_back(Card(flush_suit, seq_top-i));
		if (seq_top-4 == -1)
			hand.card.push_back(Card(flush_suit, 12));
		else
			hand.card.push_back(Card(flush_suit, seq_top-4));

		return (hand);
	}

	// // fours
	// for (int i = 12; i >= 4; i--)
	// 	if (nnumber[i] >= 4) {
	// 		hand.combo = FOURS;
	// 		for (int j = 0; j < 4; j++)
	// 			hand.card.push_back(Card(j, i));
			
	// 	}

	printf("%d %d\n", seq_top, flush_suit);

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

	

	
	return hand;
}

std::ostream& operator<<(std::ostream& os, Hand& h)  
{
	os << "Combo: " << h.combo << "\nCards: ";
	for (int i = 0; i < 5; i++)
    	os << h.card[i] << ", ";  
    return os;  
}

