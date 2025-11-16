// Problem: CF 1065 B - Vasya and Isolated Vertices
// https://codeforces.com/contest/1065/problem/B

/*
B. Vasya and Isolated Vertices
Algorithm: Calculate minimum and maximum number of isolated vertices in an undirected graph with n vertices and m edges.
Approach:
- For minimum isolated vertices:
  - If we have enough edges to connect all but at most one vertex, then min = 0.
  - Otherwise, we need (n - 2*m) isolated vertices to "use up" remaining edges efficiently by connecting them in pairs.

- For maximum isolated vertices:
  - We want to minimize the number of connected components to maximize isolated ones.
  - Use binary search or direct calculation to find smallest u such that u*(u-1)/2 >= m.
  - Then max = n - u.

Time Complexity: O(log n)
Space Complexity: O(1)

Input:
Two integers n and m (1 <= n <= 10^5, 0 <= m <= n*(n-1)/2).
Guaranteed to exist a valid graph.

Output:
Minimum and maximum possible number of isolated vertices.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  
  // Calculate minimum number of isolated vertices
  ll mn = (2 * m >= n) ? 0 : (n - 2 * m);  // If enough edges to connect all vertices, min=0; else distribute remaining edges optimally

  ll u(0);
  // Find smallest u such that u*(u-1)/2 >= m
  while (u * (u - 1) / 2 < m) {
    ++u;
  }
  
  // Maximum isolated vertices = total vertices - vertices used in a complete graph with "u" nodes
  ll mx = n - u;
  
  printf("%lld %lld\n", mn, mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/