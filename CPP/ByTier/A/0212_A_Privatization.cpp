/*
 * Problem URL : https://codeforces.com/contest/212/problem/A
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FI first
#define SE second
using namespace std;
inline int read() {
  int x = 0;
  bool op = 0;
  char c = getchar();
  while (!isdigit(c))
    op |= (c == '-'), c = getchar();
  while (isdigit(c))
    x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return op ? -x : x;
}
const int N = 410;
const int M = 5010;
int n, m, k, t, tot;
int id[N], deg[N], col[M];
vector<pii> f[N * N];
void dfs(int u, int c1, int c2) {
  // printf("%d %d %d %d\n", u, c1, c2, f[u][c1].SE);
  if (f[u][c1].SE == 0)
    return f[u][c2] = mp(0, 0), void();
  int v = f[u][c1].SE, cur = f[u][c1].FI;
  dfs(v, c2, c1);
  f[u][c1] = mp(0, 0);
  f[v][c2] = mp(cur, u);
  f[u][c2] = mp(cur, v);
  col[cur] = c2;
  return;
}
int main() {
  n = read();
  m = read();
  k = read();
  t = read();
  for (int i = 1; i <= n + m; i++)
    id[i] = ++tot, f[i].resize(t + 1);
  for (int i = 1; i <= k; i++) {
    int u = read(), v = read() + n;
    // printf("%d %d\n", u, v);
    int c1 = 0, c2 = 0;
    for (int j = 1; j <= t; j++) {
      // printf("sE:%d %d %d %d %d\n", u, id[u], deg[u], j, f[u][j].SE);
      if (f[id[u]][j].SE == 0) {
        c1 = j;
        break;
      }
    }
    for (int j = 1; j <= t; j++) {
      // printf("se:%d %d %d\n", v, deg[v], f[v][j].SE);
      if (f[id[v]][j].SE == 0) {
        c2 = j;
        break;
      }
    }
    // printf("%d %d %d %d %d\n", i, deg[u], deg[v], c1, c2);
    dfs(id[v], c1, c2);
    // printf("ccc1:%d %d %d %d\n", u, v, c1, c2);
    // for(int s = 1; s <= t; s++)printf("se:%d %d\n", s, f[id[2]][s].SE);
    col[i] = c1;
    f[id[u]][c1] = mp(i, id[v]);
    f[id[v]][c1] = mp(i, id[u]);
    deg[u]++;
    deg[v]++;
    if (deg[u] % t == 0)
      id[u] = ++tot, f[tot].resize(t + 1);
    if (deg[v] % t == 0)
      id[v] = ++tot, f[tot].resize(t + 1);
    // for(int j = 1; j <= n + m; j++) {
    //     if(id[j] == 0)continue;
    //     for(int s = 1; s <= t; s++) {
    //         printf("(%d,%d) %d %d\n", (j / n), (j - 1) % n + 1, s,
    //         f[id[j]][s].FI);
    //     }
    // }
    // puts("");
  }
  int ans = 0;
  // vector<int> tmp; tmp.pb(1); tmp.resize(1); printf("tmp:%d\n", tmp[0]);
  // for(int i = 1; i <= n + m; i++) {
  //     for(int j = 1; j <= t; j++) {
  //         printf("(%d,%d):%d %d %d\n", (i / n), (i - 1) % n + 1, deg[i], j,
  //         f[id[i]][j].SE);
  //     }
  // }
  for (int i = 1; i <= n + m; i++)
    if (deg[i] % t)
      ans++;
  printf("%d\n", ans);
  for (int i = 1; i <= k; i++)
    printf("%d ", col[i]);
  return 0;
}