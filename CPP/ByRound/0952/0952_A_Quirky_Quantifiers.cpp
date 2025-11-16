// Problem: CF 952 A - Quirky Quantifiers
// https://codeforces.com/contest/952/problem/A

/*
 * Problem: A. Quirky Quantifiers
 * Algorithm: Simple modulo operation to check if number is odd or even
 * Time Complexity: O(1) - constant time operation
 * Space Complexity: O(1) - constant space usage
 * 
 * The problem asks to output 1 if the input number is odd, 0 if even.
 * This is efficiently solved using modulo operator: 
 * - If a % 2 == 0, number is even → output 0
 * - If a % 2 == 1, number is odd → output 1
 */

#include <cstdio>
int main() {
  long a;                    // Declare variable to store input
  scanf("%ld", &a);          // Read integer from stdin
  printf("%ld\n", a % 2);    // Output remainder when divided by 2 (0 for even, 1 for odd)
  return 0;                  // Return success code
}


// https://github.com/VaHiX/CodeForces/