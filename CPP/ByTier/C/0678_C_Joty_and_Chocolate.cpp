// Problem: CF 678 C - Joty and Chocolate
// https://codeforces.com/contest/678/problem/C

/*
C. Joty and Chocolate
Purpose: Calculate the maximum number of chocolates Joty can get by optimally painting tiles.
Algorithm: Inclusion-Exclusion Principle with GCD for LCM calculation.
Time Complexity: O(log(min(a, b))) due to GCD computation.
Space Complexity: O(1) - only a few variables used.

Input:
n - number of tiles
a, b - divisors for red and blue paint
p, q - chocolates per red and blue tile

Output:
Maximum chocolates achievable.
*/

#include <stdint.h>
#include <iostream>

int64_t gcd(int64_t a, int64_t b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  int64_t n, a, b, p, q;
  std::cin >> n >> a >> b >> p >> q;
  int64_t lcm = a * b / gcd(a, b); // Compute LCM using GCD
  // Apply inclusion-exclusion principle:
  // Count red tiles (n / a), blue tiles (n / b),
  // Subtract double-counted tiles (n / lcm) to avoid overcounting
  int64_t total = p * (n / a) + q * (n / b) - ((p < q ? p : q) * (n / lcm));
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/