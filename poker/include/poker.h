#ifndef _H_POKER_
#define _H_POKER_

#include <iostream>
#include <vector>
#include <algorithm>


class Card {
public:
	int id;

	Card(int suit, int number) : id(number + suit*13) {};
	Card() {Card(0, 0);};
	int Suit() const { return(id / 13); };
	int Number() const { return(id % 13); };
	
	friend std::ostream& operator<<(std::ostream& os, const Card& c);  
};

enum Combination {HIGH, PAIR, PAIR2, TRIPLE, STR8, FLUSH, FULL, FOURS, STR8FLUSH};

struct Hand {
	enum Combination combo;
	std::vector<Card> card;  // sorted
	friend bool operator> (const Hand& h1, const Hand & h2);
	friend std::ostream& operator<<(std::ostream& os, Hand& h);
};

Hand EvalHand(std::vector<Card> cards);

#endif