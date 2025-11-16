// Problem: CF 1764 H - Doremy's Paint 2
// https://codeforces.com/contest/1764/problem/H

/*
  Algorithm/Techniques: 
  - Coordinate compression + Binary Indexed Tree (Fenwick Tree)
  - Segment-based operations with interval updates and queries
  - Reverse simulation with a set to track active intervals
  - Efficiently maintaining color counts using BIT and interval management

  Time Complexity: O((n + m) * log n + m * log^2 n)
  Space Complexity: O(n + m)
*/

#include <algorithm>
#include <iostream>
#include <set>

const int N = 4e5 + 10;
int n, m, k, L[N], R[N], c[N], ans[N];
void upd(int x, int k) {
  for (++x; x < N; x += x & -x) // Update BIT
    c[x] += k;
}
int qry(int x, int ret = 0) {
  for (++x; x; x -= x & -x) // Query BIT
    ret += c[x];
  return ret;
}
struct node {
  int l, r, t;
  bool operator<(const node &rhs) const { return l < rhs.l; } // For set ordering
};
std::set<node> s;
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  std::cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) // Read operation intervals
    std::cin >> L[i] >> R[i];
  s.insert({1, n, 2 * m}); // Initialize with full interval
  for (int i = 2 * m - 1; i >= 0; --i) { // Process backwards
    int l = L[i % m], r = R[i % m], mx = 0;
    auto it = s.lower_bound({l, 0, 0}); // Find first interval containing l
    if (it == s.end())
      --it;
    if (it->l > l)
      --it;
    while (it != s.end() && it->l <= r) { // Process all overlapping intervals
      auto P = *it;
      it = s.erase(it); // Remove interval P
      upd(P.t, -(P.r - P.l + 1)), mx = std::max(mx, P.t); // Adjust count in BIT
      if (P.l < l) // Split and insert left part
        s.insert({P.l, l - 1, P.t}), upd(P.t, l - P.l);
      if (P.r > r) // Split and insert right part
        s.insert({r + 1, P.r, P.t}), upd(P.t, P.r - r);
    }
    s.insert({l, l, mx}), upd(mx, 1); // Add new color to point l
    if (l < r) // Update range [l+1, r] with new operation index
      s.insert({l + 1, r, i}), upd(i, r - l);
    if (i < m) // Compute answer for current index
      ans[i] = n - qry(i + k - 1); // Number of distinct colors after k operations
  }
  for (int i = 0; i < m; ++i) // Output results
    std::cout << ans[i] << " \n"[i == m - 1];
}


// https://github.com/VaHiX/CodeForces/