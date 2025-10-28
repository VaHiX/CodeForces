// Problem: CF 1181 B - Split a Number
// https://codeforces.com/contest/1181/problem/B

/*
B. Split a Number
time limit per test
2 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output
Dima worked all day and wrote down on a long paper strip his favorite number n consisting of l digits. Unfortunately, the strip turned out to be so long that it didn't fit in the Dima's bookshelf.
To solve the issue, Dima decided to split the strip into two non-empty parts so that each of them contains a 
positive
 integer without leading zeros. After that he will compute the sum of the two integers and write it down on a new strip.
Dima wants the resulting integer to be as small as possible, because it increases the chances that the sum will fit it in the bookshelf. Help Dima decide what is the minimum sum he can obtain.

Algorithms/Techniques:
- String manipulation for number splitting
- Custom addition of large numbers represented as strings
- Greedy approach to find minimal sum by checking split positions

Time Complexity: O(l^2) where l is the length of the input string. 
  - For each possible split position, we perform a string addition which takes O(l) time.
  - There are up to O(l) split positions to check.

Space Complexity: O(l) for storing strings and intermediate results during computation.
*/

#include <iostream>
#include <string>

// Function to add two numbers represented as strings
std::string stringsum(std::string a, std::string b) {
  std::string res(""); // Result string initialized empty
  int carry(0); // Carry variable for addition
  for (long p = 0; p < a.size() || p < b.size() || carry; p++) {
    // Get digit from end of a, or '0' if out of bounds
    long x = p < a.size() ? a[a.size() - 1 - p] : '0';
    // Get digit from end of b, or '0' if out of bounds  
    long y = p < b.size() ? b[b.size() - 1 - p] : '0';
    // Compute sum of digits plus carry
    long z = carry + x + y - 2 * '0';
    if (z > 9) {
      carry = 1; // Set carry for next digit
      z -= 10;
    } else {
      carry = 0; // No carry
    }
    char digit = '0' + z; // Convert back to char
    res = digit + res; // Prepend to result string
  }
  return res; // Return sum as string
}

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long l; // Length of number string
  std::cin >> l;
  std::string s; // Input number as string
  std::cin >> s;
  std::string ans = s; // Initialize answer with original number

  // Check splits from middle towards right side
  for (long p = (s.size() + 1) / 2; p < s.size(); p++) {
    if (s[p] == '0') {
      continue; // Skip if current digit is zero (no valid split)
    }
    std::string tmp = stringsum(s.substr(0, p), s.substr(p)); // Compute sum
    if ((tmp.size() < ans.size()) || (tmp.size() == ans.size() && tmp < ans)) {
      ans = tmp; // Update answer if smaller
    }
    break; // Break after first valid split (since we're looking for minimum)
  }

  // Check splits from middle towards left side
  for (long p = (s.size() - 1) / 2; p > 0; p--) {
    if (s[p] == '0') {
      continue; // Skip if current digit is zero (no valid split)
    }
    std::string tmp = stringsum(s.substr(0, p), s.substr(p)); // Compute sum
    if ((tmp.size() < ans.size()) || (tmp.size() == ans.size() && tmp < ans)) {
      ans = tmp; // Update answer if smaller
    }
    break; // Break after first valid split
  }

  std::cout << ans << std::endl; // Output minimal sum
  return 0;
}


// https://github.com/VaHiX/codeForces/