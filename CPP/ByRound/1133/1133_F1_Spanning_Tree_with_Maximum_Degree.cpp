// Problem: CF 1133 F1 - Spanning Tree with Maximum Degree
// https://codeforces.com/contest/1133/problem/F1

/*
Purpose: 
This code finds a spanning tree of an undirected unweighted connected graph such that 
the maximum degree of any vertex in the spanning tree is maximized. 
It uses a greedy approach: first, connect all neighbors of the vertex with the highest degree,
then use a standard Union-Find structure to complete the spanning tree with remaining edges.

Algorithms/Techniques:
- Greedy algorithm to select edges connected to the vertex with maximum degree
- Union-Find (Disjoint Set Union) data structure to manage connected components
- Spanning tree construction via Kruskal's algorithm logic (but optimized for max degree)

Time Complexity: O(m * α(n)) where α(n) is the inverse Ackermann function (nearly constant)
Space Complexity: O(n + m) for adjacency list and edge storage

*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 200100
#define inf 1e6
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<ll, ll>
using namespace std;
vector<int> adj[N];
vector<pp> edge;
class DisjointSetUnion {
  int n;
  int *p, *r;

public:
  DisjointSetUnion(int n) {
    this->n = n;
    p = new int[n + 1];
    r = new int[n + 1];
    for (int i = 0; i <= n; i++)
      r[i] = 1, p[i] = i;
  }
  void Union(int a, int b) {
    int x = Find(a);
    int y = Find(b);
    if (r[x] > r[y]) {
      p[y] = x;
      r[x] += r[y];
    } else {
      p[x] = y;
      r[y] += r[x];
    }
  }
  int Find(int x) {
    if (p[x] == x)
      return x;
    return p[x] = Find(p[x]); // Path compression
  }
};
int main() {
  int i, j, k;
  int n, m;
  int u, v;
  int x, y;
  sff(n, m);
  for (i = 0; i < m; i++) {
    sff(u, v);
    adj[u].pb(v);
    adj[v].pb(u);
    edge.pb({u, v});
  }
  x = 0, k = -1;
  // Find the vertex with maximum degree
  for (i = 1; i <= n; i++) {
    if (adj[i].size() > x)
      x = adj[i].size(), k = i;
  }
  DisjointSetUnion dsu(n);
  // Connect all neighbors of the vertex with maximum degree to the spanning tree
  for (i = 0; i < x; i++) {
    v = adj[k][i];
    if (dsu.Find(k) != dsu.Find(v)) {
      pff(k, v);
      nl;
      dsu.Union(k, v);
    }
  }
  // Complete the spanning tree with remaining edges
  for (i = 0; i < m; i++) {
    u = edge[i].first;
    v = edge[i].second;
    if (dsu.Find(u) != dsu.Find(v)) {
      pff(u, v);
      nl;
      dsu.Union(u, v);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/