/*
 * Problem URL : https://codeforces.com/problemset/problem/2056/F2
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int res = 0, ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    ;
  for (; isdigit(ch); ch = getchar())
    res = (res << 3) + (res << 1) + (ch & 15);
  return res;
}

const int N = (1 << 18) + 5;

int dp[N];

char s[N];

inline int C(int n, int m) { return (n & m) == m; }

inline int S(int n, int m) {
  int d = m + 1 >> 1;
  return (n - m + d - 1 & d - 1) == d - 1;
}

int main() {
  int T = read();
  while (T--) {
    int k = read(), m = read(), n = 0, l = 0;
    scanf("%s", s + 1);
    for (int i = 1; i <= k; ++i)
      n += s[i] == '1';
    while (1 << l < n)
      ++l;
    fill(dp, dp + (1 << l), 0);
    for (int i = 0; i < n; ++i)
      dp[i] = S(n, i + 1);
    for (int i = 0; i < l; ++i) {
      for (int s = 0; s < 1 << l; ++s) {
        if (s & 1 << i)
          dp[s] ^= dp[s ^ 1 << i];
      }
    }
    int ans = 0;
    for (int s = 0; s < 1 << l && s < m; ++s) {
      if (!dp[s])
        continue;
      int t = m - 1 - s >> l;
      if (t % 2 == 0)
        ans ^= s;
      if (t % 4 == 0)
        ans ^= t << l;
      else if (t % 4 == 1)
        ans ^= 1 << l;
      else if (t % 4 == 2)
        ans ^= t + 1 << l;
    }
    printf("%d\n", ans);
  }
  return 0;
}