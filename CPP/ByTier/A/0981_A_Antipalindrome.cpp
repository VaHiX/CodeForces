// Problem: CF 981 A - Antipalindrome
// https://codeforces.com/contest/981/problem/A

/*
 * Problem: Antipalindrome
 * 
 * Purpose: Find the length of the longest substring of the input string that is not a palindrome.
 *          If all substrings are palindromes, output 0.
 * 
 * Algorithms/Techniques:
 * - Check if the entire string is made of the same character (allSame function)
 * - Check if the entire string is a palindrome (isPalindrome function)
 * - Use greedy logic to determine the maximum non-palindrome substring length
 * 
 * Time Complexity: O(n^2) where n is the length of the string.
 *                  - Checking allSame: O(n)
 *                  - Checking isPalindrome: O(n)
 *                  - The loop over all substrings in the worst case is O(n^2), but we only need to check full string
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 */

#include <iostream>
#include <string>

// Function to check if a string is a palindrome
bool isPalindrome(std::string s) {
  for (long p = 0; 2 * p <= s.size(); p++) { // Loop until the middle of the string
    if (s[p] != s[s.size() - 1 - p]) {       // Compare characters from both ends
      return false;                          // If any pair doesn't match, it's not a palindrome
    }
  }
  return true; // If all pairs matched, it's a palindrome
}

// Function to check if all characters in a string are the same
bool allSame(std::string s) {
  for (long p = 1; p < s.size(); p++) {        // Start from the second character
    if (s[p] != s[0]) {                        // If any character differs from the first
      return false;                            // Not all characters are the same
    }
  }
  return true; // All characters are the same
}

int main() {
  std::string s;
  std::cin >> s; // Read the input string

  // If all characters in the string are the same, then all substrings are palindromes
  if (allSame(s)) {
    std::cout << "0" << std::endl;
  } 
  // If the entire string is a palindrome but not all characters are the same
  else if (isPalindrome(s)) {
    // The longest non-palindrome substring will be the full string minus one character
    std::cout << (s.size() - 1) << std::endl;
  } 
  // If the entire string is not a palindrome
  else {
    // The entire string is the longest non-palindrome substring
    std::cout << s.size() << std::endl;
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/