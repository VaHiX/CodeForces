// Problem: CF 2035 A - Sliding
// https://codeforces.com/contest/2035/problem/A

/*
 * Problem: Calculate the sum of Manhattan distances after one person leaves
 *          and all subsequent people shift positions in row-major order.
 *
 * Algorithm/Techniques:
 *   - Sliding
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m, r, c;
    scanf("%lld %lld %lld %lld", &n, &m, &r, &c);
    
    // Compute the total Manhattan distance moved by all people
    // The formula accounts for:
    // - People in rows after 'r' that shift left (row-wise movement)
    // - People in column 'c' or right that shift up (column-wise movement)
    // - Combined effect of shifts in both directions
    ll res = (n - r) * m + (m - c) * 1 + (n - r) * (m - 1) * 1;
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/