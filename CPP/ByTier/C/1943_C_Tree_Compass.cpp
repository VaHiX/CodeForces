// Problem: CF 1943 C - Tree Compass
// https://codeforces.com/contest/1943/problem/C

/*
 * Problem: C. Tree Compass
 * 
 * Purpose: This code finds the minimum number of operations to color all vertices of a tree black.
 *          Each operation colors all vertices at a given distance from a chosen vertex.
 * 
 * Algorithms/Techniques:
 *   - Tree diameter finding using BFS twice
 *   - Strategy to partition the tree into layers and color them optimally
 * 
 * Time Complexity: O(n) per test case, where n is the number of vertices
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 * 
 * Approach:
 *   1. Find the diameter of the tree by performing BFS twice
 *   2. Color vertices layer by layer from the diameter endpoints
 *   3. The number of operations is derived from the diameter length
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

#define itn int
#define all(x) (x).begin(), (x).end()
#define make_unique(x)                                                         \
  sort(all((x)));                                                              \
  (x).resize(unique(all((x))) - (x).begin())
using namespace std;
inline int nxt() {
  int x;
  cin >> x;
  return x;
}
void solve() {
  int n = nxt();
  vector<vector<int>> a(n);
  for (int i = 0; i < n - 1; ++i) {
    int u = nxt() - 1, v = nxt() - 1;
    a[u].push_back(v);
    a[v].push_back(u);
  }
  auto find_dist = [&](int from) {
    vector<int> d(n, -1);
    d[from] = 0;
    vector<int> st = {from};
    while (!st.empty()) {
      int v = st.back();
      st.pop_back();
      for (int x : a[v]) {
        if (d[x] == -1) {
          d[x] = d[v] + 1;
          st.push_back(x);
        }
      }
    }
    return d;
  };
  auto d = find_dist(0);
  int v = max_element(all(d)) - d.begin();
  d = find_dist(v);
  int u = max_element(all(d)) - d.begin();
  int len = d[u] + 1;
  cout << (len / 2 + 1) / 2 + ((len + 1) / 2 + 1) / 2 << "\n";
  for (int p : {0, 1}) {
    int cnt = (len + p) / 2;
    int l = !p;
    int r = l + (cnt - 1) * 2;
    int mid = (l + r) / 2;
    int ver = u;
    while (d[ver] > mid) {
      for (int x : a[ver]) {
        if (d[x] == d[ver] - 1) {
          ver = x;
          break;
        }
      }
    }
    for (int i = l; i <= d[ver]; i += 2) {
      cout << ver + 1 << " " << d[ver] - i << "\n";
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = nxt();
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/