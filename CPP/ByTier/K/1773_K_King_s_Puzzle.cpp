// Problem: CF 1773 K - King's Puzzle
// https://codeforces.com/contest/1773/problem/K
//
// Constructive solution that prints a graph (as an edge list) meeting the
// problem constraints. The program handles several small special cases and
// otherwise builds an edge list using a fixed pattern. The code intentionally
// prints "YES"/"NO" where appropriate, then outputs the number of edges
// followed by each edge as "u v" on its own line.
//
// Notes about structure:
// - Small special cases (n==1, n==2) are handled explicitly.
// - If n == k the code prints "NO" and exits (no solution under constraints).
// - For k == 1 a simple cycle on n nodes is output.
// - For k == 2 the code outputs a star centered at node 1.
// - Otherwise the code builds a base path (1-2-3-...-n) and then augments
//   additional edges on the tail segment to meet the construction requirements.
//
// Complexity: building the edges takes O(E) time where E is the number of
// edges produced; in the worst case E = O(n^2) due to the nested loop, but
// for typical constraints this remains manageable.

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  // tiny instances handled directly with known constructions
  if (n == 1 && k == 1) {
    // Single node, k==1 -> trivial valid graph with 0 edges
    cout << "YES\n0\n";
    return 0;
  }

  if (n == 2 && k == 1) {
    // Two nodes and k==1 -> one edge connecting them
    cout << "YES\n";
    cout << 1 << '\n' << 1 << ' ' << 2 << '\n';
    return 0;
  }

  // If number of components requested equals number of nodes, impossible
  // to build a connected structure that meets the problem's additional
  // requirements (handled by the original solution with NO).
  if (n == k) {
    cout << "NO\n";
    return 0;
  }

  // For all other cases, a solution exists and will be constructed
  cout << "YES\n";

  if (k == 1) {
    // k==1: output a simple cycle on n nodes (n edges)
    cout << n << '\n';
    for (int i = 1; i < n; i++) {
      cout << i << ' ' << i + 1 << '\n';
    }
    cout << n << ' ' << 1 << '\n';
    return 0;
  }

  if (k == 2) {
    // k==2: output a star centered at node 1 (n-1 edges)
    cout << n - 1 << '\n';
    for (int i = 2; i <= n; i++) {
      cout << 1 << ' ' << i << '\n';
    }
    return 0;
  }

  // General construction for k >= 3 and n > k.
  // Start by creating a path 1-2, 2-3, ..., (n-1)-n. This guarantees basic
  // connectivity along the chain and provides a base set of edges.
  vector<int> x, y;
  for (int i = 1; i < n; i++) {
    x.push_back(i);
    y.push_back(i + 1);
  }

  // Augment the tail of the node sequence with extra edges. The outer loop
  // iterates from `n-k+1` to `n` in steps of 2; for each such `i` we connect
  // `i` to all nodes `j` with `j >= i+2` up to `n`. This pattern appends
  // additional edges among the last k nodes, following the original
  // constructive approach.
  for (int i = n - k + 1; i <= n; i += 2) {
    for (int j = i + 2; j <= n; j++) {
      x.push_back(i);
      y.push_back(j);
    }
  }

  // Output total edge count and the edges themselves
  cout << (int)x.size() << '\n';
  for (int i = 0; i < (int)x.size(); i++) {
    cout << x[i] << ' ' << y[i] << '\n';
  }

  return 0;
}

// https://github.com/VaHiX/CodeForces/