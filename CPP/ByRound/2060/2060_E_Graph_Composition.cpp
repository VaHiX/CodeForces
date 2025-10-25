// Problem: CF 2060 E - Graph Composition
// https://codeforces.com/contest/2060/problem/E

/*
 * E. Graph Composition
 *
 * Problem Description:
 * Given two undirected graphs F and G with n vertices each, determine the minimum number of operations
 * required to make F structurally equivalent to G. An operation is either adding or removing an edge in F.
 *
 * Algorithms/Techniques Used:
 * - Union-Find (Disjoint Set Union) for tracking connected components in both graphs
 * - Component counting and comparison to compute necessary changes
 *
 * Time Complexity: O(m1 + m2 + n * α(n)) where α is the inverse Ackermann function
 * Space Complexity: O(n)
 */

#include <stdio.h>
const int N = 2e5 + 5;
int g[N], f[N], a[N], b[N], n, m1, m2;
int hg[N], hf[N];

// Find root of x with path compression for graph g
int findg(int x) {
  if (g[x] == x)
    return x;
  return g[x] = findg(g[x]); // Path compression
}

// Find root of x with path compression for graph f
int findf(int x) {
  if (f[x] == x)
    return x;
  return f[x] = findf(f[x]); // Path compression
}

void sol() {
  scanf("%d%d%d", &n, &m1, &m2);
  for (int i = 1; i <= n; ++i) {
    hg[i] = hf[i] = 0;
    g[i] = f[i] = i;
  }
  int s1 = 0, s2 = 0, s3 = 0;

  // Read edges of graph F
  for (int i = 1; i <= m1; ++i)
    scanf("%d%d", &a[i], &b[i]);

  // Build union-find structure for graph G (connected components)
  for (int i = 1; i <= m2; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[findg(x)] = findg(y); // Union operation
  }

  // Count number of connected components in graph G
  for (int i = 1; i <= n; ++i)
    if (!hg[findg(i)]) {
      hg[findg(i)] = 1;
      ++s3;
    }

  // Build union-find structure for graph F using edges read earlier
  for (int i = 1; i <= m1; ++i) {
    if (findg(a[i]) == findg(b[i]))
      f[findf(a[i])] = findf(b[i]); // Union if already connected in G
    else
      ++s1; // Count edges that need to be removed from F (not in G)
  }

  // Count number of connected components in final graph F after processing
  for (int i = 1; i <= n; ++i)
    if (!hf[findf(i)]) {
      hf[findf(i)] = 1;
      ++s2;
    }

  // Print minimum operations needed: s1 edges to remove + s2 edges to add - s3 common components
  printf("%d\n", s1 + s2 - s3);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
}


// https://github.com/VaHiX/codeForces/