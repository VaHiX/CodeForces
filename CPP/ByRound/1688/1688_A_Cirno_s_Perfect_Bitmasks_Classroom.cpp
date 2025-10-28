// Problem: CF 1688 A - Cirno's Perfect Bitmasks Classroom
// https://codeforces.com/contest/1688/problem/A

/*
 * A. Cirno's Perfect Bitmasks Classroom
 *
 * Problem Description:
 * Given a positive integer x, find the minimum positive integer y such that:
 *   1. x & y > 0 (bitwise AND is greater than 0)
 *   2. x ^ y > 0 (bitwise XOR is greater than 0)
 *
 * Algorithm:
 * - If x == 1, return 3 (since 1 & 3 = 1 and 1 ^ 3 = 2).
 * - If x is odd, return 1 (since x & 1 = 1 and x ^ 1 > 0 for odd x).
 * - If x is even:
 *   - Find the highest power of 2 that divides x.
 *   - Let res be this power of 2. Then, y = res + (x/res == 1? 1 : 0)
 *     This ensures both conditions are satisfied with minimal y.
 *
 * Time Complexity: O(log x) per test case due to factorizing out powers of 2.
 * Space Complexity: O(1), constant space used.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    if (x == 1) {
      puts("3");
    } else if (x % 2) { // x is odd
      puts("1");
    } else {
      long res(1); // Initialize result as 1 (power of 2)
      while (x % 2 == 0) { // Extract all factors of 2 from x
        x /= 2;
        res *= 2;
      }
      printf("%ld\n", res + (x == 1)); // Add 1 if remaining x is 1
    }
  }
}


// https://github.com/VaHiX/codeForces/