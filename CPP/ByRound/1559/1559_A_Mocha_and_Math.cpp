// Problem: CF 1559 A - Mocha and Math
// https://codeforces.com/contest/1559/problem/A

/*
 * Problem: A. Mocha and Math
 * Purpose: Given a sequence of integers, we can perform operations where for any interval [l, r],
 *          we replace elements at symmetric positions with their bitwise AND. Goal is to minimize
 *          the maximum value in the sequence.
 *
 * Algorithm:
 * - For each test case, compute the bitwise AND of all elements in the array.
 * - This is optimal because every element will eventually be affected by the operation,
 *   and applying AND operations reduces values over time.
 * - The result is simply the AND of all numbers in the array.
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res;
    scanf("%ld", &res); // Read first element into result variable
    for (long p = 1; p < n; p++) { // Loop through remaining elements
      long x;
      scanf("%ld", &x);
      res &= x; // Perform bitwise AND operation with current element
    }
    printf("%ld\n", res); // Output the final result
  }
}


// https://github.com/VaHiX/codeForces/