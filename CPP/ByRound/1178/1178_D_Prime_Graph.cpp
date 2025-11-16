// Problem: CF 1178 D - Prime Graph
// https://codeforces.com/contest/1178/problem/D

/*
 * Problem: Prime Graph
 * Purpose: Construct a simple undirected graph with n vertices such that:
 *          - Each vertex has a prime degree
 *          - The total number of edges is prime
 *          - The graph can be disconnected
 *
 * Algorithm:
 * 1. Start by creating a star-like structure with vertex 1 connected to vertex n, and a path from 1 to n-1.
 * 2. Add edges in a way that maintains prime degrees and total number of edges.
 * 3. Use a prime-checking function to determine if the number of edges is prime (break when it is).
 *
 * Time Complexity: O(n * sqrt(n)) due to prime checking and loop iteration up to n
 * Space Complexity: O(n) for storing the edges
 */

#include <cstdio>
#include <vector>
#include <utility>

// Function to check if a number is prime
bool isPrime(long x) {
  for (long p = 2; p * p <= x; p++) {
    if (x % p == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> g;
  
  // Add an edge between vertex 1 and vertex n
  g.push_back(std::make_pair(1, n));
  
  // Add edges forming a path from 1 to n-1
  for (long p = 1; p < n; p++) {
    g.push_back(std::make_pair(p, p + 1));
  }
  
  // Add additional edges to adjust degrees to be prime
  for (long p = 1; 2 * p <= n; p++) {
    if (isPrime(g.size())) {
      break; // If current number of edges is prime, stop adding more
    }
    g.push_back(std::make_pair(p, p + n / 2));
  }
  
  // Output result: number of edges followed by each edge
  printf("%ld\n", g.size());
  for (long p = 0; p < g.size(); p++) {
    printf("%ld %ld\n", g[p].first, g[p].second);
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/