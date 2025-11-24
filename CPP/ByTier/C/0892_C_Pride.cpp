// Problem: CF 892 C - Pride
// https://codeforces.com/contest/892/problem/C

/*
Algorithm: Greedy + GCD
Purpose: Determine the minimum number of operations to make all elements of the array equal to 1.
         Each operation allows replacing one element with GCD of two adjacent elements.
         If it's impossible, return -1.

Time Complexity: O(n^2) - In worst case, we check all pairs for GCD.
Space Complexity: O(n) - For storing the array.

Approach:
1. If there are already 1s in the array, return n - count_of_ones.
2. If the GCD of all elements is greater than 1, it's impossible to make all elements 1, return -1.
3. Otherwise, find the shortest subarray whose GCD becomes 1, then use that to compute the minimal operations.
*/

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  long ones(0), gt(0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    ones += (a[p] == 1); // Count occurrences of 1
    gt = gcd(gt, a[p]);  // Compute GCD of all elements
  }
  long res(2 * n);
  if (ones) {
    // If there are already 1s, just need to turn the rest into 1s
    printf("%ld\n", n - ones);
  } else if (gt > 1) {
    // If GCD of all elements > 1, impossible to make all 1
    puts("-1");
  } else {
    // Find minimum operations by checking subarrays
    for (long p = 0; p < n; p++) {
      long g = a[p];
      for (long q = p + 1; q < n; q++) {
        g = gcd(g, a[q]);
        if (g == 1) {
          // Found a subarray with GCD 1, calculate operations needed
          long cand = (q - p) + (n - 1);
          res = (res < cand) ? res : cand;
          break;
        }
      }
    }
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/