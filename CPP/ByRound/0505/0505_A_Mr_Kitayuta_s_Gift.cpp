// Problem: CF 505 A - Mr. Kitayuta's Gift
// https://codeforces.com/contest/505/problem/A

/*
 * Problem: Mr. Kitayuta's Gift
 * 
 * Approach:
 * - Try inserting each of the 26 lowercase letters at every possible position (0 to s.size()) in the string.
 * - For each insertion, check if the resulting string is a palindrome.
 * - Return the first valid palindrome found.
 * 
 * Time Complexity: O(n * 26 * n) = O(n^2) where n is the length of the input string.
 *                    - Outer loop (insertion position): O(n)
 *                    - Inner loop (letter choice): O(26) = O(1)
 *                    - Palindrome check: O(n)
 * Space Complexity: O(n) for the temporary string used for checking.
 * 
 * Algorithms/Techniques:
 * - Brute-force enumeration of all possible insertions
 * - Palindrome checking using two pointers
 */

#include <iostream>
#include <string>

// Function to check if a string is a palindrome
bool isPalindrome(std::string s) {
  for (int p = 0; p < s.size() / 2; p++) {
    if (s[p] != s[s.size() - 1 - p]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  std::string s;
  getline(std::cin, s); // Read input string
  std::string t;
  
  // Try inserting each letter at every position
  for (int p = 0; p <= s.size(); p++) {
    t = s;
    t.insert(p, "a"); // Insert placeholder 'a' at position p
    t[p] = t[s.size() - p]; // This line seems incorrect or misplaced logic as it overwrites the inserted char
    
    if (isPalindrome(t)) {
      std::cout << t << std::endl;
      return 0;
    }
  }
  
  std::cout << "NA" << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/