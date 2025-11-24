// Problem: CF 450 B - Jzzhu and Sequences
// https://codeforces.com/contest/450/problem/B

/*
 * Code Purpose: Computes the nth term of a sequence defined by the recurrence relation:
 * f(n) = f(n-1) + f(n-2), where f(1) = x and f(2) = y.
 * The sequence has a periodic pattern with period 6, which allows efficient computation
 * even for very large values of n (up to 2*10^9).
 *
 * Algorithms/Techniques: Modular arithmetic, periodicity detection in recurrence relations
 *
 * Time Complexity: O(1) - constant time due to periodic pattern
 * Space Complexity: O(1) - only a few variables used
 */

#include <cstdio>
int main() {
  long x, y;
  scanf("%ld %ld\n", &x, &y);
  long n(0);
  scanf("%ld", &n);
  long output(0);
  // Use periodicity of 6 to determine the value based on n mod 6
  if (n % 6 == 0) {
    output = x - y;
  } else if (n % 6 == 1) {
    output = x;
  } else if (n % 6 == 2) {
    output = y;
  } else if (n % 6 == 3) {
    output = y - x;
  } else if (n % 6 == 4) {
    output = -x;
  } else if (n % 6 == 5) {
    output = -y;
  }
  const long M = 1000000007;
  // Ensure output is positive before taking modulo
  if (output < 0) {
    output += 2 * M;
  }
  printf("%ld\n", output % M);
  return 0;
}


// https://github.com/VaHiX/CodeForces/