// Problem: CF 1834 A - Unit Array
// https://codeforces.com/contest/1834/problem/A

/*
 * Problem: Unit Array
 * Purpose: Determine the minimum number of operations to make an array of -1s and 1s "good".
 *          An array is good if:
 *              1. Sum of elements >= 0
 *              2. Product of elements == 1
 *          
 * Algorithm:
 *   - Count positive and negative (i.e., 1s and -1s) in the array.
 *   - If there are more -1s than 1s, we must convert some -1s to 1s to balance the product.
 *   - To make the product 1, we need an even number of -1s.
 *   - If this is not satisfied, we adjust by converting -1s to 1s until parity is correct.
 *   - Finally, ensure that sum >= 0; if not, convert one more -1 to 1 to fix it.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pos(0), neg(0); // Count of 1s and -1s
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      pos += (x > 0);   // Increment if element is 1
      neg += (x < 0);   // Increment if element is -1
    }
    long move(0);         // Number of operations needed
    if (pos < neg) {
      move = (neg - pos + 1) / 2;  // Minimum moves to make positives >= negatives
      pos += move;
      neg -= move;
    }
    if (neg % 2) {        // If number of -1s is odd, we need one more operation
      ++move;
    }
    printf("%ld\n", move);
  }
}


// https://github.com/VaHiX/codeForces/