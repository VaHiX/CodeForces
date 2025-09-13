/*
 * Problem URL : https://codeforces.com/contest/1666/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000009
#define zxc(x) cerr << (#x) << '=' << (x) << '\n'
vector<int> E[MAX];
int n, m, s;

int vis[MAX], NOW;
int fa[MAX];
int ans[2][MAX];
void DFS(int u, int f) {
  if (u == s)
    return;
  if (vis[u]) {
    if (vis[u] != NOW) {
      for (int i = u; i; i = fa[i]) {
        ans[0][++ans[0][0]] = i;
      }
      fa[u] = f;
      for (int i = u; i; i = fa[i]) {
        ans[1][++ans[1][0]] = i;
      }
      puts("Possible");
      cout << ans[0][0] << '\n';
      while (ans[0][0])
        cout << ans[0][ans[0][0]--] << ' ';
      cout << '\n';
      cout << ans[1][0] << '\n';
      while (ans[1][0])
        cout << ans[1][ans[1][0]--] << ' ';
      cout << '\n';
      exit(0);
    }

    return;
  }
  vis[u] = NOW;
  fa[u] = f;
  for (int v : E[u]) {
    DFS(v, u);
  }
}

signed main() {
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 1; i <= m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
  }
  for (int v : E[s]) {
    NOW++;
    DFS(v, s);
  }
  puts("Impossible");
}