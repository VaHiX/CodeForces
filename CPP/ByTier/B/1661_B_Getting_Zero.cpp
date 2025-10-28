// Problem: CF 1661 B - Getting Zero
// https://codeforces.com/contest/1661/problem/B

/*
B. Getting Zero
Problem: Given n integers, find the minimum number of operations to make each equal to 0.
Operations:
- Increment by 1 (v = (v + 1) mod 32768)
- Double (v = (2 * v) mod 32768)

Algorithm: Brute force with optimization
For each number x, try all combinations of:
- p increments (0 to B)
- q doublings (0 to B)
Compute final value y = (x + p) * (2^q) and check if y % MOD == 0.
Time Complexity: O(B^2 * n) where B = 15, so effectively O(n)
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  const long B = 15; // Maximum number of doublings to consider
  const long MOD = 32768; // Modulo value (2^15)
  long n;
  scanf("%ld", &n);
  while (n--) {
    long res(100); // Initialize result with a large value
    long x;
    scanf("%ld", &x);
    for (long p = 0; p <= B; p++) { // Try all possible increments
      long y = x + p; // Start with incremented value
      for (long q = 0; q <= B; q++) { // Try all possible doublings
        long steps = p + q; // Total operations
        if (y % MOD == 0) { // If the value is divisible by MOD
          res = (res < steps) ? res : steps; // Update minimum steps
        }
        y *= 2; // Double the value for next iteration
      }
    }
    printf("%ld ", res);
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/