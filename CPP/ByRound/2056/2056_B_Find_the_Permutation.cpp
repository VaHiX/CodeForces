// Problem: CF 2056 B - Find the Permutation
// https://codeforces.com/contest/2056/problem/B

/*
B. Find the Permutation
Problem Description:
Given an undirected graph encoded with a permutation p of size n, where an edge exists between vertices p_i and p_j if and only if p_i < p_j, reconstruct the permutation p.

Algorithms/Techniques:
- Graph interpretation and inverse mapping
- For each vertex i in the input string (which represents the adjacency matrix), we compute how many elements to its left (in original order) are smaller than it.
- The result index for p[i] is determined by how many such elements exist, allowing us to recover the original permutation.

Time Complexity: O(n^2)
Space Complexity: O(n)

*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t; // number of test cases
  std::cin >> t;
  while (t--) {
    long n; // size of permutation
    std::cin >> n;
    std::vector<long> v(n); // vector to store the resulting permutation
    
    for (long p = 0; p < n; p++) {
      std::string s; // read adjacency row for vertex p+1
      std::cin >> s;
      
      long dist(0); // count of vertices that are smaller and appear before this one in original sequence
      
      // For each character in the string (representing edges)
      for (long u = 0; u < s.size(); u++) {
        // If current position is '1' and u < p, it means vertex p+1 connects to a previous vertex with smaller label
        dist += (s[u] == '0') * (u < p) + (s[u] == '1') * (u > p);
      }
      
      // Place the value at correct position in reverse order based on how many smaller elements are before it
      v[n - 1 - dist] = p + 1;
    }
    
    // Output the reconstructed permutation
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/