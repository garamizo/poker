#ifndef _H_POKER_
#define _H_POKER_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

// enum Outcome {INVALID, UNKNOWN, LOSE, WIN};

// class Poker {
// private:
// 	// union {
// 	// 	int m[3][3];
// 	// 	int v[9];
// 	// };
// 	int turn;  // -1 (over), 1 (player 1), 2 (player 2)
// 	float pot;

// 	void Undo(int move);
// 	Outcome TestMove(int move);

// public:
// 	Velha() { Velha(1); };
// 	Velha(int start_player);
// 	bool Play(int move);
// 	int PlanSilly();
// 	int PlanSmart();
// 	int State(); // ongoing (0), tie (-1), p1 wins (1), p2 wins (2)
// 	void Print();
// 	int Query();
// 	int Turn() {return turn;};
// 	void PrintStrategy();
// };

enum PokerCombo {HIGH, PAIR, PAIR2, TRIPLE, STR8, FLUSH, FULL, FOUR, STR8FLUSH};

class Card {
public:
	int id;

	Card(int suit, int number) : id(number + suit*13) {};
	Card() {Card(0, 0);};
	int Suit() { return(id / 13); };
	int Number() { return(id % 13); };
	void Print();
};

struct Combination {
	PokerCombo combo;
	std::vector<Card*> card;
	int Value();
};

Combination HandValue(std::vector<Card> cards);

#endif