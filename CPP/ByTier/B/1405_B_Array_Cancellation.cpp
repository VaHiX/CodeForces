// Problem: CF 1405 B - Array Cancellation
// https://codeforces.com/contest/1405/problem/B

#include <cstdio>
typedef long long ll;

/*
 * Problem: Array Cancellation
 * 
 * Given an array of integers with sum zero, we want to make all elements zero
 * using operations where we can transfer value from index i to j. If i < j,
 * the operation is free; otherwise it costs 1 coin.
 * 
 * Algorithm:
 * - Traverse the array and maintain a running sum (avail).
 * - When encountering a positive number, add it to avail (we have excess).
 * - When encountering a negative number, check if we can cover it using current avail.
 *   - If yes, subtract it from avail (free transfer).
 *   - If no, calculate how much is needed and increment cnt with the deficit (cost).
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll avail(0), cnt(0); // avail tracks cumulative excess, cnt tracks cost
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x > 0) {
        avail += x; // accumulate positive values
      } else if (x < 0) {
        if (x + avail > 0) {
          avail += x; // we can cover the negative with available excess (free)
        } else {
          x += avail; // deficit after using all available
          cnt -= x;   // x is negative, so -x gives us the cost
          avail = 0;  // reset available excess
        }
      }
    }
    printf("%lld\n", cnt);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/