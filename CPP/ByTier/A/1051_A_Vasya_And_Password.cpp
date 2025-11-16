// Problem: CF 1051 A - Vasya And Password
// https://codeforces.com/contest/1051/problem/A

/*
Purpose: This program takes a password string and modifies it to satisfy the security requirements of EatForces,
         which mandates at least one digit, one uppercase letter, and one lowercase letter. The modification is
         done by replacing a substring with another of the same length, minimizing the change.

Algorithms/Techniques: 
    - Single pass through the string to count occurrences of required character types.
    - Conditional logic to determine which characters to insert based on what's missing.
    - Efficient handling of edge cases where specific character types are missing.

Time Complexity: O(n) where n is the length of the input string s. We iterate through the string once to classify characters.
Space Complexity: O(1) - Only a fixed number of variables are used regardless of input size.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cap(0), sml(0), num(0);        // Counters for uppercase, lowercase, and digits
    long xc(0), xs(0), xn(0);           // Last positions of uppercase, lowercase, and digits
    for (long p = 0; p < s.size(); p++) {
      if ('A' <= s[p] && s[p] <= 'Z') {      // Check for uppercase letter
        ++cap;
        xc = p;
      } else if ('a' <= s[p] && s[p] <= 'z') { // Check for lowercase letter
        ++sml;
        xs = p;
      } else if ('0' <= s[p] && s[p] <= '9') { // Check for digit
        ++num;
        xn = p;
      }
    }
    // If two types are missing, we must add both; we simply replace first two characters
    if (cap == 0 && sml == 0) {
      s[0] = 'A';    // Replace first char with uppercase
      s[1] = 'a';    // Replace second char with lowercase
    } else if (cap == 0 && num == 0) {
      s[0] = 'A';    // Replace first char with uppercase
      s[1] = '0';    // Replace second char with digit
    } else if (sml == 0 && num == 0) {
      s[0] = '0';    // Replace first char with digit
      s[1] = 'a';    // Replace second char with lowercase
    } else if (cap == 0) {
      // If only uppercase missing, replace one of last seen digits or lowercase
      s[num > 1 ? xn : xs] = 'A';
    } else if (sml == 0) {
      // If only lowercase missing, replace one of last seen digits or uppercase
      s[num > 1 ? xn : xc] = 'a';
    } else if (num == 0) {
      // If only digit missing, replace one of last seen lowercase or uppercase
      s[sml > 1 ? xs : xc] = '0';
    }
    std::cout << s << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/