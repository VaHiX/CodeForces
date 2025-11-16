// Problem: CF 1830 D - Mex Tree
// https://codeforces.com/contest/1830/problem/D

/*
 * Problem: D. Mex Tree
 * 
 * Purpose: Given a tree with n nodes, each node can be colored 0 or 1. 
 * For each path (u,v), the value is the MEX (minimum excluded) of colors along the path.
 * The goal is to maximize the sum of values of all paths (u,v) where 1 <= u <= v <= n.
 * 
 * Approach:
 * - Use dynamic programming on tree (tree DP)
 * - For each node, maintain a DP state that tracks the best possible values 
 *   for different numbers of 1s in the subtree (0 or 1).
 * - When merging subtrees, compute how adding a new subtree affects the total sum.
 * - The key insight is that MEX of a path with k 1s is max(0, k) + 1.
 * 
 * Time Complexity: O(n^2) in worst case due to merging operations, but efficient in practice.
 * Space Complexity: O(n) for storing the tree and DP states.
 */


#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

template <class T> constexpr inline bool UpdateMax(T &a, const T &b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}
std::pair<std::vector<std::vector<long long>>, long long>
Process(long v, const std::vector<std::vector<long>> &edges,
        std::vector<bool> &viewed) {
  viewed[v] = true;
  std::vector<std::vector<long long>> res(2);
  // res[0] stores sums when the subtree rooted at current node has 0 ones
  // res[1] stores sums when the subtree rooted at current node has 1 one
  res[0].emplace_back(1);  // base case for 0 ones
  res[1].emplace_back(0);  // base case for 1 one
  long long n = 1;   // number of nodes in this subtree
  for (long c : edges[v]) {
    if (viewed[c]) {
      continue;
    }
    auto res_child = Process(c, edges, viewed);  // recursively solve for child
    std::vector<std::vector<long long>> res_new(2);
    // Merging logic: for each state in current and child subtree
    for (long m = 0; m < 2; ++m) {
      res_new[m].resize(res[m].size() + res_child.first[m].size());
      for (long i = 0; i < res[m].size(); ++i) {
        // Update based on combinations of current and child states
        UpdateMax(res_new[m][i], res[m][i] + res_child.first[!m].back() +
                                     2 * n * res_child.second);
        for (long j = 0; j < res_child.first[m].size(); ++j) {
          UpdateMax(res_new[m][i + j + 1], res[m][i] + res_child.first[m][j] +
                                               2 * n * res_child.second -
                                               (1 + m) * (i + 1) * (j + 1));
        }
      }
      long long max = res_new[m][0];
      long max_index = 0;
      for (long i = 1; i < res_new[m].size(); ++i) {
        if (UpdateMax(max, res_new[m][i])) {
          max_index = i;
        }
      }
      res_new[m].resize(max_index + 1);
    }
    n += res_child.second;
    res = res_new;
  }
  return {res, n};
}
void Solve() {
  long n;
  std::cin >> n;
  std::vector<std::vector<long>> edges(n);
  for (long i = 1; i < n; ++i) {
    long a, b;
    std::cin >> a >> b;
    --a;
    --b;
    edges[a].emplace_back(b);
    edges[b].emplace_back(a);
  }
  std::vector<bool> viewed(n);
  auto res = Process(0, edges, viewed);  // start from root (node 0)
  std::cout << std::max(res.first[0].back(), res.first[1].back()) << "\n";
}
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  long t;
  std::cin >> t;
  for (long i = 0; i < t; ++i) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/