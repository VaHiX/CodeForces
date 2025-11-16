// Problem: CF 1927 G - Paint Charges
// https://codeforces.com/contest/1927/problem/G

/*
Algorithm: Dynamic Programming with Segment Tree-like Approach
Time Complexity: O(n^3) where n <= 100, so effectively O(1) for constraints
Space Complexity: O(n^2) for dp and tag arrays

This problem uses dynamic programming to find the minimum number of paint charges
needed to cover all cells. For each segment [l, r], we compute the minimum charges
required to paint all cells in that segment. The key idea is to precompute overlaps
between different charge ranges and use segment tree techniques to efficiently
compute coverage information.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>

using namespace std;
#define mp make_pair
#define pb push_back
#define PII pair<int, int>
#define ll long long
template <typename... Args> void rd(Args &...args);
#define multicase 1
#define N 500005
#define mod 998244353
int a[N], b[N];
void init() {}
int dp[123][123], tag[123][123];

void solve() {
  int n;
  rd(n);
  for (int i = 1; i <= n; ++i)
    rd(a[i]);
  memset(dp, 0x3f, sizeof dp);
  memset(tag, 0, sizeof tag);
  
  // Precompute overlapping ranges for all pairs of cells
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      int R = min(n, i + a[i] - 1), L = max(1, j - a[j] + 1);
      if (L < i && R > j)
        tag[L][R]++, tag[i][R]--, tag[L][j]--, tag[i][j]++;
    }
  
  // Compute prefix sums for tag matrix
  for (int l = 1; l <= n; ++l)
    for (int r = n; r; --r)
      tag[l][r] += tag[l - 1][r] + tag[l][r + 1] - tag[l - 1][r + 1];
  
  // Mark segments that are completely covered by some charge
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      if (tag[i][j])
        dp[i][j] = 2;
  
  // Initialize segments where single charge can cover entire segment
  for (int i = 1; i <= n; ++i) {
    for (int j = max(i - a[i] + 1, 1); j <= i; ++j)
      dp[j][i] = 1;  // Paint from left
    for (int j = i; j <= min(i + a[i] - 1, n); ++j)
      dp[i][j] = 1;  // Paint from right
  }
  
  // Dynamic programming: split segments into two parts
  for (int len = 1; len <= n; ++len)
    for (int l = 1, r = len; r <= n; ++l, ++r)
      for (int m = l; m < r; ++m)
        dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r]);
  
  cout << dp[1][n] << endl;
}

int main() {
  init();
#if multicase
  int _;
  cin >> _;
  while (_--)
    solve();
#else
  solve();
#endif
}

void read(int &x) {
  x = 0;
  char ch = getchar();
  int f = 1;
  while (!isdigit(ch))
    f = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - 48, ch = getchar();
  x = f * x;
}

void read(ll &x) {
  x = 0;
  char ch = getchar();
  int f = 1;
  while (!isdigit(ch))
    f = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - 48, ch = getchar();
  x = f * x;
}

template <typename... Args> void rd(Args &...args) {
  std::initializer_list<int>{(read(args), 0)...};
}


// https://github.com/VaHiX/CodeForces/