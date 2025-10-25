// Problem: CF 1870 B - Friendly Arrays
// https://codeforces.com/contest/1870/problem/B

/*
B. Friendly Arrays
Problem Description:
Given two arrays of integers a and b, we can perform operations where we choose any element from b and apply bitwise OR with all elements in a.
After performing the operations, compute the XOR of all elements in a. The goal is to find the minimum and maximum possible values of this XOR.

Algorithms/Techniques:
- Bit manipulation with XOR and OR operations
- Greedy optimization for minimizing/maximizing result based on parity of n

Time Complexity: O(n + m) per test case, as we iterate through arrays once.
Space Complexity: O(n + m) due to storage of input arrays a and b.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &b[p]);
    }
    long A(0);
    for (long p = 0; p < n; p++) {
      A ^= a[p]; // Compute initial XOR of all elements in a
    }
    if (n % 2) { // If n is odd
      long mx(A);
      for (long p = 0; p < m; p++) {
        mx |= b[p]; // Maximize result by OR-ing with all b values
      }
      printf("%ld %ld\n", A, mx); // Minimum stays A, maximum is mx
    } else { // If n is even
      long mn(A);
      for (long p = 0; p < m; p++) {
        mn &= ~b[p]; // Minimize result by applying NOT operations on b values
      }
      printf("%ld %ld\n", mn, A); // Minimum is mn, maximum stays A
    }
  }
}


// https://github.com/VaHiX/codeForces/