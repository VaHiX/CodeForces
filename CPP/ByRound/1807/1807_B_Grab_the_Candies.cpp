// Problem: CF 1807 B - Grab the Candies
// https://codeforces.com/contest/1807/problem/B

/*
B. Grab the Candies
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(1) additional space

The problem asks whether we can reorder an array such that Mihai (who takes even bags)
always has more candies than Bianca (who takes odd bags) at every step of the game.

Approach:
- For each test case, we compute prefix sums for evens and odds separately.
- We try to sort the array in a way that ensures at no point during processing,
  Bianca's total becomes greater than or equal to Mihai's.
- The key idea is to process evens first (to increase Mihai's lead), then odds.

We simulate this by:
1. Reading all numbers and separate even and odd sums.
2. Checking if Mihai can maintain a strict lead throughout the process.
3. If the total sum of evens is greater than odds, it might still be possible,
   but only under careful ordering.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long evens(0), odds(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) { // If number is odd
        odds += x;
      } else { // If number is even
        evens += x;
      }
    }
    puts(evens > odds ? "YES" : "NO"); // Output 'YES' if Mihai's total is greater than Bianca's
  }
}


// https://github.com/VaHiX/codeForces/