// Problem: CF 696 B - Puzzles
// https://codeforces.com/contest/696/problem/B

#include <cstdio>
#include <vector>
// Problem: Expected starting times in a random DFS traversal of a tree.
// Algorithm: 
//   - Build parent and size arrays using bottom-up pass.
//   - Compute expected values using dynamic programming with linearity of expectation.
//   - Time complexity: O(n), Space complexity: O(n)
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> par(n + 1);  // Parent array
  for (long p = 2; p <= n; p++) {
    scanf("%ld", &par[p]);
  }
  std::vector<long> sz(n + 1, 1);  // Size of subtree rooted at each node
  for (long p = n; p > 0; p--) {
    sz[par[p]] += sz[p];  // Compute subtree sizes bottom-up
  }
  std::vector<double> f(n + 1, 1);  // Expected starting time array
  for (long p = 2; p <= n; p++) {
    // Compute expected starting time using the recurrence:
    // f[p] = f[par[p]] + 1 + 0.5 * (sz[par[p]] - 1 - sz[p])
    // This accounts for the random shuffle in DFS and uses linearity of expectation.
    f[p] = f[par[p]] + 1.0 + 0.5 * (sz[par[p]] - 1 - sz[p]);
  }
  for (long p = 1; p <= n; p++) {
    printf("%.1f ", f[p]);  // Output expected starting times
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/