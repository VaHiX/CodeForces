// Problem: CF 1952 I - Dark Matter
// https://codeforces.com/contest/1952/problem/I

#include <stdlib.h>
#include <iostream>

/*
 * Code Purpose: This program reads two integers and an operator from standard input,
 * then performs a complex arithmetic calculation involving the inputs.
 * 
 * Algorithms/Techniques: Simple arithmetic evaluation with input parsing
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - constant space usage
 */
int main() {
  long long a, b;        // Declare two long long integers to store the numbers
  char x;                // Declare a character to store the operator
  std::cin >> a >> x >> b;  // Read first number, operator, then second number from input
  // Perform complex arithmetic calculation:
  // (a + b) + ((a * a + b * b) + (a - b) + abs(a) * 2 * b - (a * b + 2))
  std::cout << (a + b +
                ((a * a + b * b) + (a - b) + abs(a) * 2 * b - (a * b + 2)))
            << std::endl;
}

// https://github.com/VaHiX/codeForces/