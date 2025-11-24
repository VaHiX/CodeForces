// Problem: CF 1255 C - League of Leesins
// https://codeforces.com/contest/1255/problem/C

/*
C. League of Leesins
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Reconstruct a permutation p of size n from n-2 triples q, where each triple consists of 3 elements 
from permutation p that appear consecutively in some order. The goal is to find one valid permutation p 
consistent with the given shuffled triples.

Approach:
1. Model the problem as a graph where each element is a node and each triple contributes edges between nodes.
2. For each triple, we build undirected edges among all 3 elements (as they are consecutive in some order).
3. Count degrees of each node (element) to identify endpoints (nodes with degree 1).
4. Use the structure of the graph to reconstruct the permutation by traversing from a leaf node (degree = 1)
   and going through each triple once, keeping track of visited nodes.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques:
- Graph construction using adjacency list
- Degree counting
- Path traversal based on graph structure
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> v(n + 1); // adjacency list for the graph
  std::vector<long> vis(n + 1, 0), cnt(n + 1, 0); // visited array and degree count
  long x, y, z;
  for (long p = 1; p <= n - 2; p++) {
    scanf("%ld %ld %ld", &x, &y, &z);
    v[x].push_back(y), v[x].push_back(z); // build edges among the three nodes in the triple
    v[y].push_back(x), v[y].push_back(z);
    v[z].push_back(x), v[z].push_back(y);
    cnt[x]++;
    cnt[y]++;
    cnt[z]++;
  }
  for (long p = 1; p <= n; p++) {
    if (cnt[p] == 1) { // find a node with degree 1 (start of the path)
      x = p;
      break;
    }
  }
  if (cnt[v[x][0]] == 2) { // figure out which neighbor is in the middle
    y = v[x][0];
  } else {
    y = v[x][1];
  }
  vis[x] = vis[y] = 1; // mark starting points as visited
  printf("%ld %ld ", x, y);
  for (long p = 1; p <= n - 2; p++) {
    long z;
    for (long q = 0; q < v[x].size(); q++) {
      if (!vis[v[x][q]]) { // find next unvisited neighbor
        z = v[x][q];
      }
    }
    printf("%ld ", z);
    vis[z] = 1;
    x = y; // move sliding window forward
    y = z;
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/