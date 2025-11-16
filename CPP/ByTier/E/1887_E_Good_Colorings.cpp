// Problem: CF 1887 E - Good Colorings
// https://codeforces.com/contest/1887/problem/E

/*
Algorithm: 
This solution uses a combination of graph traversal (DFS) to detect cycles in a bipartite graph and then 
applies a binary search-like approach to reduce the cycle size to 4 nodes, representing a rectangle in the grid.
The problem involves finding a 2x2 rectangle with all four corners having different colors.
Time Complexity: O(n^2) in worst case due to graph construction and search, but likely much better in practice.
Space Complexity: O(n^2) for storing the graph and auxiliary arrays.

The key insight:
- The input forms a bipartite graph where one set represents rows and the other represents columns.
- We search for a cycle in this bipartite graph.
- Once we find a cycle, we try to reduce it to size 4 by querying intermediate nodes.
- Then we output the rectangle formed by the 4 nodes.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define F first
#define S second
using namespace std;
typedef pair<int, int> pr;
inline int rd() {
  int x = 0, y = 1;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    if (c == '-')
      y = -1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return x * y;
}
const int N = 2005;
int n, m, t, in[N], tp, vs[N];
vector<pr> vc[N], ve, vo;
pr st[N];
string s;
void dfs(int x, int fa) {
  in[x] = vs[x] = 1;
  for (auto y : vc[x])
    if (!vs[y.F]) {
      st[++tp] = {x, y.S};
      dfs(y.F, x);
      --tp;
      if (ve.size())
        return;
    } else if (in[y.F] && y.F != fa) {
      ve.push_back({x, y.S});
      do {
        ve.push_back(st[tp]);
        --tp;
      } while (st[tp + 1].F != y.F);
      return;
    }
  in[x] = 0;
}
int main() {
  ios::sync_with_stdio(false);
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= 2 * n; ++i)
      vc[i].clear(), vs[i] = 0;
    ve.clear();
    tp = 0;
    memset(in, 0, sizeof(in));
    for (int i = 1, x, y; i <= 2 * n; ++i) {
      cin >> x >> y;
      y += n;
      vc[x].push_back({y, i});
      vc[y].push_back({x, i});
    }
    for (int i = 1; i <= n; ++i)
      if (!ve.size())
        dfs(i, 0);
    reverse(ve.begin(), ve.end());
    while (ve.size() > 4) {
      int md = ve.size() / 2;
      if (md % 2 == 0)
        ++md;
      if (ve[md].F > n)
        cout << "? " << ve[0].F << " " << ve[md].F - n << endl;
      else
        cout << "? " << ve[md].F << " " << ve[0].F - n << endl;
      int x, fl = 0;
      cin >> x;
      for (int i = 0; i < md; ++i)
        if (ve[i].S == x)
          fl = 1;
      if (fl) {
        vo.clear();
        vo.push_back({ve[0].F, x});
        for (int i = md; i < ve.size(); ++i)
          vo.push_back(ve[i]);
        ve = vo;
      } else {
        vo.clear();
        for (int i = 0; i < md; ++i)
          vo.push_back(ve[i]);
        vo.push_back({ve[md].F, x});
        ve = vo;
      }
    }
    if (ve[0].F > n)
      cout << "! " << ve[1].F << " " << ve[3].F << " " << ve[0].F - n << " "
           << ve[2].F - n << endl;
    else
      cout << "! " << ve[0].F << " " << ve[2].F << " " << ve[1].F - n << " "
           << ve[3].F - n << endl;
    cin >> s;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/