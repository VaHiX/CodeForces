// Problem: CF 958 B1 - Maximum Control (easy)
// https://codeforces.com/contest/958/problem/B1

/*
 * Purpose: To determine the number of "remote" planets in a tree-shaped solar system.
 *          A planet is remote if it is connected to the rest of the planets by only one hyperspace tunnel.
 *          This is equivalent to counting the number of leaf nodes in a tree.
 * 
 * Algorithm: 
 *   1. Build a degree count for each node (planet) by reading all edges.
 *   2. Count how many nodes have degree 1 (i.e., exactly one connection).
 * 
 * Time Complexity: O(N), where N is the number of planets. We process each edge once and each node once.
 * Space Complexity: O(N), for storing the degree of each planet.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0);  // Array to store degree of each node (planet), indexed from 1 to N
  for (long p = 1; p < n; p++) {  // Read N-1 edges
    long x, y;
    scanf("%ld %ld", &x, &y);
    ++a[x];  // Increment degree of planet x
    ++a[y];  // Increment degree of planet y
  }
  long cnt(0);
  for (long p = 1; p <= n; p++) {  // Count nodes with degree 1 (remote planets)
    cnt += (a[p] == 1);
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/