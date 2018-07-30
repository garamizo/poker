#include "poker.h"

namespace poker {

std::ostream& operator<<(std::ostream& os, Card& c)  
{  
    os << "(" << c.Suit() << ' ' << c.Number() << ")";  
    return os;  
}

bool Hand::operator<(Hand& h2) const
{
    if (combo != h2.combo)
        return (combo < h2.combo);

    for (int i = 0, size = card.size(); i < size; i++)
        if (card[i] < h2.card[i])
            return (true);

    return (false);
}


Hand::Hand(const std::vector<Card>& cards)
{
    // build inverted lists
    std::vector<std::vector<Card>> suit_inv(4),
                                   number_inv(13);
    std::vector<Card*> id_inv(52, 0);
    for (int i = 0, size = cards.size(); i < size; i++) {
        number_inv[cards[i].Number()].push_back(cards[i]);
        suit_inv[cards[i].Suit()].push_back(cards[i]);
        id_inv[cards[i].id] = (Card*) &cards[i];
    }

    // straight flush
    for (int j = 12; j >= 4; j--)  // for each number
        for (int i = 0; i < 4; i++) {  // for each suit
            int card_id = j + i*13;
            if (id_inv[card_id] && id_inv[card_id-1] && id_inv[card_id-2] &&
                id_inv[card_id-3] && id_inv[card_id-4])
            {
                combo = STR8FLUSH;
                card = {*id_inv[card_id], *id_inv[card_id-1], *id_inv[card_id-2],
                             *id_inv[card_id-3], *id_inv[card_id-4]};
                return;
            }
    }

    // fours
    for (int i = 12; i >= 0; i--)
        if (number_inv[i].size() == 4) {
            combo = FOURS;
            card.resize(4);
            std::copy(number_inv[i].begin(), number_inv[i].begin() + 4, card.begin());

            // complete hand with highest card
            for (int j = 12; j >= 0 && card.size() < 5; j--)
                if (number_inv[j].size() > 0 && j != i)
                    card.push_back(number_inv[j][0]);
            return;
        }

    // full-house
    for (int i = 12; i >= 0; i--)
        if (number_inv[i].size() == 3) {
            // complete hand with highest pair
            for (int j = 12; j >= 0; j--)
                if (number_inv[j].size() >= 2 && j != i) {
                    combo = FULL;
                    card.resize(5);
                    std::copy(number_inv[i].begin(), number_inv[i].begin() + 3, card.begin());
                    std::copy(number_inv[j].begin(), number_inv[j].begin() + 2, card.begin() + 3);
                    return;
                }
        }

    // flush
    for (int i = 0; i < 4; i++)
        if (suit_inv[i].size() >= 5) {
            combo = FLUSH;
            // store sorted
            std::sort(suit_inv[i].begin(), suit_inv[i].end());
            card.resize(5);
            std::reverse_copy(suit_inv[i].end()-5, suit_inv[i].end(), card.begin());
            return;
        }

    // straight
    for (int j = 12; j >= 4; j--) {  // for each number
        if (number_inv[j].size() && number_inv[j-1].size() && number_inv[j-2].size() &&
            number_inv[j-3].size() && number_inv[j-4].size())
        {
            combo = STR8;
            card = {number_inv[j][0], number_inv[j-1][0], number_inv[j-2][0],
                         number_inv[j-3][0], number_inv[j-4][0]};
            return;
        }
    }

    // 3s
    for (int i = 12; i >= 0; i--)
        if (number_inv[i].size() == 3) {
            combo = TRIPLE;
            card.resize(3);
            std::copy(number_inv[i].begin(), number_inv[i].begin() + 3, card.begin());

            // complete hand with highest cards
            for (int j = 12; j >= 0 && card.size() < 5; j--)
                if (number_inv[j].size() > 0 && j != i)
                    card.push_back(number_inv[j][0]);
            return;
        }

    // 2 pairs
    for (int i = 12; i >= 0; i--)
        if (number_inv[i].size() == 2) {
            // complete hand with highest pair
            for (int j = i-1; j >= 0; j--)
                if (number_inv[j].size() == 2) {
                    combo = PAIR2;
                    card.resize(4);
                    std::copy(number_inv[i].begin(), number_inv[i].begin() + 2, card.begin());
                    std::copy(number_inv[j].begin(), number_inv[j].begin() + 2, card.begin() + 2);
                    // complete hand with highest card
                    for (int k = 12; k >= 0 && card.size() < 5; k--)
                        if (number_inv[k].size() > 0 && k != i && k != j)
                            card.push_back(number_inv[k][0]);
                    return;
                }
        }

    // pair
    for (int i = 12; i >= 0; i--)
        if (number_inv[i].size() == 2) {
            combo = PAIR;
            card = {number_inv[i][0], number_inv[i][1]};

            // complete hand with highest cards
            for (int j = 12; j >= 0 && card.size() < 5; j--)
                if (number_inv[j].size() > 0 && j != i)
                    card.push_back(number_inv[j][0]);
            return;
        }

    // high
    combo = HIGH;
    for (int j = 12; j >= 0 && card.size() < 5; j--)
        if (number_inv[j].size() > 0)
            card.push_back(number_inv[j][0]);
}

std::ostream& operator<<(std::ostream& os, Hand& h)  
{
    os << "Combo: " << combination_str[h.combo] << "\nCards: ";
    for (int i = 0; i < h.card.size(); i++)
        os << h.card[i] << ", ";  
    return os;  
}


float WinChances(Hand& p, Hand& t, std::vector<Card*> card_inv) {
    // For Texas Holdem
    //  p: player hand (2 cards)
    //  t: incomplete table hand (up to 5 cards)
    //  num_players: players on game

    // table hand is still incomplete
    if (t.card.size() < 5) {
        float prob = 0;
        int count = 0;
        for (int i = 0, size = card_inv.size(); i < size; i++)
            if (card_inv[i]) {
                Card* draw = card_inv[i];
                t.card.push_back(*draw);
                card_inv[i] = 0;
                Hand t1(t.card);

                prob += WinChances(p, t1, card_inv);
                count++;

                card_inv[i] = draw;
                t.card.pop_back();
            }
        return (prob / count);
    }

    // guess oponents hands
    int nloss = 0,
        count = 0;
    for (int i = 0, size = card_inv.size(); i < size; i++) {
        if (!card_inv[i]) continue;

        Card* drawi = card_inv[i];
        t.card.push_back(*drawi);
        card_inv[i] = 0;

        for (int j = 0; j < size; j++) {
            if (!card_inv[j]) continue;

            Card* drawj = card_inv[j];
            t.card.push_back(*drawi);
            card_inv[j] = 0;

            Hand p1({t.card[0], t.card[1], t.card[2], t.card[3], t.card[4], p.card[0], p.card[1]});
            Hand p2({t.card[0], t.card[1], t.card[2], t.card[3], t.card[4], *drawi, *drawj});
            if (p1 < p2) nloss++;
            count++;

            card_inv[j] = drawj;
            t.card.pop_back();
        }

        card_inv[i] = drawi;
        t.card.pop_back();
    }

    float prob = float(count - nloss) / count;
    return (prob);
}

}



