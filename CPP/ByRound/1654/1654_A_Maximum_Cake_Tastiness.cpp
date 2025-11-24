// Problem: CF 1654 A - Maximum Cake Tastiness
// https://codeforces.com/contest/1654/problem/A

/*
 * Problem: A. Maximum Cake Tastiness
 * Algorithm: Find maximum sum of two adjacent elements after reversing at most one subsegment.
 * Time Complexity: O(n) per test case, where n is the number of cake pieces.
 * Space Complexity: O(1), only using a few variables for tracking max values.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mxa(0), mxb(0); // mxa = highest value, mxb = second highest value
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= mxa) { // If current element is greater than or equal to max
        mxb = mxa;    // Shift previous max to second max
        mxa = x;      // Update max
      } else if (x > mxb) { // If current element is greater than second max
        mxb = x;      // Update second max
      }
    }
    printf("%ld\n", mxa + mxb); // Print sum of two largest elements
  }
}


// https://github.com/VaHiX/codeForces/