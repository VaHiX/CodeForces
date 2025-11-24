// Problem: CF 1637 C - Andrew and Stones
// https://codeforces.com/contest/1637/problem/C

/*
C. Andrew and Stones
Purpose: Given an array of piles with stones, determine the minimum number of operations to move all stones into the first and last pile using a specific operation that transfers 2 stones from a middle pile to the first and last pile respectively.

Algorithm/Techniques:
- Greedy approach with checking impossible cases.
- The key insight is that we can only move stones from the middle piles using operations, so we must ensure enough stones exist in the middle pile to allow transformations.
- If the middle pile has at least 2 stones, it can perform an operation; otherwise, it's impossible if all others are 1.

Time Complexity: O(n) per test case
Space Complexity: O(1)

The operation allows transfer of 2 stones from a middle pile j (with at least 2 stones) to piles i and k (where i < j < k). 
We simulate moving all stones into the first and last pile by accumulating how many operations are needed,
but also verify conditions for impossibility.
*/
#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool ones(true), threeodd(false); // ones tracks if all middle piles have 1 stone, threeodd checks for odd count in middle when n=3
    ll cnt(0);
    for (long p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (p == 0 || p == n - 1) {
        continue; // Skip first and last piles, as they are not involved in operations
      }
      if (n == 3 && p == 1) {
        threeodd = x % 2; // Only check middle pile for odd count when n=3
      }
      if (x > 1) {
        ones = false; // Mark that there exists a pile with more than 1 stone in the middle
      }
      cnt += (x + 1) / 2; // Accumulate number of operations needed to bring stones to first/last pile
    }
    bool impossible = ones || threeodd; // Impossible if all middle piles have 1 stone OR if n=3 and middle has odd count
    printf("%lld\n", impossible ? (-1) : cnt);
  }
}


// https://github.com/VaHiX/codeForces/