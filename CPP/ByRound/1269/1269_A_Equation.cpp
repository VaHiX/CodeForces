// Problem: CF 1269 A - Equation
// https://codeforces.com/contest/1269/problem/A

/*
Purpose: Find two composite numbers a and b such that a - b = n
Algorithm: 
- If n is odd, set b = 9 (composite) and a = n + 9
- If n is even, set b = 4 (composite) and a = n + 4
- Since 9 and 4 are both composite numbers, and adding an even number to 9/4 maintains the composite property for large enough n,
  this approach works for all valid inputs.

Time Complexity: O(1) - constant time operation
Space Complexity: O(1) - constant space usage

The key insight is that 4 and 9 are the smallest composite numbers, and using them as base values 
guarantees that both a and b will be composite for any valid n.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long b = (n % 2) ? 9 : 4;  // If n is odd, use 9; if even, use 4 (both are composite)
  printf("%ld %ld\n", n + b, b);  // Print a = n + b and b
  return 0;
}


// https://github.com/VaHiX/CodeForces/