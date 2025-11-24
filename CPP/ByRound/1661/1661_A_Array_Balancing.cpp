// Problem: CF 1661 A - Array Balancing
// https://codeforces.com/contest/1661/problem/A

/*
 * Problem: Array Balancing
 * 
 * Algorithms/Techniques: Greedy algorithm with pairwise comparison
 * 
 * Time Complexity: O(n) per test case, where n is the length of arrays
 * Space Complexity: O(n) due to storage of arrays a and b
 *
 * Description:
 * Given two arrays a and b, we can swap elements at the same indices between arrays.
 * The goal is to minimize the sum of absolute differences between consecutive elements
 * in both arrays.
 *
 * Approach:
 * For each adjacent pair (i-1, i), we evaluate all possible combinations of assigning
 * a[i-1] and a[i] from either array a or b. We compute two potential costs for each
 * edge: one where both values come from same array (a[i-1], a[i]) or (b[i-1], b[i]),
 * and another where elements are mixed (a[i-1], b[i]) and (b[i-1], a[i]). For each such pair,
 * we select the minimum cost to accumulate in the result total.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long long res(0);
    for (long p = 1; p < n; p++) {
      // Compute cost of keeping a[i-1], a[i] from array a
      long x = a[p] - a[p - 1];
      if (x < 0) {
        x = -x;
      }
      long y = b[p] - b[p - 1];
      if (y < 0) {
        y = -y;
      }
      long z = x + y;

      // Compute cost of swapping elements between arrays
      x = a[p] - b[p - 1];
      if (x < 0) {
        x = -x;
      }
      y = b[p] - a[p - 1];
      if (y < 0) {
        y = -y;
      }
      long w = x + y;

      // Add minimum of the two costs to result
      res += (z < w) ? z : w;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/