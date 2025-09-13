/*
 * Problem URL : https://codeforces.com/contest/2019/problem/E
 * Submit Date : 2025-09-11
 */


#include <bits/stdc++.h>
using namespace std;
#define fuck puts("fuck");
const int N = 1e6 + 10, inf = 0x3f3f3f3f;
int n;
int cnt, head[N], nxt[N], to[N];
int dep[N], mxd[N];
int cdep[N], cmxd[N];
int ans;

void add(int u, int v) {
  nxt[++cnt] = head[u];
  head[u] = cnt;
  to[cnt] = v;
}

void dfs(int u, int ff) {
  for (int i = head[u]; i; i = nxt[i]) {
    if (to[i] == ff)
      continue;
    mxd[to[i]] = dep[to[i]] = dep[u] + 1;
    dfs(to[i], u);
    mxd[u] = max(mxd[u], mxd[to[i]]);
  }
}
void solve() {
  scanf("%d", &n);
  cnt = 0;
  for (int i = 1; i <= n; ++i)
    head[i] = cdep[i] = cmxd[i] = 0;
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u);
  }
  mxd[1] = dep[1] = 1;
  dfs(1, 0);
  for (int i = 1; i <= n; ++i)
    cdep[dep[i]]++, cmxd[mxd[i]]++;
  for (int i = 1; i <= n; ++i)
    cdep[i] += cdep[i - 1], cmxd[i] += cmxd[i - 1];
  ans = inf;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, cmxd[i - 1] + cdep[n] - cdep[i]);
  printf("%d\n", ans);
}
signed main() {
  int T;
  cin >> T;
  while (T--)
    solve();
}