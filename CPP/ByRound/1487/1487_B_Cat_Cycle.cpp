// Problem: CF 1487 B - Cat Cycle
// https://codeforces.com/contest/1487/problem/B

/*
B. Cat Cycle
Algorithm: Simulation with Mathematical Optimization
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem simulates two cats moving through n sleeping spots in cyclic patterns:
- Cat A moves in decreasing order: n, n-1, ..., 1, n, n-1, ...
- Cat B moves in increasing order: 1, 2, ..., n, 1, 2, ...

When both cats want the same spot, Cat A takes it and Cat B skips to the next available spot
in its sequence. The key insight is to precompute how many times Cat B has to skip due to
Cat A occupying spots, which can be calculated mathematically.

The algorithm calculates the effective position of Cat B after k hours by adjusting for
the skipped positions caused by Cat A's occupation.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    --k; // Convert to 0-based indexing for easier calculation
    
    if ((n % 2)) { // If n is odd
      // Adjust k to account for skipped positions caused by Cat A's occupancy
      k += k / (n / 2);
    }
    
    // Final position of Cat B after k hours, adjusted back to 1-based indexing
    printf("%lld\n", 1 + (k % n));
  }
}


// https://github.com/VaHiX/codeForces/