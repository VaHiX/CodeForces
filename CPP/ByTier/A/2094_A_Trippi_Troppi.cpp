// Problem: CF 2094 A - Trippi Troppi
// https://codeforces.com/contest/2094/problem/A

#include <iostream>
#include <string>

/*
Trippi Troppi
Algorithm: String manipulation
Time Complexity: O(t * n) where t is the number of test cases and n is the average string length (max 10)
Space Complexity: O(1) - only using fixed extra space regardless of input size

The code reads multiple test cases, each containing three strings.
For each test case, it outputs the concatenation of the first character of each string.
*/

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization between C and C++ standard streams for faster input/output
  long t; // Variable to store number of test cases
  std::cin >> t; // Read number of test cases
  while (t--) { // Loop through each test case
    std::string a, b, c; // Declare three strings to store the ancient country name components
    std::cin >> a >> b >> c; // Read the three strings
    std::cout << a[0] << b[0] << c[0] << std::endl; // Output first character of each string concatenated together
  }
}

// https://github.com/VaHiX/codeForces/