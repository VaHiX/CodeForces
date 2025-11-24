// Problem: CF 1828 B - Permutation Swap
// https://codeforces.com/contest/1828/problem/B

/*
B. Permutation Swap
Algorithms/Techniques: GCD, Math

Time Complexity: O(n log n) per test case, where n is the size of the permutation.
Space Complexity: O(1), as we only use a constant amount of extra space.

The problem asks to find the maximum possible value of k such that we can sort
a permutation using swaps between elements at positions i and j where i - j = k.
This is equivalent to finding the GCD of all position differences (i - p[i]) 
between the current element and its target position. The maximum valid k will be this GCD.

*/

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long g(0); // Initialize GCD of differences to 0
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      long diff = p - x; // Calculate difference between current position and target position
      diff = (diff > 0) ? diff : -diff; // Take absolute value of difference
      g = gcd(g, diff); // Update GCD with the new difference
    }
    printf("%ld\n", g); // Output the maximum valid k
  }
}


// https://github.com/VaHiX/codeForces/