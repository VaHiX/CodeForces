// Problem: CF 1929 A - Sasha and the Beautiful Array
// https://codeforces.com/contest/1929/problem/A

/*
 * Problem: Sasha and the Beautiful Array
 * Algorithm/Techniques: Greedy approach with sorting
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(1) - only using a few variables
 *
 * The beauty of an array is defined as the sum of (a[i] - a[i-1]) for i from 2 to n.
 * To maximize this value, we want to place the smallest element at the start and
 * the largest element at the end. This ensures maximum difference in the final sum.
 * So, after sorting the array, the answer is simply the difference between the
 * maximum and minimum elements.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7), mx(0); // Initialize min and max values
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      mn = (mn < x) ? mn : x; // Update minimum
      mx = (mx > x) ? mx : x; // Update maximum
    }
    printf("%ld\n", mx - mn); // Print difference between max and min
  }
}


// https://github.com/VaHiX/codeForces/