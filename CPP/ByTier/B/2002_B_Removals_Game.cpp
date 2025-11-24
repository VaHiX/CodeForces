// Problem: CF 2002 B - Removals Game
// https://codeforces.com/contest/2002/problem/B

/*
B. Removals Game
Algorithm/Technique: Greedy + Simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves two players (Alice and Bob) playing a game where they alternately remove elements
from the front or back of their respective arrays. The game ends when both have one element left.
If the remaining elements are equal, Bob wins; otherwise Alice wins.

Key Insight:
For optimal play, we simulate the game by checking whether the final remaining elements can be made equal
by choosing appropriately from the ends. We check two conditions:
1. Whether the arrays are identical (fs flag)
2. Whether the reversed array of Alice matches Bob's array (fr flag)

If either condition is true, Bob can win by mirroring Alice's choices.
Otherwise, Alice can always choose a strategy to ensure the remaining elements differ.

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
    bool fs(true), fr(true); // fs: flag for identical arrays, fr: flag for reverse match
    for (long p = 0; p < n; p++) {
      long b;
      scanf("%ld", &b);
      if (b != a[p]) {       // Check if current element matches Alice's array
        fs = false;
      }
      if (b != a[n - 1 - p]) { // Check if current element matches reverse of Alice's array
        fr = false;
      }
    }
    puts(fs || fr ? "Bob" : "Alice"); // If either condition holds, Bob wins
  }
}


// https://github.com/VaHiX/codeForces/