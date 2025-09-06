/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/F
 * Submit Date : 2025-08-13
 */

// LUOGU_RID: 153010023
#include <bits/stdc++.h>
#define LL long long
#define fr(x)                                                                  \
  freopen(#x ".in", "r", stdin);                                               \
  freopen(#x ".out", "w", stdout);
using namespace std;
const int N = 5e5 + 5;
int n, a[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int m = __lg(n);
  for (int i = 0; i <= m; i++)
    for (int j = 0; j < n; j++)
      if (j >> i & 1)
        a[j] ^= a[j ^ (1 << i)];
  for (int i = 0; i <= m; i++)
    for (int j = 0; j < n; j++)
      if (j >> i & 1)
        a[j ^ (1 << i)] ^= a[j];
  for (int i = n - 1; ~i; i--)
    cout << a[i] << " ";
  return 0;
}