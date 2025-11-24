// Problem: CF 2086 C - Disappearing Permutation
// https://codeforces.com/contest/2086/problem/C

/*
C. Disappearing Permutation
Algorithm: Cycle Detection and Counting
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This problem uses the concept of cycles in permutations. For each query,
we simulate removing an element (setting it to 0) and then determine how many
operations are needed to restore a valid permutation. This is done by finding
the number of disjoint cycles formed after removal, which directly corresponds
to the minimum number of operations needed.

The key insight is that in a permutation, elements form cycles. When we remove
elements (set them to 0), we break these cycles and must "fill" the gaps with
missing numbers from 1 to n. Each cycle that remains after removing elements contributes
to the total number of operations required.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> f(n + 1), g(n); // f maps values to their positions, g stores query indices
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &f[p]); // Read the permutation into f
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &g[p]); // Read the order of removals into g
    }
    std::vector<bool> v(n + 1, 0); // Visited array to track processed elements in current iteration
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long x = g[p]; // Current index being removed
      while (!v[x]) { // Traverse the cycle starting at x
        ++cnt;
        v[x] = true;
        x = f[x]; // Move to next element in the cycle (based on permutation)
      }
      printf("%ld ", cnt); // Print number of cycles formed so far
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/