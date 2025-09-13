/*
 * Problem URL : https://codeforces.com/contest/1776/problem/M
 * Submit Date : 2025-09-08
 */

// LUOGU_RID: 103857228
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, head[N], d[N], tot, dep[N], fa[N], cnt[N];
bool vis[N];
struct o {
  int ne, to;
} e[N << 1];
inline void add(int x, int y) {
  e[++tot].ne = head[x];
  head[x] = tot;
  e[tot].to = y;
}
inline void dfs(int x, int f) {
  fa[x] = f, dep[x] = dep[f] ^ 1;
  for (int i = head[x]; i; i = e[i].ne) {
    int to = e[i].to;
    if (to == f)
      continue;
    dfs(to, x);
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  if (!(n & 1)) {
    cout << n;
    return 0;
  }
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    d[x]++, d[y]++;
    add(x, y), add(y, x);
  }
  dep[0] = 1;
  dfs(n, 0);
  for (int i = n; i; i--) {
    if (d[i] == 1 || dep[i] == 1) {
      cout << i;
      return 0;
    }
    int x = i;
    while (!vis[x])
      vis[x] = 1, x = fa[x], cnt[x]++;
    if ((x != n && cnt[x] >= 2 && !dep[x]) || (x == n && cnt[x] >= 3)) {
      cout << i;
      return 0;
    }
  }
  return 0;
}