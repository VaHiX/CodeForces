// Problem: CF 1210 A - Anadi and Domino
// https://codeforces.com/contest/1210/problem/A

/*
A. Anadi and Domino
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Anadi has a set of dominoes. Every domino has two parts, and each part contains some dots. For every a and b such that 1 <= a <= b <= 6, there is exactly one domino with a dots on one half and b dots on the other half. The set contains exactly 21 dominoes.

Anadi has an undirected graph without self-loops and multiple edges. He wants to choose some dominoes and place them on the edges of this graph. He can use at most one domino of each type. Each edge can fit at most one domino.

When placing a domino on an edge, he also chooses its direction. In other words, one half of any placed domino must be directed toward one of the endpoints of the edge and the other half must be directed toward the other endpoint. There's a catch: if there are multiple halves of dominoes directed toward the same vertex, each of these halves must contain the same number of dots.

Task: Find the maximum number of dominoes which can be placed on the edges of the graph.

Algorithm:
- For small graphs (n <= 6), we directly output m since all edges can be covered by dominoes.
- For larger graphs, for each pair of vertices (i,j), consider that they form a "domino triangle" - how many edges connect vertices that both have edges to i and j.
- We compute the minimum such "intersection count" over all pairs of vertices.
- The answer is total edges minus this minimum intersection.

Time complexity: O(1) per test case, since n <= 7 and we do at most 7*7 * 7 operations.
Space complexity: O(1), as we use a fixed-size adjacency matrix of 10x10.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int g[10][10]; // Adjacency matrix to represent the graph
int main() {
  int n, m, a, b; 
  cin >> n >> m;
  if (n <= 6) { // If number of vertices is small enough that all edges can be covered
    cout << m << endl;
    return 0;
  }
  for (int i = 0; i < m; i++)
    cin >> a >> b, g[a][b] = g[b][a] = 1; // Read edges and build adjacency matrix
  
  int mn = 1e9; // Initialize minimum with large value
  for (int i = 1; i <= 7; i++) // Loop through all possible vertex pairs (limited to 7 due to constraints)
    for (int j = 1; j <= 7; j++) {
      int x = 0; // Count of edges connected to both i and j
      for (int k = 1; k <= 7; k++) // Check all vertices k
        if (g[i][k] && g[k][j]) // If there is an edge from i to k and from k to j
          x++; // Increment the count of triangles involving i,j,k
      mn = min(mn, x); // Keep track of minimum count
    }
  cout << m - mn; // Output the maximum number of dominoes that can be placed (total edges minus the minimum intersection)
}


// https://github.com/VaHiX/codeForces/