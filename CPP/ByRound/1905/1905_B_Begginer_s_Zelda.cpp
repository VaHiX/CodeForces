// Problem: CF 1905 B - Begginer's Zelda
// https://codeforces.com/contest/1905/problem/B

/*
B. Begginer's Zelda
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given a tree with n vertices, determine the minimum number of "Zelda operations" required to reduce the tree to a single vertex.
A Zelda operation selects two vertices u and v, compresses all vertices on the path from u to v into one new vertex, and reroutes edges accordingly.

Algorithms/Techniques:
- Tree degree analysis
- Greedy approach based on leaf nodes

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n), for storing the degree of each vertex.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf(" %ld", &n);
    std::vector<long> d(n + 1, 0); // Degree array to count edges for each vertex
    for (long p = 1; p < n; p++) { // Read all edges and update degrees
      long x, y;
      scanf("%ld %ld", &x, &y);
      ++d[x];
      ++d[y];
    }
    long leafcnt(0); // Count number of leaves (vertices with degree 1)
    for (long p = 1; p <= n; p++) {
      leafcnt += (d[p] == 1); // Increment if vertex is a leaf
    }
    printf("%ld\n", (leafcnt + 1) / 2); // Minimum operations = ceil(leaf_count / 2)
  }
}


// https://github.com/VaHiX/codeForces/