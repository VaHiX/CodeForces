// Problem: CF 1045 A - Last chance
// https://codeforces.com/contest/1045/problem/A

/*
Algorithm: Maximum Flow with Dinic's Algorithm
Time Complexity: O(V^2 * E) where V is the number of nodes and E is the number of edges
Space Complexity: O(V + E) for the flow network representation

This problem models a maximum flow scenario:
- Nodes represent weapons and spaceships
- Edges represent possible destruction assignments
- SQL rockets (type 0): 1 unit capacity, connected to specific ships
- Cognition beams (type 1): 1 unit capacity, connected to interval of ships using segment tree
- OMG bazookas (type 2): 2 unit capacity, connected to 3 ships
- We construct a flow network and find maximum flow from source to sink
- Then we reconstruct the assignment of weapons to ships using the flow information
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

#define x first
#define y second
#define m_p make_pair
using namespace std;
struct edge {
  short to, cap, rev;
  edge(int _a = 0, int _b = 0, int _c = 0) {
    to = _a;
    cap = _b;
    rev = _c;
  }
};
int S, T;
int dist[30010];
int cur[30010];
vector<edge> adj[30010];
int q[30010];
int hd, tl;
inline void addedge(int u, int v, int cap) {
  adj[u].push_back(edge(v, cap, adj[v].size()));
  adj[v].push_back(edge(u, 0, adj[u].size() - 1));
}
int dfs(int i, short fl) {
  if (i == T)
    return fl;
  short lf = fl;
  for (int &j = cur[i]; ~j; --j) {
    edge &e = adj[i][j];
    if (e.cap && dist[e.to] == dist[i] + 1) {
      short d = dfs(e.to, min(lf, e.cap));
      e.cap -= d;
      adj[e.to][e.rev].cap += d;
      lf -= d;
      if (!lf)
        return fl;
    }
  }
  dist[i] = -1;
  return fl - lf;
}
int Dinic() {
  int res = 0;
  while (true) {
    memset(dist, 0, sizeof(dist));
    dist[q[hd = tl = 0] = S] = 1;
    while (hd <= tl) {
      int i = q[hd++];
      cur[i] = adj[i].size() - 1;
      for (int j = cur[i]; ~j; --j) {
        edge &e = adj[i][j];
        if (e.cap && !dist[e.to]) {
          dist[e.to] = dist[i] + 1;
          q[++tl] = e.to;
        }
      }
    }
    if (!dist[T])
      break;
    int fl;
    while (fl = dfs(S, 10000))
      res += fl;
  }
  return res;
}
int bel[5010];
int tpe[5010];
int main(void) {
  int n, m;
  scanf("%d%d", &n, &m);
  S = 0;
  T = 30000;
  vector<pair<pair<int, int>, int>> v;
  for (int i = 1; i <= 8191; ++i) {
    addedge(n + i, n + (i << 1), 10000);
    addedge(n + i, n + (i << 1 | 1), 10000);
  }
  for (int i = 1; i <= n; ++i) {
    int a, b, c;
    scanf("%d%d", &tpe[i], &a);
    switch (tpe[i]) {
    case 0: {
      while (a--) {
        scanf("%d", &b);
        addedge(i, b + 8191 + n, 1);  // Connect weapon to specific ship
      }
      break;
    }
    case 1: {
      scanf("%d", &b);
      v.push_back(m_p(m_p(a, b), i));  // Store beam info for later processing
      int l = a + 8191, r = b + 8191;   // Segment tree indices
      while (l <= r) {
        if (l & 1)
          addedge(i, n + l, 1), l++;   // If l is left child, connect to node
        if (!(r & 1))
          addedge(i, n + r, 1), r--;   // If r is right child, connect to node
        l >>= 1;
        r >>= 1;
      }
      break;
    }
    case 2: {
      scanf("%d%d", &b, &c);
      addedge(i, a + 8191 + n, 1);   // Connect weapon to 3 ships
      addedge(i, b + 8191 + n, 1);
      addedge(i, c + 8191 + n, 1);
      break;
    }
    }
  }
  sort(v.begin(), v.end());  // Sort beams by left boundary for later processing
  for (int i = 1; i <= n; ++i) {
    if (tpe[i] != 2) {
      addedge(S, i, 1);   // Connect source to non-bazooka weapons (capacity 1)
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (tpe[i] == 2) {
      addedge(S, i, 2);   // Connect source to bazookas (capacity 2)
    }
  }
  for (int i = 1; i <= m; ++i) {
    addedge(n + 8191 + i, T, 1);  // Connect ships to sink (capacity 1)
  }
  printf("%d\n", Dinic());  // Find maximum flow
  for (int i = 1; i <= m; ++i) {
    for (int j = adj[i + 8191 + n].size() - 1; ~j; --j) {
      edge &e = adj[i + 8191 + n][j];
      if (e.cap && e.to != T) {
        bel[i] = e.to;  // Record which weapon destroyed ship i
      }
    }
  }
  multiset<pair<pair<int, int>, int>> s;  // Store beams in a multiset
  int pnt = 0, vs = v.size();
  for (int i = 1; i <= m; ++i) {
    if (bel[i] <= n && tpe[bel[i]] != 1)  // Skip if this ship was destroyed by a bazooka or weapon that's not a beam
      continue;
    while (pnt < vs && v[pnt].x.x <= i) {
      s.insert(m_p(m_p(v[pnt].x.y, v[pnt].x.x), v[pnt].y));  // Insert beam into multiset
      ++pnt;
    }
    while (!s.empty() && s.begin()->x.x < i)  // Remove beams that end before current ship
      s.erase(s.begin());
    if (!s.empty())
      bel[i] = s.begin()->y, s.erase(s.begin());  // Assign weapon based on beam with minimum right boundary
  }
  for (int i = 1; i <= m; ++i) {
    if (bel[i])
      printf("%d %d\n", bel[i], i);  // Output assignments
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/