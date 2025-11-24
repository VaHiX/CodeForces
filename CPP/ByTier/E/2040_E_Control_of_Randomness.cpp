// Problem: CF 2040 E - Control of Randomness
// https://codeforces.com/contest/2040/problem/E

/*
E. Control of Randomness
Algorithms/Techniques: Tree DFS traversal, Dynamic Programming on trees, Mathematical expectation calculation with optimized coin usage.

Time Complexity: O(n * q + n^2) per test case due to sorting and traversal.
Space Complexity: O(n^2) for storing tree edges and auxiliary arrays.

This code solves a problem involving a robot moving in a tree toward the root vertex 1, where the number of steps depends on coin usage. The goal is to compute the minimum expected steps using dynamic programming and optimization techniques with modular arithmetic.

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e3 + 10;
int n, q;
vector<int> e[N]; // Adjacency list for the tree
int fa[N], dep[N]; // fa[u] stores parent of u; dep[u] stores depth of u

// DFS to calculate parent and depth of each node
void dfs(int u, int fff) {
  fa[u] = fff;
  dep[u] = dep[fff] + 1;
  for (int v : e[u])
    if (v != fff)
      dfs(v, u);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1, u, v; i < n; ++i) // Read edges
      scanf("%d%d", &u, &v), e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0); // Start DFS from root node 1

    while (q--) {
      int v, p;
      scanf("%d%d", &v, &p);
      if (v == 1)
        puts("0"); // Already at root
      else if (fa[v] == 1)
        puts("1"); // Direct parent of root, one step needed
      else {
        int de = dep[v] - 1; // Distance from v to root
        int res = 0;
        if (de & 1) // If odd distance
          de--, ++res; // Adjust and increment result
        p = min(p, de >> 1); // Limit p by half of depth
        int cnt = de >> 1; // Number of even steps to process

        static int a[N]; // Array storing intermediate nodes
        for (int i = 1, pos = v; i <= cnt; ++i)
          a[i] = fa[pos], pos = fa[fa[pos]]; // Get parents at even steps

        sort(a + 1, a + cnt + 1,
             [&](int aa, int bb) { return e[aa].size() < e[bb].size(); }); // Sort based on degree

        res += p * 2; // Add cost for using coins in optimal way
        for (int i = 1; i <= cnt - p; ++i)
          res += 2 * e[a[i]].size(); // Remaining steps contribute based on degrees
        printf("%d\n", res); // Output result
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/