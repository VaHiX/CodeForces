// Problem: CF 1717 A - Madoka and Strange Thoughts
// https://codeforces.com/contest/1717/problem/A

/*
 * Problem: A. Madoka and Strange Thoughts
 * Purpose: Count pairs (a, b) such that 1 <= a, b <= n and lcm(a,b)/gcd(a,b) <= 3
 *
 * Algorithm: 
 * - Using mathematical identity: lcm(a,b) * gcd(a,b) = a * b
 * - So lcm(a,b)/gcd(a,b) = (a * b) / (gcd(a,b)^2)
 * - The condition becomes: (a * b) / (gcd(a,b)^2) <= 3
 * - Which simplifies to: a * b <= 3 * gcd(a,b)^2
 *
 * Key observations:
 * - If gcd(a, b) = g, then a = g * x and b = g * y for coprime x and y
 * - Substituting and simplifying gives: x * y <= 3
 * - Enumerating all possible coprime pairs (x, y) where x * y <= 3:
 *   - (1,1): contributes count of g such that g*n >= g (i.e., all valid)
 *   - (1,2): contributes count of g such that 2g <= n
 *   - (2,1): same as above
 *   - (1,3): contributes count of g such that 3g <= n
 *   - (3,1): same as above
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long n;
    scanf("%lld", &n);
    // Formula derived from analysis of cases where lcm/gcd <= 3
    printf("%lld\n", n + 2 * (n / 2) + 2 * (n / 3));
  }
}


// https://github.com/VaHiX/codeForces/