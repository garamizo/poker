#include "poker.h"
#include <iostream>
#include <vector>

using namespace std;

void TestSort() {
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
}

void TestChances() {
    poker::Hand table({{0, 1},
                       {3, 6},
                       {2, 1},
                       {1, 11}});
    poker::Hand p1({{0, 12},
                    {2, 12}});

    std::vector<poker::Card*> id_inv(52, 0);
    for (int i = 0, size = table.card.size(); i < size; i++)
        id_inv[table.card[i].id] = (poker::Card*) &table.card[i];
    id_inv[p1.card[0].id] = (poker::Card*) &p1.card[0];
    id_inv[p1.card[1].id] = (poker::Card*) &p1.card[1];

    cout << WinChances(p1, table, id_inv) << endl;
}

int main(int argc, char* argv[]) {

    TestChances();
    return 0;
}