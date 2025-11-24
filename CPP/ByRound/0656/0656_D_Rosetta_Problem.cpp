// Problem: CF 656 D - Rosetta Problem
// https://codeforces.com/contest/656/problem/D

#include <cstdio>
int main() {
  const long B = 8;  // Base for conversion, octal system
  long a;
  scanf("%ld", &a);  // Read input integer
  int count(0);      // Counter for number of 1s in base-8 representation
  while (a > 0) {
    count += (a % B == 1);  // Increment if last digit is 1
    a /= B;                 // Move to next digit
  }
  printf("%d\n", count);  // Print the result
  return 0;
}
/*
 * Problem: Count the number of 1s in the base-8 (octal) representation of a given integer.
 *
 * Algorithms/Techniques: 
 *   - Base conversion using division and modulus
 *   - Bit manipulation concept applied to base-8
 *
 * Time Complexity: O(log_B(a)) where B = 8, so effectively O(log(a))
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

// https://github.com/VaHiX/codeForces/