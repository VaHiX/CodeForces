// Problem: CF 656 C - Without Text
// https://codeforces.com/contest/656/problem/C

#include <stddef.h>
#include <iostream>
#include <string>

/*
 * Purpose: Calculates a weighted sum of characters in a string where uppercase letters contribute positively 
 * and lowercase letters contribute negatively based on their alphabetical position.
 * 
 * Algorithm: Single pass through the string, checking each character's case and computing its contribution 
 * to the running sum.
 * 
 * Time Complexity: O(n) where n is the length of the input string
 * Space Complexity: O(1) - only using a fixed amount of extra space regardless of input size
 */
int main() {
  std::string s;                    // Declare string to read input
  std::cin >> s;                    // Read input string from standard input
  int sum(0);                       // Initialize sum to zero
  for (size_t p = 0; p < s.size(); p++) {  // Loop through each character in the string
    if ('A' <= s[p] && s[p] <= 'Z') {      // Check if character is uppercase
      sum += (s[p] - 'A' + 1);             // Add position of uppercase letter (A=1, B=2, ...)
    }
    if ('a' <= s[p] && s[p] <= 'z') {      // Check if character is lowercase
      sum -= (s[p] - 'a' + 1);             // Subtract position of lowercase letter (a=1, b=2, ...)
    }
  }
  std::cout << sum << std::endl;     // Output the final calculated sum
  return 0;
}

// https://github.com/VaHiX/codeForces/