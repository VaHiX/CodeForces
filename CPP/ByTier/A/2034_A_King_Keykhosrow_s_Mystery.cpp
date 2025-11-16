// Problem: CF 2034 A - King Keykhosrow's Mystery
// https://codeforces.com/contest/2034/problem/A

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", (a * b) / gcd(a, b)); // LCM calculation using GCD
  }
}
/*
==================================================
Problem: A. King Keykhosrow's Mystery
Purpose: Find the smallest integer m such that:
1. m >= a or m >= b
2. (m % a) == (m % b)

Algorithm: 
- The solution uses the mathematical property that if two numbers have the same remainder when divided by a and b respectively, then the smallest such number is the LCM (Least Common Multiple) of a and b.
- LCM(a, b) = (a * b) / GCD(a, b)

Time Complexity: O(log(min(a, b))) per test case due to GCD calculation
Space Complexity: O(log(min(a, b))) for recursive GCD calls

==================================================
*/

// https://github.com/VaHiX/codeForces/