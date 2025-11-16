// Problem: CF 909 A - Generate Login
// https://codeforces.com/contest/909/problem/A

/*
 * Code purpose: Generate the alphabetically earliest possible login 
 *               by combining a prefix of the first name and a prefix 
 *               of the last name.
 * 
 * Algorithm: 
 *   - Start with the first character of the first name.
 *   - Extend the first name prefix as long as the next character 
 *     is lexicographically smaller than the first character of the last name.
 *   - Append the first character of the last name.
 * 
 * Time Complexity: O(n + m), where n is the length of the first name 
 *                    and m is the length of the last name. In worst case, 
 *                    we scan the entire first name.
 * Space Complexity: O(n + m), to store the resulting login string.
 */

#include <iostream>
#include <string>

int main() {
  std::string fn, ln;
  std::cin >> fn >> ln;
  std::string login(""); // Initialize empty login string
  login += fn[0];        // Start with first character of first name
  for (int p = 1; p < fn.size(); p++) {  // Iterate through the rest of first name
    if (fn[p] < ln[0]) {                 // If current char < first char of last name
      login += fn[p];                    // Add it to login
    } else {
      break;                             // Stop if we find a character >= first char of last name
    }
  }
  login += ln[0];        // Append first character of last name
  std::cout << login << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/