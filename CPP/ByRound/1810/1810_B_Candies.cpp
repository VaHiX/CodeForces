// Problem: CF 1810 B - Candies
// https://codeforces.com/contest/1810/problem/B

/*
B. Candies
Algorithms/Techniques: Reverse engineering of operations, binary representation logic.
Time Complexity: O(log n) per test case.
Space Complexity: O(log n) for storing the sequence.

This problem involves transforming 1 candy into exactly n candies using two specific spells:
- Spell 1 (a=1): x -> 2*x - 1
- Spell 2 (a=2): x -> 2*x + 1

The solution works by reversing the process: starting from n, we trace back to 1,
determining which spell was used at each step. This mirrors how binary numbers are built:
we look at the parity of (n - 1) and decide whether to apply reverse of spell 1 or 2.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    std::vector<int> seq;
    bool possible(true);
    while (x > 1) {
      if (x % 2 == 0) {           // If x is even, it's impossible to reach with given operations
        possible = false;
        break;
      }
      if ((x / 2) % 2) {          // Decide which operation was used based on (x/2) parity
        seq.push_back(2);         // Reverse of spell 2 (x -> 2*x + 1)
        x /= 2;                   // Apply reverse operation
      } else {
        seq.push_back(1);         // Reverse of spell 1 (x -> 2*x - 1)
        x = (x + 1) / 2;          // Apply reverse operation
      }
    }
    if (possible) {
      printf("%ld\n", seq.size());
      for (long p = seq.size() - 1; p >= 0; p--) {
        printf("%d ", seq[p]);    // Print the reversed sequence to get correct order
      }
      puts("");
    } else {
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/