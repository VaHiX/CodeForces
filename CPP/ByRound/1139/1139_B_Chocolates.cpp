// Problem: CF 1139 B - Chocolates
// https://codeforces.com/contest/1139/problem/B

#include <cstdio>
#include <vector>
// Problem: B. Chocolates
// Purpose: To maximize the number of chocolates bought under constraints that
//          for each type i, if we buy x_i chocolates, then for all j < i,
//          either x_j = 0 or x_j < x_i.
//
// Algorithm: Greedy approach from right to left. 
//            We process chocolates from highest type to lowest, 
//            and for each type, we take the minimum of available chocolates and 
//            (maximum allowed value - 1), ensuring the sequence remains decreasing.
//
// Time Complexity: O(n)
// Space Complexity: O(n)

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read the number of chocolates available for each type
  }
  long mx(1e9 + 11); // Initialize max allowed chocolates to a large value
  long long total(0); // Total chocolates bought
  for (long p = n - 1; p >= 0; p--) {
    if (mx <= 1) {
      break; // Early termination if no more valid chocolates can be taken
    }
    if (a[p] >= mx) {
      a[p] = mx - 1; // Adjust current type to ensure decreasing sequence
    }
    total += a[p]; // Add to total
    mx = a[p]; // Update max allowed for next iteration
  }
  printf("%lld\n", total);
  return 0;
}

// https://github.com/VaHiX/codeForces/