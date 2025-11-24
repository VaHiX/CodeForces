// Problem: CF 1925 B - A Balanced Problemset?
// https://codeforces.com/contest/1925/problem/B

/*
B. A Balanced Problemset?
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithm: 
The goal is to maximize the GCD of n positive integers that sum up to x.
Key insight:
If we want to maximize the GCD, then each number in the set must be a multiple of that GCD.
Let g be the desired GCD. Then:
1. Each element in the set is at least g
2. Total sum = x ≥ n * g (since there are n elements)
3. So we can try all possible values of g from 1 to x/n and check if it's valid.

However, there is a more efficient way using divisors:
- The maximum GCD g such that x is divisible by g and x/g >= n.
- Why? because we have to split x into exactly n parts, so at least n * g <= x.
- We can iterate through all divisors of x up to sqrt(x), for each divisor p,
  check that either p or x/p (the corresponding pair) is >= n and contributes to max possible GCD.

Time Complexity: O(sqrt(x) * t) where t is number of test cases, and x up to 1e8.
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, n;
    scanf("%ld %ld", &x, &n);
    long ans(1);
    for (long p = 1; p * p <= x; p++) {
      if (x % p) {
        continue;
      }
      long q = (x / p);
      // Check if p can be a valid candidate for GCD
      if (q >= n) {
        ans = (ans > p) ? ans : p;
      }
      // Check if q can be a valid candidate for GCD
      if (p >= n) {
        ans = (ans > q) ? ans : q;
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/