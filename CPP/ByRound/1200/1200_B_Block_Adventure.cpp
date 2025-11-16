// Problem: CF 1200 B - Block Adventure
// https://codeforces.com/contest/1200/problem/B

/*
B. Block Adventure
Purpose: Determine if it's possible to move a character from the first column to the last column of a row of blocks,
         given constraints on movement and block manipulation.

Algorithms/Techniques: Greedy approach with simulation
Time Complexity: O(n) per test case, where n is the number of columns
Space Complexity: O(1), only using a constant amount of extra space

The solution simulates movement from column 1 to column n.
At each step:
1. Check if we can move to the next column based on height difference (|h_i - h_{i+1}| <= k)
2. If not possible, we may need to adjust heights with available blocks
3. Update the remaining blocks in bag and current column height

Key variables:
- prev: height of previous column
- m: number of blocks in bag
- possible: flag indicating if game can be won
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    ll prev;
    scanf("%lld", &prev);
    bool possible(true); // Initially assume it's possible
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // If we cannot move due to height difference and have no blocks to adjust
      if (prev + m + k < x) {
        possible = false;
      } else {
        // Adjust available blocks based on height difference and current capacity
        m -= (((x > k) ? (x - k) : 0) - prev);
      }
      prev = x; // Update previous column height
    }
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/