// Problem: CF 1717 F - Madoka and The First Session
// https://codeforces.com/contest/1717/problem/F

/*
Algorithm: Min Cost Max Flow
Time Complexity: O(V*E^2) where V = n+2, E = m+n*2
Space Complexity: O(V+E) where V = n+2, E = m+n*2

This solution models the problem as a min cost max flow problem:
- Each edge (u,v) in input can be used in one of two directions
- We want to assign each edge to either (u,v) or (v,u) such that:
  - For each node i where s[i] = 1, we have b[i] = a[i]
  - For each node i where s[i] = 0, we have b[i] = 0 (but we don't care about assignment)

We use the following approach:
1. Model as flow network with source S and sink T
2. Each edge (u,v) becomes two directed edges in the flow graph (u->v, v->u) with capacity 1 and cost 0
3. Connect source S to every node i with demand a[i] (if s[i]=1, then we have a requirement)
4. Connect every node i to sink T with capacity based on requirement
5. Use min cost max flow to compute a valid assignment that satisfies the constraints
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
namespace IO {
const int buflen = 1 << 21;
int x;
bool f;
char ch, buf[buflen], *p1 = buf, *p2 = buf;
inline char gc() {
  return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, buflen, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  x = 0, f = 1, ch = gc();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 0;
    ch = gc();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
  return f ? x : -x;
}
} // namespace IO
using IO::read;
const int N = 1e4 + 5, E = 6e4 + 5;
int n, m, S, T, tot = 1, a[N], s[N], we[E], dis[N], u[N], v[N];
bool inq[N];
struct Edge {
  int y, z, c;
} fr[N];
vector<Edge> G[N];
queue<int> Q;
inline void adde(int u, int v, int w, int c) {
  G[u].emplace_back(Edge{v, ++tot, c}), we[tot] = w;
  G[v].emplace_back(Edge{u, ++tot, -c}), we[tot] = 0;
}
bool spfa() {
  memset(dis, 0x3f, sizeof dis);
  Q.push(S);
  dis[S] = 0;
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    inq[x] = 0;
    for (auto e : G[x]) {
      int y = e.y, z = e.z, c = e.c;
      if (we[z] && dis[y] > dis[x] + c) {
        dis[y] = dis[x] + c;
        fr[y] = Edge{x, z, c};
        if (!inq[y])
          Q.push(y), inq[y] = 1;
      }
    }
  }
  return dis[T] != dis[0];
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++)
    s[i] = read();
  for (int i = 1; i <= n; i++)
    a[i] = read();
  for (int i = 1; i <= m; i++)
    u[i] = read(), v[i] = read(), a[u[i]]++, a[v[i]]--;
  for (int i = 1; i <= n; i++)
    if (s[i] && (a[i] & 1)) {
      puts("NO");
      return 0;
    }
  for (int i = 1; i <= m; i++)
    adde(u[i], v[i], 1, 0);
  S = n + 1, T = n + 2;
  for (int i = 1; i <= n; i++) {
    if (s[i]) {
      if (a[i] > 0)
        adde(S, i, a[i] / 2, -100);
      if (a[i] < 0)
        adde(i, T, -a[i] / 2, -100);
    } else
      adde(S, i, 1000000, 0), adde(i, T, 1000000, 0);
  }
  while (spfa()) {
    int mn = 1e9;
    for (int i = T; i != S; i = fr[i].y)
      mn = min(mn, we[fr[i].z]);
    if (dis[T] >= 0)
      break;
    for (int i = T; i != S; i = fr[i].y)
      we[fr[i].z] -= mn, we[fr[i].z ^ 1] += mn;
  }
  for (int i = 1; i <= m; i++)
    if (we[2 * i + 1])
      a[u[i]] -= 2, a[v[i]] += 2;
  for (int i = 1; i <= n; i++)
    if (s[i] && a[i]) {
      puts("NO");
      return 0;
    }
  puts("YES");
  for (int i = 1; i <= m; i++)
    if (we[2 * i + 1])
      cout << v[i] << ' ' << u[i] << '\n';
    else
      cout << u[i] << ' ' << v[i] << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/