// Problem: CF 1956 B - Nene and the Card Game
// https://codeforces.com/contest/1956/problem/B

/*
Problem: B. Nene and the Card Game

Algorithms/Techniques: Simulation with greedy strategy using hash set to track cards on table.

Time Complexity: O(n) per test case, where n is the number of cards per player.
Space Complexity: O(n), for storing the set of cards already placed on the table.

The game involves two players (you and Nene) taking turns placing cards on a table,
with each card having a value from 1 to n. Each value appears exactly twice across all cards.
Each turn, a player selects a card from their hand:
- If the same value is already on the table, they score 1 point.
- The selected card is then placed on the table.

Nene plays optimally, trying to maximize her own score first and minimize your score second.
This simulation mimics how you would play to achieve maximum points under such constraints.
We iterate through each of your cards and determine when you can score a point by seeing if
the value was already played (i.e., present in the set). If so, increment counter `cnt`.
Otherwise, insert it into the set as it will be placed on the table.

*/

#include <cstdio>
#include <unordered_set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::unordered_set<long> s; // Set to keep track of cards already on the table
    long cnt(0);                // Counter for points you can get
    for (long p = 0; p < n; p++) { // For each card in your hand
      long x;
      scanf("%ld", &x);
      if (s.count(x)) {         // If this value is already on the table, you get a point
        ++cnt;
      } else {
        s.insert(x);            // Otherwise, place the card on the table
      }
    }
    printf("%ld\n", cnt);       // Output maximum points you can get
  }
}


// https://github.com/VaHiX/codeForces/