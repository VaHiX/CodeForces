// Problem: CF 1811 C - Restore the Array
// https://codeforces.com/contest/1811/problem/C

/*
 * Problem: Restore the Array
 * 
 * Purpose: Given an array b where each element b[i] is the maximum of two adjacent elements in array a,
 *          reconstruct any possible array a that could have generated b.
 * 
 * Algorithm:
 *   - The first element of array a is equal to the first element of array b.
 *   - For subsequent elements, we can set a[i] = min(b[i-1], b[i]) for i > 0.
 *   - The last element of a is equal to the last element of b.
 * 
 * Time Complexity: O(n) per test case, as we iterate through the array once.
 * Space Complexity: O(n) for storing the array b and the reconstructed array a.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> b(n - 1);
    for (long p = 0; p < n - 1; p++) {
      scanf("%ld", &b[p]);
    }
    printf("%ld ", b[0]); // First element of a is b[0]
    for (long p = 1; p < n - 1; p++) {
      // For middle elements, set a[p] = min(b[p-1], b[p])
      printf("%ld ", b[p - 1] < b[p] ? b[p - 1] : b[p]);
    }
    printf("%ld\n", b.back()); // Last element of a is b[n-2]
  }
}


// https://github.com/VaHiX/CodeForces/