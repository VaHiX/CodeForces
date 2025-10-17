// Problem: CF 1742 D - Coprime
// https://codeforces.com/contest/1742/problem/D

/*
D. Coprime
Algorithm: Precompute all coprime pairs up to 1000, then for each test case find maximum index sum of coprime elements.

Time Complexity: O(B^2 + n) where B = 1001
Space Complexity: O(B^2)

This solution precomputes all pairs (p, q) such that gcd(p, q) == 1 and stores them in a adjacency list m.
For each query, we use the precomputed list to find maximum index sum of coprime elements.

*/
#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long B = 1001;
  std::vector<std::vector<long>> m(B); // Precompute coprime pairs
  for (long p = 1; p < B; p++) {
    for (long q = 1; q < B; q++) {
      if (gcd(p, q) > 1) { // Skip non-coprime pairs
        continue;
      }
      m[p].push_back(q);   // Store q as neighbor of p
      m[q].push_back(p);   // Store p as neighbor of q
    }
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> where(B, -1); // Maps value to its index+1 (1-based)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      where[x] = p + 1; // Store the position of element x
    }
    long res(-1); // Result to store maximum index sum
    for (long p = 1; p < B; p++) {
      if (where[p] < 0) { // If value p does not exist in current array
        continue;
      }
      for (long u = 0; u < m[p].size(); u++) {
        long q = m[p][u]; // Get coprime value q to p
        if (where[q] < 0) { // If value q does not exist in current array
          continue;
        }
        long sum = where[p] + where[q]; // Sum of positions
        res = (res > sum ? res : sum);  // Update maximum sum
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/