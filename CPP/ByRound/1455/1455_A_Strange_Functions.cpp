// Problem: CF 1455 A - Strange Functions
// https://codeforces.com/contest/1455/problem/A

/*
 * Problem: Strange Functions
 * Algorithms/Techniques: Simulation, String manipulation, Mathematical function analysis
 *
 * Time Complexity: O(n) where n is the length of the input string (due to string operations and loop)
 * Space Complexity: O(n) for storing the string representation of the number
 *
 * Description:
 * The problem involves computing a function g(x) = x / f(f(x)) where f(x) reverses the digits of x
 * and removes leading zeros. For each test case, we need to count how many distinct values g(x)
 * can take for all x in [1, n].
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Disable sync with C stdio for faster I/O
  std::cin.tie(0);                        // Untie cin from cout for faster I/O
  long t;
  std::cin >> t;                          // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s;                        // Read the input number as string
    std::cout << (s.size()) << std::endl; // Print the length of the string (this is the answer)
  }
}


// https://github.com/VaHiX/codeForces/