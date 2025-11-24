// Problem: CF 1903 D2 - Maximum And Queries (hard version)
// https://codeforces.com/contest/1903/problem/D2

#pragma GCC optimize(2)
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;
#define int long long
char *p1, *p2, buf[100000];
#define nc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
int read() {
  int x = 0, f = 1;
  char ch = nc();
  while (ch < 48 || ch > 57) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }
  while (ch >= 48 && ch <= 57)
    x = x * 10 + ch - 48, ch = nc();
  return x * f;
}
signed main() {
  ios::sync_with_stdio(false), cout.tie(nullptr);
  int n, q;
  n = read(), q = read();
  vector<int> a(n);
  int s = 0, mx = 0;
  for (auto &x : a)
    x = read();
  for (auto _ : a)
    s += _, mx = max(mx, _);
  vector<int> dp(1 << 20); // dp[mask] stores the cost to make all numbers have prefix mask
  for (int x = 0; x < n; x++) {
    int lst = 0, bt = 0;
    for (int i = 19; i >= 0; i--)
      if (a[x] >> i & 1) { // For each bit set in a[x]
        int bm = 1 << i;   // Bit mask for current bit
        bt |= bm;          // Update the prefix mask
        int _ = bm - (a[x] & (bm - 1)); // Cost needed to make the i-th bit set
        dp[bt] += _;       // Add this cost to dp[bt]
        if (lst)
          dp[lst] -= _;    // Subtract this cost from the previous prefix
        lst = bt;          // Update the last prefix used
      }
  }
  // Accumulate costs from children to parent masks in the mask tree
  for (int i = 0; i < 20; i++)
    for (int S = 0; S < (1 << 20); S++)
      if (S >> i & 1)
        dp[S - (1 << i)] += dp[S];
  dp[0] = 0; // Base case: no prefix, no cost
  for (int S = 1; S < (1 << 20); S++)
    dp[S] += dp[S - 1]; // Prefix sum of costs
  for (int S = 0; S < (1 << 20); S++)
    dp[S] = n * S - dp[S]; // Adjust dp to represent total cost for a prefix
  for (int S = (1 << 20) - 2; S >= 0; S--)
    dp[S] = min(dp[S], dp[S + 1]); // Monotonic min update for binary search
  while (q--) {
    int k;
    k = read();
    if ((s + k) / n >= mx)
      cout << (s + k) / n << endl; // If k is large enough, all elements can be equal
    else
      cout << upper_bound(dp.begin(), dp.end(), k) - dp.begin() - 1 << endl; // Binary search on dp
  }
}


// https://github.com/VaHiX/CodeForces/