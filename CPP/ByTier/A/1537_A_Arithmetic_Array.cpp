// Problem: CF 1537 A - Arithmetic Array
// https://codeforces.com/contest/1537/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0); // sum of elements in the array
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // accumulate the sum
    }
    // if sum >= n, we can make it good by adding 0s or other non-negatives
    // else we need to add enough elements to balance the mean to 1
    printf("%ld\n", (s >= n) ? (s - n) : 1);
  }
}

/*
 * Problem: A. Arithmetic Array
 *
 * Purpose:
 *   Given an array of integers, determine the minimum number of non-negative
 *   integers to append so that the arithmetic mean of the resulting array equals 1.
 *
 * Algorithm:
 *   For each test case, calculate the sum of the given array elements.
 *   If the sum is greater than or equal to the array length (n), then we can
 *   simply add zeros to maintain a mean of 1. Otherwise, we must add enough
 *   non-negative values to make the mean exactly 1.
 *
 * Time Complexity: O(n) per test case, where n is the size of the input array.
 * Space Complexity: O(1), as we only use a few variables regardless of input size.
 */

// https://github.com/VaHiX/codeForces/