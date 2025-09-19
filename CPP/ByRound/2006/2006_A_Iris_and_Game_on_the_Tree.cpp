/*
 * Problem URL : https://codeforces.com/problemset/problem/2006/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int T, n, C[N];
char s[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      C[i] = 0;
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      C[u]++, C[v]++;
    }
    scanf("%s", s + 1);
    int cnt = 0;
    for (int i = 2; i <= n; i++)
      if (s[i] == '?')
        cnt++;
    int c0 = 0, c1 = 0, c2 = 0;
    for (int i = 2; i <= n; i++) {
      if (C[i] != 1)
        continue;
      if (s[i] == '0')
        c0++;
      else if (s[i] == '1')
        c1++;
      else
        c2++;
    }
    if (s[1] == '0')
      printf("%d\n", (c2 + 1) / 2 + c1);
    else if (s[1] == '1')
      printf("%d\n", (c2 + 1) / 2 + c0);
    else if (c0 != c1)
      printf("%d\n", c2 / 2 + max(c0, c1));
    else
      printf("%d\n", (c2 + ((cnt - c2) & 1)) / 2 + c0);
  }
  return 0;
}