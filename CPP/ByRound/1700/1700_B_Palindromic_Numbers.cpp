// Problem: CF 1700 B - Palindromic Numbers 
// https://codeforces.com/contest/1700/problem/B

/*
 * Problem: Find a positive number of the same length as the given number such that their sum is a palindrome.
 * 
 * Algorithm/Techniques:
 * - For each test case, we construct a number such that when added to the input,
 *   the result is a palindrome.
 * - Case 1: If the first digit of input is not '9', we simply take the complement of each digit
 *   (i.e., 9 - digit) to form the second number.
 * - Case 2: If the first digit is '9', we need to perform subtraction with borrowing,
 *   similar to how you would subtract numbers manually from right to left.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the number.
 * Space Complexity: O(n) for storing the result string.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long len;
    std::cin >> len;
    std::string s;
    std::cin >> s;
    std::string t(s.size(), '_'); // Initialize result string with same size as input
    
    if (s[0] != '9') {
      // Simple case: take complement of each digit
      for (long p = 0; p < s.size(); p++) {
        t[p] = '0' + ('9' - s[p]); // Complement digit (e.g., '9'-'5' = 4)
      }
    } else {
      // Complex case: handle borrowing when first digit is '9'
      int carry(0);
      for (long p = s.size() - 1; p >= 0; p--) {
        int a = 1 - carry;         // We want to subtract from 1 (for borrowing)
        int b = s[p] - '0';        // Current digit
        int diff = a - b;          // Difference
        if (diff < 0) {
          carry = 1;
          diff += 10;              // Borrow from next digit
        } else {
          carry = 0;
        }
        t[p] = (char)(diff + '0'); // Convert back to character
      }
    }
    std::cout << t << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/