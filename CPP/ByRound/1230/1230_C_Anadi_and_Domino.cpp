// Problem: CF 1230 C - Anadi and Domino
// https://codeforces.com/contest/1230/problem/C

/*
C. Anadi and Domino
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Anadi has a set of dominoes. Every domino has two parts, and each part contains some dots. For every a and b such that 1 <= a <= b <= 6, there is exactly one domino with a dots on one half and b dots on the other half. The set contains exactly 21 dominoes.

Anadi has an undirected graph without self-loops and multiple edges. He wants to choose some dominoes and place them on the edges of this graph. He can use at most one domino of each type. Each edge can fit at most one domino. It's not necessary to place a domino on each edge of the graph.

When placing a domino on an edge, he also chooses its direction. In other words, one half of any placed domino must be directed toward one of the endpoints of the edge and the other half must be directed toward the other endpoint. There's a catch: if there are multiple halves of dominoes directed toward the same vertex, each of these halves must contain the same number of dots.

The goal is to find the maximum number of dominoes that can be placed on the edges of the graph.

Algorithm:
1. For small graphs (n <= 6), we just output m since each edge can have one domino.
2. For larger graphs:
   - Build adjacency matrix representation of the graph.
   - For every pair of vertices (a, b), count how many vertices have edges to both a and b.
   - This represents how many times we can place a domino with these numbers on its halves.
   - Take the minimum such count across all pairs.
   - Return m minus this minimum (the number of edges that cannot be filled with dominoes).
   
Time Complexity: O(n^3) where n is the number of vertices due to triple nested loops over vertices.
Space Complexity: O(n^2) for storing the adjacency matrix representation of the graph.

*/

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  if (n <= 6) {
    printf("%ld\n", m);
    return 0;
  }
  std::vector<std::vector<long>> g(n, std::vector<long>(n, 0));
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x - 1][y - 1] = g[y - 1][x - 1] = 1; // Mark edges in the adjacency matrix
  }
  long mn(1e9);
  for (long a = 0; a < n; a++) {
    for (long b = 0; b < n; b++) {
      long x(0);
      for (long c = 0; c < n; c++) {
        if (g[c][a] && g[c][b]) { // Check if vertex c connects to both a and b
          ++x;
        }
      }
      mn = (mn < x) ? mn : x; // Update minimum count of common neighbors
    }
  }
  printf("%ld\n", m - mn); // Maximum dominoes is total edges minus minimum conflicts
  return 0;
}


// https://github.com/VaHiX/codeForces/