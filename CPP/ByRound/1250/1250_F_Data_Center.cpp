// Problem: CF 1250 F - Data Center
// https://codeforces.com/contest/1250/problem/F

/*
 * Problem: F. Data Center
 * Purpose: Find the minimum perimeter of a rectangle with integer side lengths and area n.
 * Algorithm: 
 *   - Iterate through all possible divisors p of n from 1 to sqrt(n)
 *   - For each divisor p, compute the corresponding side length n/p
 *   - Calculate the perimeter 2*(p + n/p) and keep track of the minimum
 * Time Complexity: O(sqrt(n))
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long area(10 * n); // Initialize with a value larger than any possible perimeter
  for (long p = 1; p * p <= n; p++) {
    if (n % p) { // If p is not a divisor of n, skip
      continue;
    }
    long tmp = 2 * (p + n / p); // Calculate perimeter for current pair of sides
    area = (area < tmp) ? area : tmp; // Update minimum perimeter
  }
  printf("%ld\n", area);
  return 0;
}


// https://github.com/VaHiX/codeForces/