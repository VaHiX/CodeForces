// Problem: CF 1547 E - Air Conditioners
// https://codeforces.com/contest/1547/problem/E

/*
E. Air Conditioners

Algorithm: 
- For each cell i, we compute the minimum temperature as min_{1 <= j <= k}(t_j + |a_j - i|)
- We use a two-pass approach with dynamic programming to efficiently calculate this:
  1. Initialize f[i] = t_j if position a_j = i+1 (0-indexed)
  2. First pass: f[i] = min(f[i], f[i-1] + 1)
  3. Second pass: f[i] = min(f[i], f[i+1] + 1)

Time Complexity: O(n + k) per test case
Space Complexity: O(n) for the array f

Input:
- q test cases
- For each case: n (length), k (number of air conditioners)
- Positions a_1, ..., a_k (1-based indexing)
- Temperatures t_1, ..., t_k

Output:
- n temperatures, one per cell in the strip
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(k), w(k), f(n, 2e9 + 7); // v = positions, w = temperatures, f = result array
    for (long p = 0; p < k; p++) {
      scanf("%ld", &v[p]);
    }
    for (long p = 0; p < k; p++) {
      scanf("%ld", &w[p]);
    }
    for (long p = 0; p < k; p++) {
      f[v[p] - 1] = w[p]; // Set initial temperature at position v[p]-1
    }
    for (long p = 1; p < n; p++) {
      f[p] = std::min(f[p], f[p - 1] + 1); // Forward pass: propagate left distances
    }
    for (long p = n - 2; p >= 0; p--) {
      f[p] = std::min(f[p], f[p + 1] + 1); // Backward pass: propagate right distances
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", f[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/