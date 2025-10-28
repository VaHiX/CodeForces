// Problem: CF 1249 B2 - Books Exchange (hard version)
// https://codeforces.com/contest/1249/problem/B2

/*
B2. Books Exchange (hard version)
Algorithm: Find the cycle length for each node in a permutation.
Time Complexity: O(n) amortized per query, where n is the number of kids.
Space Complexity: O(n) per query.

The problem models a permutation where each kid passes their book to another kid.
We need to find how many days it takes for each kid's book to return to them.

This is essentially finding the length of cycles in a permutation graph.
For each unvisited node, we traverse the cycle it belongs to,
and assign the cycle length to all nodes in that cycle.

Key techniques:
- Cycle detection in permutations
- Union-find like approach with visited tracking
- Preprocessing each cycle once and reusing the result

*/
#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1, 0); // Store the permutation p
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]); // Read permutation
    }
    std::vector<bool> b(n + 1, 0); // Visited array to track processed nodes
    std::vector<long> dur(n + 1, 0); // Duration array to store cycle length for each node
    for (long p = 1; p <= n; p++) {
      if (b[p]) {
        continue; // Skip already processed nodes
      }
      std::vector<long> cycle; // Store all nodes in the current cycle
      long cur(p); // Start traversal from node p
      while (!b[cur]) {
        b[cur] = 1; // Mark current node as visited
        cycle.push_back(cur); // Add to the cycle
        cur = a[cur]; // Move to next node in the permutation
      }
      for (long k = 0; k < cycle.size(); k++) {
        dur[cycle[k]] = cycle.size(); // Assign the cycle length to all nodes in this cycle
      }
    }
    for (long p = 1; p <= n; p++) {
      printf("%ld ", dur[p]); // Output the result
    }
    puts(""); // New line after each query
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/