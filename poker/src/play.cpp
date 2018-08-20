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
                       {1, 11},
                       {2, 5}});
    poker::Hand p1({table.card[0], table.card[1], table.card[2], table.card[3], table.card[4],
                    {0, 12},
                    {2, 12}});

    vector<int> id_inv(52, 0);
    for (int i = 0, size = p1.card.size(); i < size; i++)
        id_inv[table.card[i].id] = 1;

    int nloss = 0, count = 0;
    float prob = 100 * WinChances(p1, table, id_inv, nloss, count, 3);  // prob of p1 win

    cout << "P1 win chances: " << prob << endl;
    cout << p1 << endl;
}

int main(int argc, char* argv[]) {

    TestChances();
    return 0;
}