// Problem: CF 1868 F - LIS?
// https://codeforces.com/contest/1868/problem/F

/*
 * Problem: F. LIS?
 * 
 * Purpose:
 *   Given an array of integers, we aim to find the minimum number of operations 
 *   to make all elements negative. Each operation selects the interval with the 
 *   maximum sum and subtracts 1 from all its elements. The algorithm uses 
 *   convex hull trick to efficiently manage and query the maximum sum subarray.
 *
 * Algorithms/Techniques:
 *   - Convex Hull Trick (CHT) for maintaining slopes of prefix sums
 *   - Divide and conquer with optimization using CHT
 *   - Prefix sums for efficient interval sum calculation
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <utility>

using namespace std;
constexpr int N = 5e5 + 1, S = 1 << 20, B = 16;
int n;
int64_t ps[N];
template <bool dir> struct ConvexHullTree {
  vector<int> t[S / B / 2];
  bool cmp(int a, int b, int64_t c) {
    return (ps[c] - ps[b]) * (c - a) < (ps[c] - ps[a]) * (c - b);
  }
  void build(int i, int L, int R) {
    if (R <= L + B)
      return;
    int st = L, ed = R;
    if (!dir)
      swap(--st, --ed);
    for (int j = st, d = (ed > st) - (ed < st); j != ed; j += d) {
      auto &ch = t[i];
      while (ch.size() >= 2) {
        if (cmp(ch.end()[-2], ch.back(), j))
          break;
        ch.pop_back();
      }
      ch.push_back(j);
    }
    t[i].shrink_to_fit();
    build(2 * i + 1, L, (L + R) / 2);
    build(2 * i + 2, (L + R) / 2, R);
  }
  int tangent(int i, int L, int R, int l, int r, int j) {
    if (R <= l || r <= L)
      return l;
    if (R == L + 1)
      return L;
    if (l <= L && R <= r) {
      if (R <= L + B) {
        int x = L;
        for (int i = L; ++i < R;)
          if (cmp(x, i, j))
            x = i;
        return x;
      }
      int l = 0, r = t[i].size();
      while (r != l + 1) {
        int m = (l + r) / 2;
        (cmp(t[i][m - 1], t[i][m], j) ? l : r) = m;
      }
      return t[i][l];
    }
    auto al = tangent(2 * i + 1, L, (L + R) / 2, l, r, j);
    auto ar = tangent(2 * i + 2, (L + R) / 2, R, l, r, j);
    return cmp(al, ar, j) ? ar : al;
  }
};
ConvexHullTree<0> low;
ConvexHullTree<1> high;
int64_t get_cost(int l, int r, int paid, int64_t ans) {
  while (r > l + 1 && ps[l] + paid > ps[l + 1])
    ++l;
  while (r > l + 1 && ps[r] - paid < ps[r - 1])
    --r;
  if (r <= l + 1)
    return max({}, ps[r] - ps[l] + 1 - paid) + ans;
  int x0 = low.tangent(0, 0, n, l + 1, r + 1, l);
  auto tail = [&](int m, int p) {
    if (m - l < r - m)
      return get_cost(m, r, p, get_cost(l, m, p, ans + p - paid));
    else
      return get_cost(l, m, p, get_cost(m, r, p, ans + p - paid));
  };
  if (ps[x0] < ps[l] + paid * int64_t(x0 - l)) {
    return tail(x0, paid);
  }
  int x1 = high.tangent(0, 0, n, l, r, r);
  if (ps[x1] > ps[r] - paid * int64_t(r - x1)) {
    return tail(x1, paid);
  }
  int c0 = (ps[x0] - ps[l]) / (x0 - l), c1 = (ps[r] - ps[x1]) / (r - x1);
  if (c0 >= c1)
    c0 = c1, x0 = x1;
  ++c0;
  return tail(x0, c0);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> ps[i];
  if (is_sorted(ps + 1, ps + n + 1, less{}) ||
      is_sorted(ps + 1, ps + n + 1, greater{})) {
    return cout << max({}, max(ps[1], ps[n]) + 1), 0;
  }
  partial_sum(ps, ps + n + 1, ps);
  ++n;
  high.build(0, 0, n);
  low.build(0, 0, n);
  cout << get_cost(0, n - 1, 0, 0);
}


// https://github.com/VaHiX/CodeForces/