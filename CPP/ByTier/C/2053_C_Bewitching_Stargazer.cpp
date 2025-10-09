// Problem: CF 2053 C - Bewitching Stargazer
// https://codeforces.com/contest/2053/problem/C

/*
C. Bewitching Stargazer
Algorithm: Simulation with binary representation interpretation
Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem simulates a recursive observation process on segments [l, r] where:
- If the segment length is even, it splits into two equal halves.
- If odd, it observes the middle element m and adds m to the lucky value,
  then recursively observes [l, m-1] and [m+1, r].
- Observations stop when segment length becomes less than k.

This process can be interpreted as traversing a binary tree of segments.
The key insight is that we only continue observing if the segment size >= k,
and in each such step, the contribution to the lucky value corresponds
to the binary representation bits of n, shifted appropriately based on k.

We simulate this using bit manipulation:
- While n >= k, check if n is odd (n % 2) and accumulate contributions.
- For each step, move to next level (n /= 2), and update cur = cur * 2.
- The final result is mul * sum / 2 where mul represents n+1 (initial contribution).
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll mul(n + 1), sum(0), cur(1);
    while (n >= k) {            // Continue observing only if segment size >= k
      sum += (n % 2) * cur;     // If n is odd, add current bit contribution to sum
      n /= 2;                   // Move up one level in the binary tree
      cur *= 2;                 // Update bit weight for next level
    }
    printf("%lld\n", mul * sum / 2);  // Final lucky value computed
  }
}


// https://github.com/VaHiX/codeForces/