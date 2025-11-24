// Problem: CF 1970 C3 - Game on Tree (Hard)
// https://codeforces.com/contest/1970/problem/C3

/*
Algorithm/Techniques: 
- Tree Dynamic Programming (DP) with game theory (Nim-like game).
- Use DFS to compute for each node:
  - cnt[u]: number of children with unmarked (inactive) subtrees.
  - z[u]: whether the subtree rooted at u has any unmarked node.
- Then, DFS2 computes f[u]:
  - f[u] = true if the current player (Ron) has a winning strategy from node u.
  - This is determined by analyzing the nim-like game state from node u.
- For each round, the winner is determined based on whether the starting node u is in a winning state.

Time Complexity: O(n + t)
Space Complexity: O(n)
*/

#include <stdio.h>
#include <iostream>

using namespace std;
const int MAXN = 2e5 + 10;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const int inf_int = 0x7f7f7f7f;
const long long inf_long = 0x7f7f7f7f7f7f7f7f;
const double eps = 1e-9;
char Buf[1 << 23], *P1 = Buf, *P2 = Buf;
#define getchar()                                                              \
  (P1 == P2 && (P2 = (P1 = Buf) + fread(Buf, 1, 1 << 23, stdin), P1 == P2)     \
       ? EOF                                                                   \
       : *P1++)
template <typename type> inline void read(type &x) {
  x = 0;
  bool f = false;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    f |= ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename type, typename... args>
inline void read(type &x, args &...y) {
  read(x), read(y...);
}
int n, t, k, head[MAXN], cnt[MAXN], f[MAXN];
bool vis[MAXN], z[MAXN];
struct node {
  int to, next;
} edge[MAXN << 1];
void build(int u, int v) {
  edge[++k].to = v;
  edge[k].next = head[u];
  head[u] = k;
}
void dfs(int u) {
  vis[u] = true;
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].to;
    if (vis[v])
      continue;
    dfs(v);
    if (!z[v]) {
      cnt[u]++;
      z[u] = true;
    }
  }
}
void dfs2(int u) {
  vis[u] = true;
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].to;
    if (vis[v])
      continue;
    if (!f[u] && (cnt[u] == 0 || (cnt[u] == 1 && !z[v])))
      f[v] = true;
    else
      f[v] = false;
    dfs2(v);
  }
}
signed main() {
  read(n, t);
  for (int i = 1; i < n; i++) {
    int u, v;
    read(u, v);
    build(u, v);
    build(v, u);
  }
  dfs(1);
  for (int i = 1; i <= n; i++)
    vis[i] = false;
  f[1] = false;
  dfs2(1);
  for (int i = 1; i <= t; i++) {
    int s;
    read(s);
    if (f[s] || cnt[s] > 0)
      cout << "Ron\n";
    else
      cout << "Hermione\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/