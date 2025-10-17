// Problem: CF 1879 B - Chips on the Board
// https://codeforces.com/contest/1879/problem/B

/*
B. Chips on the Board

Purpose:
This solution computes the minimum cost to place chips on an n×n board such that every cell has at least one chip in its row or column.
Each chip placed at position (i, j) costs a[i] + b[j].

Algorithm:
- For each test case, we compute two candidates for the minimum cost:
  1. Place all chips in the same row (using the minimum a[i] value), and
     distribute chips across columns using minimum b[j] values.
  2. Place all chips in the same column (using the minimum b[j] value), and
     distribute chips across rows using minimum a[i] values.
- The answer is the minimum of these two candidates.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll sa(0), sb(0), ma(1e9 + 7), mb(1e9 + 7); // sa, sb accumulate total cost; ma, mb track min a[i], b[j]
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ma = (ma < x ? ma : x); // keep minimum a[i]
      sa += x; // accumulate sum of a
    }
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      mb = (mb < x ? mb : x); // keep minimum b[j]
      sb += x; // accumulate sum of b
    }
    ll candA(sa + n * mb), candB(sb + n * ma); // candidate 1: all in rows, candidate 2: all in columns
    printf("%lld\n", candA < candB ? candA : candB);
  }
}


// https://github.com/VaHiX/codeForces/