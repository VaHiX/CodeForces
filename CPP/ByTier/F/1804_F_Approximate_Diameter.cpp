// Problem: CF 1804 F - Approximate Diameter
// https://codeforces.com/contest/1804/problem/F

/*
 * Problem: Approximate Diameter in Dynamic Graphs
 *
 * Purpose:
 * This code efficiently approximates the diameter of a graph that undergoes
 * sequential edge additions. The diameter is the maximum shortest path distance
 * between any two vertices. The solution uses a binary search on the diameter
 * combined with BFS to compute distances, providing approximate values within a
 * factor of 2 of the true diameter.
 *
 * Algorithms/Techniques:
 * - Binary search on the diameter (using a divide-and-conquer approach)
 * - BFS for computing shortest distances
 * - Efficient pre-processing to track edges added at each step
 * - Recursive function to compute approximations using bounds
 *
 * Time Complexity: O((n + m + q) * log(n + m + q))
 * Space Complexity: O(n * (n + m + q))
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m + q; i++) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].emplace_back(y, i);
    g[y].emplace_back(x, i);
  }
  vector<int> ans(q + 1, -1);
  auto Calc = [&](int bound) {
    vector<int> d(n, -1);
    d[0] = 0;
    vector<int> que(n, 0);
    int qSz = 1;
    for (int b = 0; b < qSz; b++) {
      for (auto &e : g[que[b]]) {
        if (e.second < bound && d[e.first] == -1) {
          que[qSz++] = e.first;
          d[e.first] = d[que[b]] + 1;
        }
      }
    }
    int ret = *max_element(d.begin(), d.end());
    ans[bound - m] = ret;
    return ret;
  };
  function<void(int, int, int, int)> Dfs = [&](int l, int vl, int r, int vr) {
    if (r - l <= 1) {
      return;
    }
    if (vl <= 2 * vr) {
      for (int i = l + 1; i < r; i++) {
        ans[i - m] = vl;
      }
      return;
    }
    int mid = (l + r) >> 1;
    int vmid = Calc(mid);
    Dfs(l, vl, mid, vmid);
    Dfs(mid, vmid, r, vr);
  };
  Dfs(m, Calc(m), m + q, Calc(m + q));
  for (int i = 0; i <= q; i++) {
    cout << ans[i] << " \n"[i == q];
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/