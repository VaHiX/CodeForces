// Problem: CF 630 N - Forecast
// https://codeforces.com/contest/630/problem/N

/*
 * Purpose: Solve a quadratic equation ax^2 + bx + c = 0 and output the two real roots,
 *          with the larger root (optimistic scenario) first, followed by the smaller root (pessimistic scenario).
 *
 * Algorithm: 
 *   - Use the quadratic formula: x = (-b ± sqrt(b^2 - 4ac)) / (2a)
 *   - Compute both roots and ensure the larger one is printed first
 *
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few variables used, no dynamic allocation
 */

#include <cmath>
#include <iostream>

int main() {
  long double a, b, c;
  std::cin >> a >> b >> c;
  
  // Calculate the two roots using the quadratic formula
  long double x1 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a;
  long double x2 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
  
  // Ensure x1 is the larger root and x2 is the smaller root
  if (x1 < x2) {
    long double x = x1;
    x1 = x2;
    x2 = x;
  }
  
  // Set output precision to 15 decimal places to ensure accuracy within 10^-6
  std::cout.precision(15);
  std::cout << std::fixed << x1 << std::endl << std::fixed << x2 << std::endl;
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/