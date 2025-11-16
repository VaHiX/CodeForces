// Problem: CF 1810 E - Monsters
// https://codeforces.com/contest/1810/problem/E

/*
Algorithm: Union-Find (Disjoint Set Union) with sorting by monster danger
Purpose: Determine if all monsters in a graph can be defeated, starting from a
vertex with danger 0, moving through edges only when the monster's danger
requirement is met.

Approach:
1. For each vertex, store its monster danger value.
2. Use Union-Find (DSU) to merge connected components, considering the danger
values.
3. Sort edges by the maximum danger of the two vertices they connect.
4. Process edges in increasing order of max danger, merging components and
updating validity.
5. Check if any component reachable from a start vertex (with danger 0) can
contain all vertices.

Time Complexity: O(m log m + n α(n)) where α is the inverse Ackermann function.
Space Complexity: O(n + m)

The solution works because:
- Edges are processed in order of increasing danger, so we can safely merge
components.
- For each component, we track whether it's valid (contains a start vertex with
danger 0 and sufficient monsters defeated).
- At the end, we check if the component containing vertex 1 is valid and
includes all vertices.
*/

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <utility>

using namespace std;
const int maxn = 2e5 + 5;
pair<int, int> edges[maxn];
int a[maxn];
int root[maxn];
bool is_valid[maxn];
int get_root(int u) {
  while (root[u] > 0)
    u = root[u];
  return u;
}
void join(int u, int v) {
  int cost = max(a[u], a[v]);
  u = get_root(u);
  v = get_root(v);
  if (u == v)
    return;
  if (-root[v] > -root[u]) {
    swap(u, v);
  }
  int new_valid =
      (is_valid[u] && -root[u] >= cost) || (is_valid[v] && -root[v] >= cost);
  root[u] += root[v];
  root[v] = u;
  is_valid[u] = new_valid;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (a[i] == 0) {
        is_valid[i] = 1;
      } else
        is_valid[i] = 0;
      root[i] = -1;
    }
    for (int i = 1; i <= m; ++i) {
      cin >> edges[i].first >> edges[i].second;
    }
    sort(edges + 1, edges + m + 1, [&](auto &e1, auto &e2) {
      int costE1 = max(a[e1.first], a[e1.second]);
      int costE2 = max(a[e2.first], a[e2.second]);
      return costE1 < costE2;
    });
    for (int i = 1; i <= m; ++i) {
      const auto [u, v] = edges[i];
      join(u, v);
    };
    if (is_valid[get_root(1)] && -root[get_root(1)] == n) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/