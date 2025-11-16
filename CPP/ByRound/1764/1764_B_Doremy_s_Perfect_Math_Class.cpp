// Problem: CF 1764 B - Doremy's Perfect Math Class
// https://codeforces.com/contest/1764/problem/B

/*
 * Problem: B. Doremy's Perfect Math Class
 * Purpose: Given a set of positive integers, determine the maximum possible size
 *          of the set after repeatedly adding differences between elements that are not already in the set.
 * Algorithm: 
 *   - Key insight is that the maximum number of elements we can have is determined 
 *     by the GCD of all numbers in the set. All generated numbers will be multiples
 *     of this GCD, and the total count will be the sum of (max_element / gcd) + 1 if zero exists.
 *   - Use Euclidean algorithm to compute GCD.
 * Time Complexity: O(n log(max_element)) per test case due to GCD computation
 * Space Complexity: O(1) extra space, not counting input storage
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long g(0), mx(0);
    bool z(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (!x) {
        z = true;  // Mark if zero is present in the set
      }
      g = gcd(g, x);  // Compute GCD of all elements so far
      mx = (mx > x) ? mx : x;  // Track maximum element
    }
    printf("%ld\n", z + (mx / g));  // Output result: 1 if zero exists, plus max/gcd
  }
}


// https://github.com/VaHiX/codeForces/