// Problem: CF 2008 D - Sakurako's Hobby
// https://codeforces.com/contest/2008/problem/D

/*
D. Sakurako's Hobby

Purpose:
This program calculates for each element in a permutation, how many "black" nodes are reachable from it.
A node is considered reachable if we can get to it by following the permutation links (p[i] -> p[p[i]] -> ...).
The color of each node is given in a binary string (0 = black, 1 = white).
For each index i, F(i) returns the count of black nodes in the cycle that i belongs to.

Algorithms:
- Cycle Detection with DFS traversal through permutation.
- Color tracking using a boolean vector.
- For each unvisited node, we traverse its cycle and compute the number of black nodes.
- Assign the same count to all nodes in that cycle since they share the same reachable set.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing vectors and auxiliary data structures

*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<long> v(n + 1, 0), f(n + 1, 0); // v: permutation array; f: result function F(i)
    std::vector<bool> w(n + 1, 0); // w: visited marker for cycle detection
    for (long p = 1; p <= n; p++) {
      std::cin >> v[p]; // Read the permutation
    }
    std::string s;
    std::cin >> s; // Read color string (0 = black, 1 = white)
    for (long p = 1; p <= n; p++) {
      if (w[p]) {
        continue; // Skip already processed nodes
      }
      std::vector<long> u; // Stores indices in current cycle
      long x(p), cnt(0); // x: current node, cnt: black count in cycle
      while (!w[x]) {
        u.push_back(x); // Add to cycle list
        w[x] = 1; // Mark as visited
        cnt += (s[x - 1] == '0'); // Increment if node is black (s[x-1] because of 1-based indexing)
        x = v[x]; // Move to next node in permutation
      }
      for (long k = 0; k < u.size(); k++) {
        f[u[k]] = cnt; // Assign the total black count to all nodes in this cycle
      }
    }
    for (long p = 1; p <= n; p++) {
      printf("%ld ", f[p]); // Print result for each node
    }
    puts(""); // Newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/