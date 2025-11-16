// Problem: CF 1360 D - Buying Shovels
// https://codeforces.com/contest/1360/problem/D

/*
D. Buying Shovels
Algorithm: For each possible package size p (from 1 to k and up to sqrt(n)), check if p divides n.
If it does, then the number of packages needed is n/p. If n/p is <= k, we can use this, otherwise,
we look at p itself as a candidate. Find minimum such candidate.
Time Complexity: O(sqrt(n) * t) where n <= 1e9 and t <= 100
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long res(n); // Initialize result with n (worst case: buy n packages of size 1)
    for (long p = 1; p * p <= n && p <= k; p++) { // Loop up to sqrt(n) and k
      if (n % p) { // If p does not divide n, skip
        continue;
      }
      long cur = (n / p <= k) ? p : (n / p); // Choose the smaller number of packages
      res = (res < cur) ? res : cur; // Update minimum
    }
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/