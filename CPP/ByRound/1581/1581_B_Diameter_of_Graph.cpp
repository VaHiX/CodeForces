// Problem: CF 1581 B - Diameter of Graph
// https://codeforces.com/contest/1581/problem/B

/*
B. Diameter of Graph
Algorithm: Determine if a connected undirected graph with n nodes, m edges, and diameter < k-1 is possible.
Time Complexity: O(1) per test case
Space Complexity: O(1)

Key observations:
- For n=1, only m=0 is valid, and k must be > 1 for diameter < k-1 (i.e., diameter = 0).
- A connected graph with n nodes has at least n-1 edges and at most n*(n-1)/2 edges.
- If m = n*(n-1)/2 (complete graph), then the diameter is at most 2, so k must be > 2.
- Otherwise, the diameter can be made at most 3, so k must be > 3.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    bool ans;
    if (n == 1) {
      // For a single node graph, only m=0 is possible
      // Diameter = 0, so k must be > 1
      ans = (m == 0 && k > 1);
    } else if (m < n - 1 || m > n * (n - 1) / 2) {
      // Check if m is within valid range for a connected graph
      // Minimum edges: n-1 (tree), maximum edges: n*(n-1)/2 (complete graph)
      ans = false;
    } else if (m == (n * (n - 1) / 2)) {
      // If the graph is complete, diameter is at most 2
      // So we need k > 2 to satisfy diameter < k-1
      ans = (k > 2);
    } else {
      // For all other cases, it's possible to construct a graph with diameter <= 3
      // So we need k > 3 to satisfy diameter < k-1
      ans = (k > 3);
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/