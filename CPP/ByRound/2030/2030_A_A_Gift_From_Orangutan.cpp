// Problem: CF 2030 A - A Gift From Orangutan
// https://codeforces.com/contest/2030/problem/A

/*
 * Problem: A Gift From Orangutan
 * Purpose: Given an array of integers, we need to rearrange it to maximize the sum of 
 *          differences between prefix maximum and prefix minimum across all positions.
 *
 * Algorithm:
 *   - For each test case, compute the maximum possible score by sorting the array in descending order,
 *     then calculate (n - 1) * (max_element - min_element).
 *   - This is because when sorted in descending order, the first element will be max and last will be min,
 *     so the contribution of each index to the final sum depends only on the difference between max and min.
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(1) additional space (not counting input)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1001), mx(0); // Initialize min and max with extreme values
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      mn = (mn < x ? mn : x); // Update minimum
      mx = (mx > x ? mx : x); // Update maximum
    }
    printf("%ld\n", (n - 1) * (mx - mn)); // Output the maximum score possible
  }
}


// https://github.com/VaHiX/codeForces/