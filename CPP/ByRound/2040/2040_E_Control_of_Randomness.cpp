/*
 * Problem URL : https://codeforces.com/contest/2040/problem/E
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;

int n, q;
vector<int> e[N];
int fa[N], dep[N];

void dfs(int u, int fff) {
  fa[u] = fff;
  dep[u] = dep[fff] + 1;
  for (int v : e[u])
    if (v != fff)
      dfs(v, u);
}
int main() {

  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1, u, v; i < n; ++i)
      scanf("%d%d", &u, &v), e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0);
    while (q--) {
      int v, p;
      scanf("%d%d", &v, &p);
      if (v == 1)
        puts("0");
      else if (fa[v] == 1)
        puts("1");
      else {
        int de = dep[v] - 1;
        int res = 0;
        if (de & 1)
          de--, ++res;
        p = min(p, de >> 1);
        int cnt = de >> 1;
        static int a[N];
        for (int i = 1, pos = v; i <= cnt; ++i)
          a[i] = fa[pos], pos = fa[fa[pos]];
        sort(a + 1, a + cnt + 1,
             [&](int aa, int bb) { return e[aa].size() < e[bb].size(); });
        res += p * 2;
        for (int i = 1; i <= cnt - p; ++i)
          res += 2 * e[a[i]].size();
        printf("%d\n", res);
      }
    }
  }

  return 0;
}