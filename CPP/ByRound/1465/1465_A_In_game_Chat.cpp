// Problem: CF 1465 A - In-game Chat
// https://codeforces.com/contest/1465/problem/A

/*
 * Problem: In-game Chat Bad Message Filter
 * Algorithm: Count trailing closing parentheses and compare with remaining characters.
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) additional space (excluding input storage).
 *
 * The solution counts how many ')' characters appear at the end of the string,
 * then compares this count to the number of non-')' characters in the string.
 * If the count of trailing ')' is strictly greater than the number of other
 * characters, the message is considered bad.
 */

#include <iostream>
#include <string>
int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio for faster input/output
  std::cin.tie(0);                       // Untie cin from cout for faster input
  long t;
  std::cin >> t;                         // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n;                       // Read length of the string
    std::string s;
    std::cin >> s;                       // Read the string
    long cnt(0);                         // Counter for trailing ')' characters
    for (long p = s.size() - 1; p >= 0; p--) {  // Iterate from end to start of string
      if (s[p] == ')') {                 // If character is ')'
        ++cnt;                           // Increment counter
      } else {
        break;                           // Stop when a non-')' character is encountered
      }
    }
    std::cout << ((cnt > n - cnt) ? "Yes" : "No") << std::endl;  // Output result based on comparison
  }
}


// https://github.com/VaHiX/codeForces/