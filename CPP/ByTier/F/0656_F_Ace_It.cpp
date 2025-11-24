// Problem: CF 656 F - Ace It!
// https://codeforces.com/contest/656/problem/F

/*
 * Code Purpose: This program processes a 7-character string input starting with 'A' followed by 6 digits.
 *               It calculates a checksum by summing the digits (with special handling for '0') and adds 1.
 *               The result is the final output.
 *
 * Algorithms/Techniques: String parsing, character-to-digit conversion, conditional logic
 *
 * Time Complexity: O(n) where n is the length of the input string (constant 7 in this case)
 * Space Complexity: O(1) - only using a fixed amount of extra space regardless of input size
 */

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  int count = 1;  // Initialize count to 1 as per the problem logic
  for (int p = 1; p < s.size(); p++) {  // Start from index 1 to skip the 'A' character
    count += (s[p] == '0') ? 9 : (s[p] - '0');  // If digit is '0', add 9, otherwise add the digit value
  }
  std::cout << count << std::endl;
}


// https://github.com/VaHiX/CodeForces/