// Problem: CF 489 D - Unbearable Controversy of Being
// https://codeforces.com/contest/489/problem/D

/*
 * Problem: Unbearable Controversy of Being
 * Algorithm: Count "damn rhombi" in a directed graph
 * 
 * A "damn rhombus" is a set of four nodes {a, b, c, d} such that:
 * - There is a path from a to c via b and another via d
 * - The connections a->b, b->c, a->d, d->c are direct edges
 * 
 * Approach:
 * - Build an adjacency list and adjacency matrix for fast lookup
 * - For each pair of nodes (source, target), count how many intermediate nodes
 *   can be used to form a path from source to target
 * - For each such intermediate node count 'common', the number of paths from source to target
 *   through different intermediate nodes, we compute C(common, 2) = common*(common-1)/2 combinations
 * 
 * Time Complexity: O(n^2 * m) where n is number of nodes, m is number of edges
 * Space Complexity: O(n^2) for adjacency matrix and O(n * avg_degree) for adjacency list
 */
#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  std::vector<std::vector<long>> edges(n + 1);  // adjacency list
  std::vector<std::vector<bool>> adj(n + 1, std::vector<bool>(n + 1, 0));  // adjacency matrix
  for (long p = 0; p < m; p++) {
    long a, b;
    scanf("%ld %ld\n", &a, &b);
    edges[a].push_back(b);  // build adjacency list
    adj[a][b] = 1;  // mark edge in adjacency matrix
  }
  long long output(0);  // result counter
  for (long source = 1; source <= n; source++) {
    for (long target = 1; target <= n; target++) {
      if (source == target) {
        continue;  // skip same source and target
      }
      long long common = 0;  // number of common intermediate nodes
      for (long p = 0; p < edges[source].size(); p++) {
        if (adj[edges[source][p]][target] > 0) {  // if there's a path from source->intermediate->target
          ++common;
        }
      }
      output += common * (common - 1) / 2;  // combinations of choosing 2 from common paths
    }
  }
  printf("%lld\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/