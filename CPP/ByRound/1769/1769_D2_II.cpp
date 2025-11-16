// Problem: CF 1769 D2 - Игра в Девятку II
// https://codeforces.com/contest/1769/problem/D2

/*
Code purpose:
This code generates k distinct card distributions for a card game called "Nine"
(Девятка) where each distribution has a unique "importance of the first move"
value. The game involves two players (Alice and Bob) with 18 cards each from a
36-card deck (9 ranks × 4 suits). Players play optimally to minimize the cards
left in the opponent's hand when they win. The "importance of the first move" is
the absolute difference in the number of cards remaining in the loser's hand
between scenarios where Alice or Bob goes first.

Algorithms/Techniques:
- Bit manipulation to represent card hands as masks
- Precomputed masks for specific card distributions designed to create varying
'importance of the first move' values
- The 36-card deck is represented as 36 bits, with each bit corresponding to a
unique card

Time Complexity: O(k * N * T) where N=9 (ranks) and T=4 (suits) - for generating
and printing k distributions Space Complexity: O(1) - fixed size arrays and
masks, not dependent on input size k beyond the output size

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); i++)
using ll = long long;
const int N = 9, T = 4;
const char *SUITS = "CDSH";
const char *VALS = "6789TJQKA";
vector<ll> masks = {
    67515452935, 67515454987, 67515456011, 67515456013, 67515456523,
    67515456525, 67515456526, 67517553677, 67517553678, 67517558284,
    67518604813, 67521752588, 19592278700, 34336059520, 32688256024,
    10934253124, 21497764062, 953865822,   54567319559, 26364203238,
    20511443181, 67643379720, 67642331145, 67642331148, 67634991116,
    67626602508,
};
string card(int k) { return {VALS[k % N], SUITS[k / N]}; }
void print(ll mask) {
  forn(j, T * N) {
    if ((mask >> j) & 1) {
      cout << card(j) << " "; // Output a card if bit j is set
    }
  }
  cout << "\n";
}
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int k;
  cin >> k;
  ll full = (1ll << (T * N)) - 1; // All 36 bits set for full deck
  forn(i, k) {
    print(masks[i]);        // Print Alice's cards
    print(full - masks[i]); // Print Bob's cards (complement)
    cout << "\n";
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/