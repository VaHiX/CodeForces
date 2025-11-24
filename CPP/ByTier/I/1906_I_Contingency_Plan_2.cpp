// Problem: CF 1906 I - Contingency Plan 2
// https://codeforces.com/contest/1906/problem/I

/*
 * Problem: Contingency Plan 2
 * 
 * Purpose:
 * This code solves a problem where we are given a tree of computers connected by cables,
 * and we want to determine the minimum number of new directed cables to add to make the
 * network not vulnerable during a disaster. A network is not vulnerable if there exists
 * exactly one topological order (i.e., a unique way to arrange the nodes such that all
 * edges point from earlier to later nodes in the order).
 * 
 * Approach:
 * We use a depth-first search (DFS) with a Y-combinator to traverse the tree and 
 * determine where to place new directed edges to ensure only one valid topological order.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 * 
 * Techniques Used:
 * - Tree Traversal using DFS
 * - Y-Combinator for recursive lambda
 * - Topological ordering detection and correction via directed edge additions
 */

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

namespace std {
template <class Fun> class y_combinator_result {
  Fun fun_;

public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}
  template <class... Args> decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};
template <class Fun> decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
} // namespace std

int main() {
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int N;
  cin >> N;
  // Build adjacency list where each edge stores (neighbor, direction)
  std::vector<std::vector<std::pair<int, int>>> adj(N);
  for (int e = 0; e < N - 1; e++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    // Add edge from u to v with direction 0
    adj[u].push_back({v, 0});
    // Add edge from v to u with direction 1
    adj[v].push_back({u, 1});
  }
  // Store the list of operations (new edges to add)
  std::vector<std::array<int, 2>> ops;
  ops.reserve(N + 1);
  // Lambda to add an operation (directed edge)
  auto add_op = [&](int x, int y, int xz) {
    if (x == N || y == N)
      return;
    if (xz == 1)
      ops.push_back({x, y});
    else
      ops.push_back({y, x});
  };
  // Outer range keeps track of the bounds for different directions
  std::array<int, 2> outer_range{N, N};
  // Traverse the tree with DFS using Y-combinator
  auto root_range =
      std::y_combinator([&](auto self, int cur, int prv) -> std::array<int, 2> {
        std::array<int, 2> res{cur, cur};
        for (auto [nxt, cur_z] : adj[cur]) {
          if (nxt == prv)
            continue;
          auto nxt_res = self(nxt, cur);
          // If the structure maintains topological order, update the range
          if (res[!cur_z] == cur && nxt_res[cur_z] == nxt) {
            res[!cur_z] = nxt_res[!cur_z];
          } else {
            // Add a new directed edge to break multiple orderings
            add_op(nxt_res[!cur_z], outer_range[cur_z], !cur_z);
            outer_range[cur_z] = nxt_res[cur_z];
          }
        }
        return res;
      })(0, -1);
  // Finalize the topological order by adding final edges from root
  add_op(root_range[0], outer_range[1], 0);
  add_op(root_range[1], outer_range[0], 1);
  cout << ops.size() << '\n';
  for (auto [x, y] : ops) {
    cout << x + 1 << ' ' << y + 1 << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/