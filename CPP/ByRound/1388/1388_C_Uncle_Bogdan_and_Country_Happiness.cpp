// Problem: CF 1388 C - Uncle Bogdan and Country Happiness
// https://codeforces.com/contest/1388/problem/C

/*
C. Uncle Bogdan and Country Happiness

Algorithm: DFS on tree with subtree aggregation
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This problem involves a tree structure representing a country with cities connected by roads. 
Each city has a population (p_i) and an observed happiness index (h_i). The task is to determine 
if the given happiness indexes are possible based on the people's movements and mood changes.

The solution uses DFS traversal from the root (city 1) to compute:
- Total population in each subtree
- Required happiness values that must be achieved in each node

Key idea:
1. For each node, we calculate how many people (from its subtree) need to have good mood versus bad mood.
2. We propagate these constraints upward and verify consistency.

For a subtree rooted at node u:
- pop[u] = total number of people living in the subtree
- hap[u] = net "good mood" count needed at that node

The checks done during DFS:
1. Ensure happiness index is consistent with population (parity check)
2. All happiness values must be within bounds [0, pop]
3. At each node, the happiness value should satisfy the constraint from children
*/

#include <cstdio>
#include <vector>
void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<long> &pop, std::vector<long> &hap, std::vector<bool> &vis,
         bool &possible) {
  if (!possible) { // Early termination if already impossible
    return;
  }
  if (vis[node]) { // Skip visited nodes
    return;
  }
  vis[node] = true; // Mark current node as visited
  long cnt(0); // Counter for happiness from children
  
  // Traverse all neighbors of the current node
  for (long u = 0; u < g[node].size(); u++) {
    long cur = g[node][u];
    if (vis[cur]) {
      continue; // Skip already visited nodes (tree edges)
    }
    dfs(cur, g, pop, hap, vis, possible); // Recursive DFS on child
    pop[node] += pop[cur]; // Aggregate population from subtree
    cnt += hap[cur]; // Add happiness contribution from child
  }
  
  // The total happiness at node = h_node + total people in subtree (must be even for balancing)
  if ((hap[node] + pop[node]) % 2) {
    possible = false; // Odd sum makes distribution impossible
    return;
  }
  
  // Compute required happiness at current node
  hap[node] = (hap[node] + pop[node]) / 2;
  
  // Boundary checks
  if (hap[node] < 0 || hap[node] > pop[node]) {
    possible = false; // Happiness must lie between 0 and population
    return;
  }
  
  // Ensure no child can satisfy happiness more than current node
  if (hap[node] < cnt) {
    possible = false; // Cannot exceed child contributions
    return;
  }
  return;
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> pop(n + 1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &pop[p]);
    }
    std::vector<long> hap(n + 1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &hap[p]);
    }
    std::vector<bool> vis(n + 1, false); // Visited array
    std::vector<std::vector<long>> g(n + 1); // Adjacency list representation of tree
    for (long p = 1; p < n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      g[x].push_back(y);
      g[y].push_back(x);
    }
    bool possible(true); // Flag to track if solution exists
    dfs(1, g, pop, hap, vis, possible); // Start DFS from root (node 1)
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/