/*
 * Problem URL : https://codeforces.com/contest/1067/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

int f[100005][201];
int g[100005][201];

void add(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}

int main() {
  int n;
  ignore = scanf("%d", &n);

  f[0][1] = 1;

  for (int i = 1; i <= n; i++) {
    int a;
    ignore = scanf("%d", &a);

    int s1 = 0;
    for (int t = 200; t >= 1; t--) {
      add(s1, f[i - 1][t]);

      if (a == -1 || a == t) {
        f[i][t] = s1;
        add(f[i][t], g[i - 1][t]);
      }
    }

    int s2 = 0;

    for (int t = 1; t <= 200; t++) {
      if (a == -1 || a == t)
        g[i][t] = s2;

      add(s2, f[i - 1][t]);
      add(s2, g[i - 1][t]);
    }
  }

  int ans = 0;
  for (int t = 1; t <= 200; t++) {
    add(ans, f[n][t]);
  }

  printf("%d\n", ans);
}
