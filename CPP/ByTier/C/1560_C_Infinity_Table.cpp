// Problem: CF 1560 C - Infinity Table
// https://codeforces.com/contest/1560/problem/C

#include <cstdio>
typedef long long ll;

/*
C. Infinity Table
Algorithm: The table is filled in a spiral pattern starting from top-left.
           We determine the layer (ring) in which number k resides,
           then compute its exact row and column within that layer.
Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll k;
    scanf("%lld", &k);
    ll idx(0);
    // Find the smallest idx such that idx*idx >= k
    // This gives us the layer (ring) where k is located
    while (idx * idx < k) {
      ++idx;
    }
    ll row(idx), col(idx);
    // Calculate how far k is from the start of the current layer
    ll rem = k - (idx - 1) * (idx - 1);
    if (rem <= idx) {
      // k is in the top row of this layer
      row = rem;
    } else {
      // k is in the right column of this layer
      col = 2 * idx - rem;
    }
    printf("%lld %lld\n", row, col);
  }
}


// https://github.com/VaHiX/codeForces/