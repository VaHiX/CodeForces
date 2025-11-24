// Problem: CF 486 A - Calculating Function
// https://codeforces.com/contest/486/problem/A

/*
 * Code Purpose: Calculate the function f(n) = -1 + 2 - 3 + 4 - ... + (-1)^n * n
 * 
 * Algorithm: Mathematical pattern recognition
 * - For odd n: f(n) = -(n+1)/2
 * - For even n: f(n) = n/2
 * 
 * Time Complexity: O(1) - constant time operation
 * Space Complexity: O(1) - constant space usage
 * 
 * Techniques: Observing mathematical patterns and using modular arithmetic
 */

#include <cstdio>
int main() {
  long long n;
  scanf("%lld\n", &n);
  printf("%lld\n", (n % 2) ? (-n / 2 - 1) : (n / 2));  // If n is odd, use formula for odd case; otherwise use even case
  return 0;
}


// https://github.com/VaHiX/CodeForces/