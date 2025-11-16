// Problem: CF 863 A - Quasi-palindrome
// https://codeforces.com/contest/863/problem/A

/*
 * Problem: Check if a given number is quasi-palindromic.
 * A quasi-palindromic number is one that can be transformed into a palindrome 
 * by adding leading zeros.
 * 
 * Approach:
 * 1. Read the input as a string to handle leading zeros properly.
 * 2. Traverse the string from right to left to remove leading zeros.
 * 3. Store the non-leading-zero part in reverse order in a vector.
 * 4. Check if the vector represents a palindrome.
 * 
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(n), for storing the processed digits in the vector.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  bool start(0); // Flag to indicate if we have encountered a non-zero digit
  std::vector<char> v; // Vector to store the non-leading-zero digits in reverse order
  for (long p = s.size() - 1; p >= 0; p--) {
    start |= (s[p] != '0'); // Set flag to true if a non-zero digit is found
    if (start) {
      v.push_back(s[p]); // Add digit to vector if we've started encountering non-zero digits
    }
  }
  bool palindrome(true); // Assume the string is a palindrome initially
  for (long p = 0; p < v.size() / 2; p++) {
    if (v[p] != v[v.size() - p - 1]) { // Compare characters from both ends
      palindrome = false;
      break;
    }
  }
  std::cout << (palindrome ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/