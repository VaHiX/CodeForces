// Problem: CF 1970 C2 - Game on Tree (Medium)
// https://codeforces.com/contest/1970/problem/C2

/*
Problem: Game on Tree (Medium)
Algorithms/Techniques: Tree DFS, Game Theory, Nim-like Sprague-Grundy Analysis
Time Complexity: O(n) per round, O(n) total for all rounds
Space Complexity: O(n)

This problem models a game on a tree where two players (Ron and Hermione) take turns moving a stone
from an active node to an adjacent inactive node. The player who cannot move loses.

The key insight is that this is a Nim-like game on a tree. We can use a depth-first search to
compute for each node whether it's a winning or losing position for the current player,
based on parity of depth and recursive evaluation of child nodes.

For each starting node, we run a DFS from that node and compute a boolean value z[u]:
- z[u] = true means the current player (Ron or Hermione) can win from node u
- z[u] = false means the current player will lose from node u

The root of the DFS is the starting node of the current round.
The DFS propagates information about winning/losing positions based on parity of depth:
- If the depth is even, we check if any child position is winning (to make z[u] true)
- If the depth is odd, we check if all child positions are losing (to make z[u] false)
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
int n, t, k, head[MAXN], dep[MAXN];
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
  bool pd = false;
  z[u] = (dep[u] % 2 == 1);
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].to;
    if (vis[v])
      continue;
    pd = true;
    dep[v] = dep[u] + 1;
    dfs(v);
    if (dep[u] % 2 == 0 && z[v])
      z[u] = true;
    if (dep[u] % 2 == 1 && !z[v])
      z[u] = false;
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
  for (int i = 1; i <= t; i++) {
    int s;
    read(s);
    dfs(s);
    if (z[s])
      cout << "Ron";
    else
      cout << "Hermione";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/