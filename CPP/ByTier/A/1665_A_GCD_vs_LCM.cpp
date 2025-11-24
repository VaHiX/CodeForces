// Problem: CF 1665 A - GCD vs LCM
// https://codeforces.com/contest/1665/problem/A

/*
 * Problem: GCD vs LCM
 * 
 * Algorithm/Technique: Greedy Construction
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * Approach:
 * - We are given a positive integer n and need to find four positive integers a, b, c, d such that:
 *   1. a + b + c + d = n
 *   2. gcd(a, b) = lcm(c, d)
 * 
 * - A simple and effective way to construct such values:
 *   - Set c = 1 and d = 1. Then lcm(c, d) = 1.
 *   - Now, we need gcd(a, b) = 1.
 *   - We can choose a = n - 3, b = 1, c = 1, d = 1.
 *   - This satisfies the sum condition: (n - 3) + 1 + 1 + 1 = n
 *   - And gcd(a, b) = gcd(n - 3, 1) = 1 = lcm(1, 1) = 1
 * 
 * - This strategy works for all n >= 4.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld 1 1 1\n", n - 3);  // Output a = n-3, b = 1, c = 1, d = 1
  }
}


// https://github.com/VaHiX/CodeForces/