/*
 * Problem URL : https://codeforces.com/contest/2137/problem/G
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int head[N], num, n, m, k, in[N], deg[N];
struct edge {
  int to, next;
} g[N * 2];
void addd(int u, int v) {
  num++;
  g[num].to = v;
  g[num].next = head[u];
  head[u] = num;
}
bool col[N], ans[N], vis[N], f[N][2];
struct node {
  int opt, x;
} a[N];
queue<int> q;
void work(int x) {
  col[x] = 1;
  if (f[x][0])
    q.push(x);
  if (f[x][1])
    q.push(x + n);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u > n) {
      u -= n;
      for (int i = head[u]; i; i = g[i].next) {
        int v = g[i].to;
        if (f[v][0] == 0) {
          f[v][0] = 1;
          if (col[v])
            q.push(v);
        }
      }
    } else {
      for (int i = head[u]; i; i = g[i].next) {
        int v = g[i].to;
        in[v]--;
        if (in[v] == 0) {
          f[v][1] = 1;
          if (col[v])
            q.push(v + n);
        }
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    //	int n,m;
    int q;
    cin >> n >> m >> q;
    int u, v;
    num = 0;
    for (int i = 1; i <= n; i++)
      head[i] = f[i][0] = f[i][1] = in[i] = deg[i] = col[i] = 0;
    for (int i = 1; i <= m; i++) {
      cin >> u >> v;
      addd(v, u);
      in[u]++;
      deg[u]++;
    }
    for (int i = 1; i <= n; i++)
      if (!in[i])
        f[i][0] = f[i][1] = 1;
    for (int i = 1; i <= q; i++) {
      cin >> a[i].opt >> a[i].x;
      if (a[i].opt == 1)
        col[a[i].x] = 1;
    }
    for (int i = 1; i <= n; i++) {
      if (!col[i])
        q++, a[q].opt = 1, a[q].x = i;
      col[i] = 0;
    }
    for (int i = q; i >= 1; i--) {
      if (a[i].opt == 1) {
        work(a[i].x);
      } else {
        ans[i] = (col[a[i].x] & f[a[i].x][0]);
      }
    }
    for (int i = 1; i <= q; i++)
      if (a[i].opt == 2)
        cout << (ans[i] ? "YES\n" : "NO\n");
  }
}
