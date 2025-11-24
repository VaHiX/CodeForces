// Problem: CF 765 D - Artsem and Saunders
// https://codeforces.com/contest/765/problem/D

#include <cstdio>
#include <vector>
/*
 * Problem: Artsem and Saunders
 * 
 * Given a function f: [n] -> [n], we need to find functions g: [n] -> [m] and h: [m] -> [n]
 * such that:
 *   g(h(x)) = x for all x in [n]
 *   h(g(x)) = f(x) for all x in [n]
 * 
 * This is essentially decomposing f into a composition of two functions where:
 *   - h is a surjection from [m] to [n]
 *   - g is an injection from [n] to [m]
 * 
 * Key insight:
 *   - Since g(h(x)) = x, h is injective and g is surjective
 *   - The structure is such that we're essentially finding a permutation-like decomposition
 *   - We build a directed graph where each node points to f[i]. Then, we identify strongly
 *     connected components (or cycles), and for each cycle, we assign a unique index.
 * 
 * Algorithm:
 *   1. Identify points that are fixed points (f[i] == i), assign them unique indices in h.
 *   2. For non-fixed points, trace the chain to see if all elements point to a previously
 *      identified fixed point.
 *   3. If any chain does not lead to a fixed point, it's impossible to decompose.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> f(n + 1, 0), g(n + 1, 0), h(n + 1, 0), vis(n + 1, 0);
  long m(0); // size of the range of g and domain of h, i.e., m

  // First pass: find fixed points and assign them to h
  for (int p = 1; p <= n; p++) {
    scanf("%ld", &f[p]);
    if (f[p] == p) { // if p is a fixed point
      h[++m] = p;   // add p to h
      g[p] = m;     // g[p] maps to the position of p in h
      vis[p] = true; // mark p as visited
    }
  }

  bool possible(true);
  // Second pass: try to assign g values for non-fixed points
  for (int p = 1; p <= n; p++) {
    if (!vis[p]) { // if p is not a fixed point
      if (!vis[f[p]]) { // if f[p] is not visited, we can't determine g[p]
        possible = 0;
        break;
      } else
        g[p] = g[f[p]]; // g[p] will be same as g[f[p]]
    }
  }

  if (!possible) {
    puts("-1");
  } else {
    printf("%ld\n", m);
    for (int p = 1; p <= n; p++) {
      printf("%ld ", g[p]);
    };
    puts("");
    for (int p = 1; p <= m; p++) {
      printf("%ld ", h[p]);
    };
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/