// Problem: CF 1985 A - Creating Words
// https://codeforces.com/contest/1985/problem/A

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string x, y;
    std::cin >> x >> y;
    char c = x[0];           // Store first character of string x
    x[0] = y[0];             // Replace first character of x with first character of y
    y[0] = c;                // Replace first character of y with stored first character of x
    std::cout << x << " " << y << std::endl;
  }
}
/*
Problem: A. Creating Words
Purpose: Swap the first characters of two 3-character strings and output the results.
Algorithms/Techniques: String manipulation, character swapping using temporary variable
Time Complexity: O(1) - Constant time operations for each test case (strings are always length 3)
Space Complexity: O(1) - Fixed space usage regardless of input size
*/

// https://github.com/VaHiX/codeForces/