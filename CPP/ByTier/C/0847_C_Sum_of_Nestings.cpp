// Problem: CF 847 C - Sum of Nestings
// https://codeforces.com/contest/847/problem/C

/*
 * Code Purpose: Construct a regular bracket sequence of length 2*n with total nesting sum equal to k.
 * 
 * Algorithm/Techniques:
 * - Greedily build the sequence by maintaining current nesting level 'cur'.
 * - For each position, decide whether to place '(' or ')' based on how much nesting we can still assign.
 * - The maximum possible nesting sum for n opening brackets is n*(n-1)/2 (when all brackets are nested maximally).
 * 
 * Time Complexity: O(n) - single pass through 2*n positions.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cstdio>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  // Check if it's even possible to achieve the required sum k
  if (n * (n - 1) / 2 < k) {
    puts("Impossible");
  } else {
    ll cur(0); // Current nesting level
    for (ll p = 1; p <= 2 * n; p++) {
      // If current nesting can be increased without exceeding k
      if (cur <= k) {
        k -= cur;   // Reduce remaining k by current nesting
        ++cur;      // Increase nesting level
        putchar('('); // Place opening bracket
      } else {
        --cur;      // Decrease nesting level
        putchar(')'); // Place closing bracket
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/