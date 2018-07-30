#ifndef _H_POKER_
#define _H_POKER_

#include <iostream>
#include <vector>
#include <algorithm>

namespace poker {

class Card {
public:
	int id;

	Card(int suit, int number) : id(number + suit*13) {};
	Card() {Card(0, 0);};
	int Suit() const { return(id / 13); };
	int Number() const { return(id % 13); };
	 
    bool operator<(Card& c2) const
    {
        return (Number() < c2.Number());
    }

    friend std::ostream& operator<<(std::ostream& os, Card& c); 
};

enum Combination {HIGH, PAIR, PAIR2, TRIPLE, STR8, FLUSH, FULL, FOURS, STR8FLUSH};
const char* combination_str[] = {"high", "pair", "2 pairs", "3 of a kind", "straight",
								 "flush", "full-house", "4 of a kind", "straight-flush"};

class Hand {
public:
	enum Combination combo;
	std::vector<Card> card;  // sorted

	Hand(const std::vector<Card>& cards);

	bool operator<(Hand & h2) const;
	friend std::ostream& operator<<(std::ostream& os, Hand& h);
};

}

#endif