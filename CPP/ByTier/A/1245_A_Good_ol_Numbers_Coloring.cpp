// Problem: CF 1245 A - Good ol' Numbers Coloring
// https://codeforces.com/contest/1245/problem/A

/*
 * Problem: Determine if the number of nonnegative integers colored black is infinite.
 * Algorithm: This problem is based on the concept of greatest common divisor (GCD).
 *            A number i is colored white if it can be expressed as a linear combination of a and b, 
 *            i.e., i = x*a + y*b for some non-negative integers x and y.
 *            By Bézout's identity, such combinations cover all multiples of gcd(a, b).
 *            If gcd(a, b) == 1, then every sufficiently large integer can be represented as a combination,
 *            meaning only finite numbers will remain black.
 *            Otherwise, if gcd(a, b) > 1, there are infinitely many integers that cannot be represented
 *            using multiples of a and b — hence infinite black numbers.
 * 
 * Time Complexity: O(log(min(a, b))) per test case due to GCD computation.
 * Space Complexity: O(1), constant space usage.
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); } // Compute GCD using Euclidean algorithm
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    puts(gcd(a, b) <= 1 ? "Finite" : "Infinite"); // If GCD is 1, finite; else infinite
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/