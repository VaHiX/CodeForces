// Problem: CF 1844 E - Great Grids
// https://codeforces.com/contest/1844/problem/E

/*
Code Purpose:
This program determines whether a great grid can be constructed that satisfies the given constraints.
A great grid:
1. Contains only 'A', 'B', or 'C'.
2. Every 2x2 contiguous subgrid contains all three different letters.
3. Adjacent cells (sharing an edge) contain different letters.
Constraints specify that certain diagonally adjacent cells must have the same letter.
The solution uses graph coloring techniques and DFS to check consistency of constraints.

Algorithms/Techniques:
- Graph representation using adjacency lists.
- Bipartite graph checking using DFS with bit manipulation to track colors.
- Constraint propagation via graph edges representing equality/inequality.

Time Complexity: O(n * m + k)
Space Complexity: O(n * m + k)
*/

#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <utility>
#include <vector>

using namespace std;
#define mp make_pair
#define fr first
#define sc second
long long n, m, d;
vector<pair<long long, long long>> vl[2069], al[2069];
bitset<2069> vtd, dh;
bool r0;
void dfs(long long x) {
  long long i, sz = al[x].size(), l, w;
  vtd[x] = 1;
  for (i = 0; i < sz; i++) {
    l = al[x][i].fr;
    w = al[x][i].sc;
    if (!vtd[l]) {
      dh[l] = dh[x] ^ w;
      dfs(l);
    } else if (dh[l] != (dh[x] ^ w)) {
      r0 = 1;
    }
    if (r0) {
      return;
    }
  }
}
int main() {
  long long t, rr, i, j, k, k2, sz, y, x, y2, x2, yy, xx, e, e2;
  scanf("%lld", &t);
  for (rr = 0; rr < t; rr++) {
    scanf("%lld%lld%lld", &n, &m, &d);
    for (i = 1; i <= n - 1; i++) {
      vl[i].clear();
    }
    for (i = 0; i < d; i++) {
      scanf("%lld%lld%lld%lld", &y, &x, &y2, &x2);
      yy = min(y, y2);
      xx = min(x, x2);
      e = x2 < x;
      vl[yy].push_back({xx, e});
    }
    for (i = 1; i <= m - 1; i++) {
      al[i].clear();
      vtd[i] = 0;
    }
    for (i = 1; i <= n - 1; i++) {
      if (!vl[i].empty()) {
        k = vl[i][0].fr;
        e = vl[i][0].sc;
        sz = vl[i].size();
        for (j = 1; j < sz; j++) {
          k2 = vl[i][j].fr;
          e2 = vl[i][j].sc;
          al[k].push_back({k2, e ^ e2});
          al[k2].push_back({k, e ^ e2});
        }
      }
    }
    r0 = 0;
    for (i = 1; i <= m - 1 && !r0; i++) {
      if (!vtd[i]) {
        dh[i] = 0;
        dfs(i);
      }
    }
    if (!r0) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}


// https://github.com/VaHiX/CodeForces/