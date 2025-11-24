// Problem: CF 486 D - Valid Sets
// https://codeforces.com/contest/486/problem/D

/*
 * Problem: Valid Sets on Tree
 * 
 * Description:
 * Given a tree with n nodes, each having a value a[i], we need to count the number of valid sets.
 * A valid set S of nodes must satisfy:
 * 1. S is non-empty and connected.
 * 2. For any two nodes u, v in S, all nodes on the path between them must also be in S.
 * 3. The difference between the maximum and minimum values in S is at most d.
 * 
 * Algorithm:
 * - For each node in the tree, we perform a DFS to count how many valid subsets rooted at that node exist.
 * - In DFS, we ensure that for any valid subset, the values follow the constraint.
 * - We use memoization to avoid recomputation.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

#include <cstdio>
#include <vector>
typedef long long ll;
const ll MOD = 1000000007;

// DFS function to count valid sets starting from 'node'
// Parameters:
//   node: current node being processed
//   from: parent node in DFS traversal
//   g: adjacency list of the tree
//   a: array of node values
//   minValue: minimum value in the current valid set
//   diff: allowed difference (d)
//   root: root node of the current DFS
ll dfs(long node, long from, const std::vector<std::vector<long>> &g,
       const std::vector<long> &a, long minValue, long diff, long root) {
  ll res(1); // Initialize result as 1 (empty set)
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (u == from) {
      continue; // Skip parent node
    }
    // Check if node u can be included in current valid set
    if (a[u] <= minValue + diff &&
        ((a[u] > minValue) || (a[u] == minValue && u > root))) {
      // Multiply the result with number of valid subsets in subtree of u
      res *= (dfs(u, node, g, a, minValue, diff, root) + 1);
      res %= MOD; // Apply modulo to prevent overflow
    }
  }
  return res;
}

int main() {
  long d, n;
  scanf("%ld %ld", &d, &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<std::vector<long>> g(n);
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  ll total(0);
  for (long p = 0; p < n; p++) {
    // Perform DFS for each node as potential root of valid set
    ll cur = dfs(p, -1, g, a, a[p], d, p);
    total += cur;
    total %= MOD;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/