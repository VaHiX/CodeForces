// Problem: CF 2156 F2 - Strange Operation (Hard Version)
// https://codeforces.com/contest/2156/problem/F2

/*
Algorithm: 
This solution uses a segment tree-based approach to simulate the process of transforming a permutation into its lexicographically smallest form using the given operation. The key idea is to determine for each position in the input permutation, which value should be assigned to it in the final permutation. The approach uses two segment trees:
1. A location segment tree (LocSegmentTree) to efficiently find positions of elements
2. A rank segment tree (RankSegmentTree) to keep track of ranks of elements

Time Complexity: O(n log n) - Each query and update in segment trees is O(log n), and we do these operations for each element.
Space Complexity: O(n) - Space used by the two segment trees and auxiliary arrays.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

const long long INF = 2e9;
struct LocSegmentTree {
  int n;
  std::vector<int> t;
  LocSegmentTree(int size, const std::vector<int> &initial) {
    n = size;
    t.resize(2 * n);
    for (int i = 0; i < n; ++i)
      t[n + i] = initial[i];
    for (int i = n - 1; i > 0; --i)
      t[i] = std::min(t[i << 1], t[i << 1 | 1]);
  }
  void update(int p, int value) {
    for (t[p += n] = value; p > 1; p >>= 1)
      t[p >> 1] = std::min(t[p], t[p ^ 1]);
  }
  int query(int l, int r) {
    int res = INF;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = std::min(res, t[l++]);
      if (r & 1)
        res = std::min(res, t[--r]);
    }
    return res;
  }
};
struct RankSegmentTree {
  int n;
  std::vector<int> t;
  std::vector<int> lazy;
  RankSegmentTree(int size) {
    n = size;
    t.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
    std::vector<int> initial_ranks(n);
    std::iota(initial_ranks.begin(), initial_ranks.end(), 0);
    build(initial_ranks, 1, 0, n - 1);
  }
  void build(const std::vector<int> &a, int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
    }
  }
  void push(int v) {
    if (lazy[v] != 0) {
      t[v * 2] += lazy[v];
      lazy[v * 2] += lazy[v];
      t[v * 2 + 1] += lazy[v];
      lazy[v * 2 + 1] += lazy[v];
      lazy[v] = 0;
    }
  }
  void range_add(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
      return;
    if (l == tl && r == tr) {
      t[v] += addend;
      lazy[v] += addend;
    } else {
      push(v);
      int tm = (tl + tr) / 2;
      range_add(v * 2, tl, tm, l, std::min(r, tm), addend);
      range_add(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, addend);
    }
  }
  int point_query(int v, int tl, int tr, int pos) {
    if (tl == tr) {
      return t[v];
    }
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      return point_query(v * 2, tl, tm, pos);
    } else {
      return point_query(v * 2 + 1, tm + 1, tr, pos);
    }
  }
};
void solve() {
  int n;
  std::cin >> n;
  std::vector<int> p(n);
  std::vector<int> location(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
    p[i]--;
    location[p[i]] = i;
  }
  LocSegmentTree seg(n, location);
  RankSegmentTree rank_tree(n);
  std::vector<int> ans(n, -1);
  int curr = 1;
  for (int i = 0; i < n; ++i) {
    if (ans[i] >= 0) {
      continue;
    }
    int rank = rank_tree.point_query(1, 0, n - 1, p[i]);
    if (rank % 2 == 0) {
      // Even rank - assign current value directly
      rank_tree.range_add(1, 0, n - 1, p[i] + 1, n - 1, -1);
      seg.update(p[i], INF);
      ans[i] = curr;
      curr++;
    } else {
      // Odd rank - need to find a valid j to perform the operation
      int current_pos = i;
      int j = -1;
      while (true) {
        // Find the position of the element smaller than current
        j = seg.query(0, p[current_pos] - 1);
        int next_rank = rank_tree.point_query(1, 0, n - 1, p[j]);
        if (next_rank % 2 != 0) {
          // Continue search with this element
          current_pos = j;
          continue;
        }
        break; // Found a suitable j
      }
      // Assign the values for i and j
      ans[j] = curr;
      ans[i] = curr + 1;
      curr += 2;
      // Update segment tree and rank tree
      seg.update(p[i], INF);
      seg.update(p[j], INF);
      if (p[i] < p[j]) {
        rank_tree.range_add(1, 0, n - 1, p[i] + 1, p[j] - 1, -1);
        rank_tree.range_add(1, 0, n - 1, p[j] + 1, n - 1, -2);
      } else {
        rank_tree.range_add(1, 0, n - 1, p[j] + 1, p[i] - 1, -1);
        rank_tree.range_add(1, 0, n - 1, p[i] + 1, n - 1, -2);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << (i == n - 1 ? "" : " ");
  }
  std::cout << "\n";
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/