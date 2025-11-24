// Problem: CF 1695 B - Circle Game
// https://codeforces.com/contest/1695/problem/B

/* 
B. Circle Game
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Algorithms/Techniques: 
- Game theory and optimal play strategy
- Greedy approach to determine winner based on parity of n and minimum element index

The game is played in a circle where players alternate turns removing stones from piles.
Mike goes first. If a player cannot remove stones, they lose.

Key observations:
1. If n is odd, Mike always wins because he can always make a move that forces Joe into a losing position.
2. If n is even:
   - Find the index of the minimum pile.
   - If the index is odd, Joe wins (because he can always mirror Mike's moves).
   - If the index is even, Mike wins (same reason as above).

This logic handles all cases where optimal play leads to a deterministic outcome.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    if (n % 2) { // If number of piles is odd, Mike always wins
      puts("Mike");
      continue;
    }
    long idx(0); // Find index of minimum element
    for (long p = 0; p < n; p++) {
      if (a[p] < a[idx]) {
        idx = p;
      }
    }
    // If the index of the smallest pile is odd, Joe wins. Otherwise, Mike wins.
    puts(idx % 2 ? "Mike" : "Joe");
  }
}


// https://github.com/VaHiX/codeForces/