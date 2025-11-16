// Problem: CF 730 K - Roads Orientation Problem
// https://codeforces.com/contest/730/problem/K

/*
Algorithm: 
The problem is to orient all edges of a graph such that:
1. There are no cycles (i.e., output should be a directed acyclic graph).
2. Source 's' has all its edges pointing out (no incoming edges).
3. Target 't' has all its edges pointing in (no outgoing edges).
4. All other vertices must have both incoming and outgoing edges.

Approach:
- First, we build an undirected graph and run DFS from source 's' to identify a spanning tree and back edges.
- Then we check if the target 't' is reachable from 's'. If not, return "No".
- We use BFS-like processing to orient all edges according to the rules.
- For each edge, we decide direction based on DFS tree and back edges.
- The final orientation is validated and outputted.

Time Complexity: O(n + m), where n is number of nodes and m is number of edges.
Space Complexity: O(n + m) for storing graph and auxiliary arrays.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

#define cl(x) memset(x, 0, sizeof(x))
using namespace std;
typedef pair<int, int> abcd;
inline char nc() {
  static char buf[100000], *p1 = buf, *p2 = buf;
  if (p1 == p2) {
    p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
    if (p1 == p2)
      return EOF;
  }
  return *p1++;
}
inline void read(int &x) {
  char c = nc(), b = 1;
  for (; !(c >= '0' && c <= '9'); c = nc())
    if (c == '-')
      b = -1;
  for (x = 0; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = nc())
    ;
  x *= b;
}
const int N = 400005, M = 1000005;
struct edge {
  int u, v, next;
} G[M << 1];
int head[N], inum = 1;
inline void add(int u, int v, int p) {
  G[p].u = u;
  G[p].v = v;
  G[p].next = head[u];
  head[u] = p;
}
int fat[N], depth[N], lnk[N];
#define V G[p].v
int fae[N], dir[M];
vector<int> back[N];
inline void dfs(int u, int fa, int fp) {
  fat[u] = fa;
  depth[u] = depth[fa] + 1;
  for (int p = head[u]; p; p = G[p].next)
    if (p != (fp ^ 1)) {
      if (!depth[V]) {
        lnk[u] = V;
        fae[V] = (p >> 1);
        dfs(V, u, p);
      } else if (depth[V] < depth[u])
        back[lnk[V]].push_back(p >> 1);
    }
}
int n, m, s, t;
abcd Q[10000005];
int l, r;
inline void Clear() {
  for (int i = 1; i <= n; i++)
    head[i] = 0;
  inum = 1;
  for (int i = 1; i <= n; i++)
    fat[i] = depth[i] = lnk[i] = fae[i] = 0, back[i].clear();
}
int main() {
  int T, iu, iv;
  read(T);
  while (T--) {
    read(n);
    read(m);
    read(s);
    read(t);
    for (int i = 1; i <= m; i++)
      read(iu), read(iv), add(iu, iv, ++inum), add(iv, iu, ++inum);
    for (int i = 1; i <= m; i++)
      dir[i] = -1;
    dfs(s, 0, 0);
    if (!depth[t]) {
      Clear();
      printf("No\n");
      continue;
    }
    l = r = -1;
    Q[++r] = abcd(t, 0);
    while (l < r) {
      int u = Q[++l].first, d = Q[l].second;
      while (fat[u] && dir[fae[u]] == -1) {
        dir[fae[u]] = d;
        for (int j = 0; j < (signed)back[u].size(); j++) {
          dir[back[u][j]] = d;
          int p = back[u][j] << 1;
          if (G[p].v == fat[u])
            Q[++r] = abcd(G[back[u][j] << 1].u, d ^ 1);
          if (G[p].u == fat[u])
            Q[++r] = abcd(G[back[u][j] << 1].v, d ^ 1);
        }
        u = fat[u];
      }
    }
    int flag = 0;
    for (int i = 1; i <= m; i++)
      if (dir[i] == -1)
        flag = 1;
    if (flag) {
      Clear();
      printf("No\n");
      continue;
    }
    printf("Yes\n");
    for (int i = 1; i <= m; i++)
      if ((depth[G[i << 1].u] < depth[G[i << 1].v]) == dir[i])
        printf("%d %d\n", G[i << 1].v, G[i << 1].u);
      else
        printf("%d %d\n", G[i << 1].u, G[i << 1].v);
    Clear();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/