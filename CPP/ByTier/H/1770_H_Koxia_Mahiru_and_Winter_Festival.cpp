// Problem: CF 1770 H - Koxia, Mahiru and Winter Festival
// https://codeforces.com/contest/1770/problem/H

/*
Purpose: This code solves the problem of finding optimal paths for Koxia and Mahiru to traverse a grid graph during a Winter Festival, minimizing the maximum edge congestion.

Algorithms/Techniques: 
- Recursive decomposition of paths based on permutations p and q
- Greedy path building with careful handling of endpoints

Time Complexity: O(n^3) in worst case due to recursive calls and path building
Space Complexity: O(n^3) for storing the paths and recursion stack

The approach recursively decomposes the problem by selecting a "middle" point (m) and building paths such that:
1. Vertical paths (NS) from top to bottom
2. Horizontal paths (EW) from left to right
Each recursive call reduces the problem size, and the algorithm ensures minimum congestion.
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;
struct Paths {
  vector<vector<pair<int, int>>> NS, EW;
  Paths() {
    NS.clear();
    EW.clear();
  }
};
Paths solve(vector<int> p, vector<int> q) {
  int n = p.size();
  Paths Ret;
  Ret.NS.resize(n);
  Ret.EW.resize(n);
  if (n == 0)
    return Ret;
  if (n == 1) {
    Ret.NS[0].push_back({1, 1});
    Ret.EW[0].push_back({1, 1});
    return Ret;
  }
  for (int i = 1; i <= n; i++) {
    Ret.NS[0].push_back({i, 1});
    Ret.NS[n - 1].push_back({i, n});
  }
  for (int i = 2; i <= p[0]; i++)
    Ret.NS[0].push_back({n, i});
  for (int i = n - 1; i >= p[n - 1]; i--)
    Ret.NS[n - 1].push_back({n, i});
  vector<int> p_new(0);
  for (int i = 1; i <= n - 2; i++)
    p_new.push_back(p[i] - (p[i] > p[0]) - (p[i] > p[n - 1]));
  for (int i = 1; i <= n; i++)
    Ret.EW[0].push_back({1, i});
  for (int i = 2; i <= q[0]; i++)
    Ret.EW[0].push_back({i, n});
  int m = 1;
  if (p[0] == 1 && p[n - 1] == n && q[0] == 1 && q[n - 1] == n) {
    m = n - 1;
    for (int i = 1; i <= n; i++)
      Ret.EW[n - 1].push_back({n, i});
  } else {
    for (int i = 1; i < n; i++)
      if (q[i] < q[m])
        m = i;
    for (int i = m + 1; i >= 2; i--)
      Ret.EW[m].push_back({i, 1});
    for (int i = 1; i < n; i++)
      Ret.EW[m].push_back({1, i});
    for (int i = 1; i <= q[m]; i++)
      Ret.EW[m].push_back({i, n});
  }
  vector<int> q_new(0);
  for (int i = 1; i < n; i++)
    if (i != m)
      q_new.push_back(q[i] - (q[i] > q[0]) - (q[i] > q[m]));
  if (n > 1) {
    Paths S = solve(p_new, q_new);
    int t;
    for (int i = 1; i < n - 1; i++) {
      Ret.NS[i].push_back({1, i + 1});
      for (auto [x, y] : S.NS[i - 1]) {
        Ret.NS[i].push_back({x + 1, y + 1});
        t = y + 1;
      }
      Ret.NS[i].push_back({n, t});
      if (p[i] != t)
        Ret.NS[i].push_back({n, p[i]});
    }
    int l = 0;
    for (int i = 1; i < n; i++)
      if (i != m) {
        Ret.EW[i].push_back({i + 1, 1});
        if (i > m)
          Ret.EW[i].push_back({i, 1});
        for (auto [x, y] : S.EW[l]) {
          Ret.EW[i].push_back({x + 1, y + 1});
          t = x + 1;
        }
        Ret.EW[i].push_back({t, n});
        if (q[i] != t)
          Ret.EW[i].push_back({q[i], n});
        ++l;
      }
  }
  return Ret;
}
int main() {
  int n;
  vector<int> p, q;
  cin >> n;
  p.resize(n);
  q.resize(n);
  for (int i = 0; i < n; i++)
    cin >> p[i];
  for (int i = 0; i < n; i++)
    cin >> q[i];
  Paths Solution = solve(p, q);
  for (auto path : Solution.NS) {
    cout << path.size();
    for (auto [x, y] : path)
      cout << ' ' << x << ' ' << y;
    cout << '\n';
  }
  for (auto path : Solution.EW) {
    cout << path.size();
    for (auto [x, y] : path)
      cout << ' ' << x << ' ' << y;
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/