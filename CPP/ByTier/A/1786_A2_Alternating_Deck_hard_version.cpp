// Problem: CF 1786 A2 - Alternating Deck (hard version)
// https://codeforces.com/contest/1786/problem/A2

/*
A2. Alternating Deck (hard version)
Algorithm: Simulation of card dealing process with alternating player turns.
Time Complexity: O(n) per test case, where n is the number of cards.
Space Complexity: O(1), only using a constant amount of extra variables.

The problem simulates dealing cards from a deck where:
- Cards are dealt in a pattern: 1 to Alice, 2 to Bob, 3 to Bob, 4 to Alice, etc.
- Players alternate every two steps.
- At each step, the number of cards taken equals the step number (or remaining cards if less).
- The first card is white, and colors alternate throughout the deck.

This implementation simulates the dealing process and counts how many white and black cards
each player ends up with.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long rem(n), aw(0), ad(0), bw(0), bd(0), sw(1); // aw: Alice white, ad: Alice dark, bw: Bob white, bd: Bob dark, sw: switch (who gets next)
    for (long p = 1; rem > 0 && p <= n; p++) {
      long take = (rem < p) ? rem : p;                    // How many cards to take in this step
      long tw = (take + sw) / 2;                          // White cards allocated to current player
      long td = (take + (1 - sw)) / 2;                    // Black cards allocated to current player
      if (p % 2) {                                        // Every odd-numbered turn, switch players
        sw = 1 - sw;
      }
      if (p % 4 <= 1) {                                   // If step is 1,2,5,6,... allocate to Alice
        aw += tw;
        ad += td;
      } else {                                            // Else, allocate to Bob
        bw += tw;
        bd += td;
      }
      rem -= take;                                        // Reduce remaining cards
    }
    printf("%ld %ld %ld %ld\n", aw, ad, bw, bd);
  }
}


// https://github.com/VaHiX/codeForces/