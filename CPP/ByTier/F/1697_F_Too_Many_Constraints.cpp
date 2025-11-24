// Problem: CF 1697 F - Too Many Constraints
// https://codeforces.com/contest/1697/problem/F

/*
 * Problem: F. Too Many Constraints
 *
 * Purpose: This code solves a constrained array building problem where we need
 * to construct a non-decreasing array of integers from 1 to k, satisfying
 * various constraints. The constraints can be:
 *              1. a[i] != x
 *              2. a[i] + a[j] <= x
 *              3. a[i] + a[j] >= x
 *
 * Approach:
 * - We model this as a 2-SAT problem where each element a[i] can take value
 * from 1 to k.
 * - For each element, we create 2*k+2 variables to represent if a[i] is at
 * least (val+1) or at most val (with special handling for boundary values).
 * - We enforce the non-decreasing property through edges between consecutive
 * variables.
 * - All constraints are converted into clauses of the 2-SAT problem.
 * - We use Tarjan's algorithm for detecting a valid assignment in 2-SAT.
 *
 * Time Complexity: O(n*k + m*k)
 * Space Complexity: O(n*k)
 */

#include <algorithm>
#include <stdio.h>
#include <vector>

#define N 500010
using namespace std;

// Fast input reader
inline int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < 48) {
    if (c == '-')
      f = 0;
    c = getchar();
  }
  while (c >= 48)
    x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
  return f ? x : -x;
}

int n, m, k, tot, idx, top, cnt;
int s[N], low[N], dfn[N], in[N], bel[N];
vector<int> g[N];

// Initialize data structures for Tarjan's algorithm
void init() {
  idx = top = cnt = 0;
  for (int i = 0; i < tot; i++)
    g[i].clear(), dfn[i] = 0, s[i] = -1;
}

// Tarjan's algorithm for SCC detection
void dfs(int u) {
  in[u] = 1;
  s[++top] = u;
  low[u] = dfn[u] = ++idx;
  for (auto v : g[u]) {
    if (!dfn[v])
      dfs(v);
    if (in[v])
      low[u] = min(low[u], low[v]);
  }
  if (low[u] == dfn[u]) {
    cnt++;
    while (s[top + 1] != u) {
      bel[s[top]] = cnt;
      in[s[top--]] = 0;
    }
  }
}

// Run Tarjan's algorithm on all unvisited nodes
void tarjan() {
  for (int i = 0; i < tot; i++)
    if (!dfn[i])
      dfs(i);
}

// Convert coordinates to variable index for 2-SAT
int id(int x, int val, int c) { return 2 * (val * n + x - 1) + c; }

// Add implication edge (u => v)
void link(int u, int v) {
  g[u ^ 1].push_back(v); // Add reverse edge for implication (u => v)
  g[v ^ 1].push_back(u); // Add reverse edge for implication (v => u)
}

// Solve a single testcase
void solve() {
  n = read();
  m = read();
  k = read();
  tot = n * (k + 2) * 2; // Total number of variables
  init();                // Reset all variables

  // Build basic 2-SAT clauses for non-decreasing array constraints
  for (int i = 1; i <= n; i++) {
    // Set bounds for the value of a[i]: [1, k]
    // If x = 1, then a[i] >= 1 (always true as values are 1 to k)
    link(id(i, 1, 1), id(i, 1, 1));
    link(id(i, k + 1, 0), id(i, k + 1, 0));

    // Link consecutive values so that a[i] = j implies a[i] >= j and a[i] <= j
    for (int j = 1; j <= k; j++)
      link(id(i, j, 1), id(i, j + 1, 0));

    // Link non-decreasing property: If a[i] <= j then a[i+1] >= j
    if (i < n)
      for (int j = 1; j <= k + 1; j++)
        link(id(i, j, 0), id(i + 1, j, 1));
  }

  // Process all given constraints
  while (m--) {
    int op = read();
    if (op == 1) {
      // Constraint 1: a[i] != x
      int i = read(), x = read();
      link(id(i, x, 0),
           id(i, x + 1, 1)); // Make sure a[i] != x by ensuring x is impossible
    } else if (op == 2) {
      // Constraint 2: a[i] + a[j] <= x
      int i = read(), j = read(), x = read();
      for (int y = 1; y <= k + 1; y++)
        if (x - y + 1 >= 1 && x - y + 1 <= k + 1) {
          link(id(i, y, 0), id(j, x - y + 1,
                               0)); // Imply that a[i] >= y => a[j] >= x - y + 1
        }
    } else {
      // Constraint 3: a[i] + a[j] >= x
      int i = read(), j = read(), x = read();
      for (int y = 1; y <= k + 1; y++)
        if (x - y + 1 >= 1 && x - y + 1 <= k + 1) {
          link(id(i, y, 1), id(j, x - y + 1,
                               1)); // Imply that a[i] <= y => a[j] <= x - y + 1
        }
    }
  }

  tarjan(); // Run Tarjan's algorithm to find strongly connected components

  // Check for contradiction in 2-SAT
  for (int i = 0; i < tot; i++)
    if (bel[i] == bel[i ^ 1]) {
      printf("-1\n");
      return;
    }

  // Assign values based on SCCs
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= k + 1; j++)
      if (bel[id(i, j, 0)] < bel[id(i, j, 1)]) {
        printf("%d ", j - 1); // Adjust for 1-based indexing
        break;
      }
  printf("\n");
}

signed main() {
  int T = read();
  while (T--)
    solve();
  return 0;
}

// https://github.com/VaHiX/CodeForces/