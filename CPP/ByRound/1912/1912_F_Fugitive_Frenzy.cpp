// Problem: CF 1912 F - Fugitive Frenzy
// https://codeforces.com/contest/1912/problem/F

/*
 * Problem: F. Fugitive Frenzy
 *
 * Purpose: Compute the expected duration of a chase on a tree, where the police officer moves first and
 *          the fugitive responds optimally. The chase is modeled as a game with incomplete information,
 *          and the solution uses iterative approximation to find the expected time.
 *
 * Algorithms/Techniques:
 * - Floyd-Warshall to compute all-pairs shortest distances in the tree
 * - Iterative method to solve linear system for expected values
 * - Game theory: minimax approach with mixed strategies
 *
 * Time Complexity: O(N^3 + M * iterations) where N is number of vertices, M is number of leaves,
 *                  and iterations is the number of iterations in the convergence loop (~2000).
 * Space Complexity: O(N^2 + M) for storing adjacency matrix, distances, and leaf nodes.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#ifndef ALGO
#define DUMP(...)
#endif
using i64 = long long;
template <typename T, typename U> inline bool enlarge(T &a, U b) {
  return a < b ? (a = b, true) : false;
}
template <typename T, typename U> inline bool minify(T &a, U b) {
  return a > b ? (a = b, true) : false;
}
using Float = long double;
struct Solver {
  void solve(int ca, std::istream &reader) {
    int N;
    reader >> N;
    // Initialize adjacency matrix with large values
    std::vector<std::vector<int>> adj(N, std::vector<int>(N, N));
    std::vector<int> deg(N);
    for (int i = 0; i < N - 1; ++i) {
      int x, y;
      reader >> x >> y;
      --x;
      --y;
      deg[x]++;
      deg[y]++;
      adj[x][y] = adj[y][x] = 1;
    }
    // Set diagonal to 0 (distance from node to itself)
    for (int i = 0; i < N; ++i) {
      adj[i][i] = 0;
    }
    // Floyd-Warshall to compute shortest paths between all pairs of vertices
    for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          minify(adj[i][j], adj[i][k] + adj[k][j]);
        }
      }
    }
    // Find all leaf nodes (degree = 1)
    std::vector<int> leaves;
    for (int i = 0; i < N; ++i) {
      if (deg[i] == 1) {
        leaves.emplace_back(i);
      }
    }
    int M = leaves.size();
    // Initialize y vector with 1s for iterative computation
    std::vector<Float> y(M, 1);
    // Iterative process to converge towards solution
    for (int iteration = 0; iteration < 2000; ++iteration) {
      std::vector<Float> yy(M);
      for (int i = 0; i < M; ++i) {
        Float p = 0, q = -1;
        for (int j = 0; j < M; ++j)
          if (i != j) {
            p += y[j];
            q += adj[leaves[i]][leaves[j]] * y[j] + 1;
          }
        yy[i] = p / q;
      }
      y.swap(yy);
    }
    DUMP(y);
    int S;
    reader >> S;
    --S;
    {
      Float p = 0, q = -1;
      for (int j = 0; j < M; ++j)
        if (leaves[j] != S) {
          p += y[j];
          q += adj[S][leaves[j]] * y[j] + 1;
        }
      Float result = q / p;
      printf("%.13f\n", (double)result);
    }
  }
};
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;
  int cas = 1;
  for (int ca = 1; ca <= cas; ++ca) {
    auto solver = std::make_unique<Solver>();
    solver->solve(ca, reader);
  }
}


// https://github.com/VaHiX/CodeForces/