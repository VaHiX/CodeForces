// Problem: CF 1504 A -  Déjà Vu
// https://codeforces.com/contest/1504/problem/A

/*
 * Problem: A. Déjà Vu
 * 
 * Algorithm/Techniques: 
 * - Check if the string is all 'a's. If so, inserting an 'a' anywhere will result in a palindrome, so output "NO".
 * - Otherwise, we can insert an 'a' at the beginning to avoid creating a palindrome, because the original string is not a palindrome.
 * 
 * Time Complexity: O(n) for each string check, where n is the length of the string.
 * Space Complexity: O(n) for storing the new string after insertion.
 */

#include <iostream>
#include <string>

// Function to check if a string is a palindrome
bool isPalindrome(std::string x) {
  for (long p = 0; 2 * p <= x.size(); p++) {
    if (x[p] != x[x.size() - 1 - p]) {
      return false;
    }
  }
  return true;
}

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool possible(false);
    
    // Check if there's any non-'a' character in the string
    for (long p = 0; p < s.size(); p++) {
      if (s[p] != 'a') {
        possible = true;
        break;
      }
    }
    
    // Initialize result string by appending 'a' at the end
    std::string res = s + 'a';
    
    // If appending at the end still results in a palindrome, try prepending 'a'
    if (isPalindrome(res)) {
      res = 'a' + s;
    }
    
    // If we found a non-'a' character, it's possible to avoid palindrome
    if (possible) {
      std::cout << "YES\n" << res << std::endl;
    } else {
      // All characters are 'a', inserting 'a' anywhere creates a palindrome
      std::cout << "NO" << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/