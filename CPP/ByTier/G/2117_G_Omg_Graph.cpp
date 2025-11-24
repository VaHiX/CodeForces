// Problem: CF 2117 G - Omg Graph
// https://codeforces.com/contest/2117/problem/G

/*
G. Omg Graph
Algorithms/Techniques: Union-Find (Disjoint Set Union), Sorting, Minimum Spanning Tree (MST) with modified logic
Time Complexity: O(m log m + n + m α(n)) where α is the inverse Ackermann function.
Space Complexity: O(n + m)

This solution finds the minimum cost path from vertex 1 to vertex n in a weighted undirected graph,
where the cost of a path is defined as the sum of the minimum and maximum weights of edges on that path.
The approach uses a modified Union-Find structure to build a spanning tree while tracking the minimum edge weight
in each connected component. When components are merged, we track the smallest edge weight in the union,
which helps us compute the optimal cost efficiently by considering the largest edge in the current MST
and the smallest edge in the combined component.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 55, INF = 1e9 + 1, MOD = 1e9 + 7;
int T, n, m;
int f[N], mn[N]; // f: parent array for Union-Find; mn: min edge weight in component
int fd(int x) { return f[x] == x ? x : f[x] = fd(f[x]); } // find with path compression
struct edge {
  int u, v, w;
  bool operator<(const edge &x) const { return w < x.w; } // sorting by weight
} a[N];
signed main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    }
    sort(a + 1, a + 1 + m); // sort edges by weight
    for (int i = 1; i <= n; i++) {
      f[i] = i;
      mn[i] = INF; // initialize min weights
    }
    int ans = 2 * INF;
    for (int i = 1; i <= m; i++) {
      int u = a[i].u, v = a[i].v, w = a[i].w;
      int uu = fd(u); // find root of u's component
      int vv = fd(v); // find root of v's component
      if (uu != vv) { 
        f[vv] = uu; // union the components
        mn[uu] = min(mn[uu], mn[vv]); // update min weight of new union
        mn[uu] = min(mn[uu], w); // also include current edge weight
      }
      if (fd(1) == fd(n)) { // check if 1 and n are in same component
        ans = min(ans, a[i].w + mn[fd(1)]); // cost = max edge + min edge in union
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/