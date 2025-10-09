// Problem: CF 2041 F - Segmentation Folds
// https://codeforces.com/contest/2041/problem/F

/*
F. Segmentation Folds
Algorithms/Techniques: Sieve of Eratosthenes, Segment Folding with Prime Conditions, DFS with Memoization

Time Complexity: O(n log log n + n) where n = r - l, dominated by sieve and linear traversal.
Space Complexity: O(n + p) where p is the number of primes up to 2 * 10^6, due to arrays for primes, sieve, and segment tracking.

The problem involves folding a segment [l, r] such that we minimize its final length using operations:
- LTR: fold from left to right by choosing x s.t. l + x is prime and x is maximized
- RTL: fold from right to left by choosing x s.t. r + x is prime and x is minimized

We precompute primes, then simulate folding using DFS with tracking of valid segments.
The count of optimal paths is computed via recursive DFS on the segment boundaries.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
using i64 = long long;

namespace pr {
int p[2000010], pn; // Stores all primes up to 2e6
void init() {
  constexpr int n = 2000000;
  for (int i = 2; i <= n; i++) { // Sieve of Eratosthenes initialization
    if (!p[i])
      p[++pn] = i;
    for (int j = 1; j <= pn && i * p[j] <= n; j++) {
      p[i * p[j]] = 1; // Mark composite numbers
      if (i % p[j] == 0)
        break; // Stop if divisible to avoid redundancy
    }
  }
}
} // namespace pr

bool vis[200010]; // Visited flags for valid segment points
int pre[200010], nex[200010], mi, cnt;

void dfs(int l, int r) {
  if (mi > r - l) { // Update minimum interval length and reset count
    mi = r - l, cnt = 1;
  } else if (mi == r - l)
    cnt++; // Increase count for same minimum length

  int x = pre[(l + r) / 2]; // Find the latest valid point to the left of middle
  if (x != -1 && x > l)
    dfs(x, r); // Recurse on updated interval using LTR-like fold

  int y = nex[(l + r + 1) / 2]; // Find the earliest valid point to the right of middle
  if (y != -1 && y < r)
    dfs(l, y); // Recurse on updated interval using RTL-like fold
}

void solve() {
  i64 l, r;
  scanf("%lld%lld", &l, &r);
  l *= 2, r *= 2, mi = 1e9, cnt = 0; // Double l and r to map into [0..r-l] interval

  for (i64 i = l; i <= r; i++) // Mark all points as initially valid
    vis[i - l] = true;

  // Mark composites using sieve
  for (int i = 1; i <= pr::pn; i++) {
    int x = pr::p[i];
    for (i64 j = max((l + x - 1) / x, 2ll) * x; j <= r; j += x)
      vis[j - l] = false;
  }

  // Preprocessing left boundaries:
  pre[0] = -1;
  for (i64 i = l + 1; i <= r; i++) {
    if (vis[i - l])
      pre[i - l] = i - l;
    else
      pre[i - l] = pre[i - l - 1]; // Propagate last valid point
  }

  // Preprocessing right boundaries:
  nex[r - l] = -1;
  for (i64 i = r - 1; i >= l; i--) {
    if (vis[i - l])
      nex[i - l] = i - l;
    else
      nex[i - l] = nex[i - l + 1]; // Propagate next valid point
  }

  dfs(0, r - l); // Begin recursive folding from full interval
  printf("%d\n", cnt);
}

int main() {
  pr::init(); // Precompute all primes up to 2e6
  int T;
  for (scanf("%d", &T); T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/