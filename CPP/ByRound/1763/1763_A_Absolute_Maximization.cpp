// Problem: CF 1763 A - Absolute Maximization
// https://codeforces.com/contest/1763/problem/A

/*
 * Problem: Maximum Difference After Swapping Bits
 * 
 * Algorithms/Techniques:
 * - Bit manipulation
 * - Greedy approach to maximize difference between max and min elements
 * 
 * Time Complexity: O(n * log(max_val)) where n is the size of array,
 *                  and max_val is the maximum value in the array (at most 1023).
 *                  In practice, since values are bounded by 1024, this is effectively O(n)
 * 
 * Space Complexity: O(1) - only using fixed-size arrays of size 11 for bit tracking
 * 
 * The approach counts for each bit position whether there exists both a number with
 * that bit set to 1 and another with it set to 0.
 * For each such position, we can create an optimal configuration that maximizes
 * the difference between max and min values in the array.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool a[11] = {0}; // Tracks if there's at least one number having bit 1 at position u
    bool z[11] = {0}; // Tracks if there's at least one number having bit 0 at position u
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      for (long u = 0; u <= 10; u++) { // Loop through up to 11 bits (since max value is 1023)
        if (x % 2) {
          a[u] = 1; // Mark that we have at least one number with bit 1 at position u
        } else if (x % 2 == 0) {
          z[u] = 1; // Mark that we have at least one number with bit 0 at position u
        }
        x /= 2;   // Move to next less significant bit
      }
    }
    long res(0), mult(1);
    for (long u = 0; u <= 10; mult *= 2, u++) {
      res += mult * a[u] * z[u]; // If both bits exist at position u, add value of that bit to result
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/