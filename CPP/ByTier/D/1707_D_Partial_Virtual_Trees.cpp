// Problem: CF 1707 D - Partial Virtual Trees
// https://codeforces.com/contest/1707/problem/D

/*
Code Purpose:
This code solves the problem of counting the number of ways to reduce a set of vertices of a tree to a single root vertex (vertex 1) through a sequence of operations.
Each operation involves choosing a subset of vertices that forms a "partial virtual tree" (a subset where all lowest common ancestors of pairs in the subset are also in the subset) and replacing the current set with this subset.

Algorithms/Techniques:
- Tree Dynamic Programming (DFS)
- Convolution with modular arithmetic
- Combinatorial counting with inclusion-exclusion principle
- Memoization through recurrence relations

Time Complexity: O(n^3)
Space Complexity: O(n^2)

Note: The code heavily uses low-level loops for performance and does not use standard containers or STL in a high-level way, resulting in complex inline code.
*/
#include <iostream>
#include <string>

using namespace std;
using I = long long;
enum { N = 2001 };
basic_string<I> g[N];
I n, p, V[N], f[N][N], r[N], s[N], A[N];
void d(I u, I F) {
  // Recursive DFS to compute subtree information
  for (I v : g[u])
    if (v ^ F)
      d(v, u);
  I e = 0;
  // Collect children of u
  for (I v : g[u])
    if (v ^ F)
      s[e] = 0, V[e++] = v;
  // Compute f[u][i] for all i
  for (I i = 1, l, w = 0, *g = f[u]; i < n; ++i)
    if (e) {
      l = r[e] = 1;
      // Precompute r[j] = product of f[V[j]][i] for j in range [j+1, e)
      for (I j = e; j--;)
        r[j] = r[j + 1] * f[V[j]][i] % p;
      g[i] = w = (w + *r) % p;
      // Update g[i] using convolution
      for (I j = 0, o; j < e; ++j)
        o = f[V[j]][i], s[j] = (s[j] + l * r[j + 1]) % p,
        g[i] = (g[i] + o * s[j] + p - w) % p, l = l * o % p;
    } else
      g[i] = i;
}
int main() {
  cin >> n >> p;
  I i = 0;
  // Build adjacency list
  for (I u, v; ++i < n;)
    cin >> u >> v, A[i] = 1, g[u] += v, g[v] += u;
  // Process each child of root (vertex 1)
  for (I v : g[1])
    for (d(v, 1), i = 0; ++i < n;)
      A[i] = A[i] * f[v][i] % p;
  // Use inclusion-exclusion to derive final answer
  for (i = 0; ++i < n;)
    for (I j = n; j-- > i;)
      A[j] = (A[j] + p - A[j - 1]) % p;
  // Output the answer
  for (i = 0; ++i < n;)
    cout << A[i] << ' ';
}


// https://github.com/VaHiX/CodeForces/