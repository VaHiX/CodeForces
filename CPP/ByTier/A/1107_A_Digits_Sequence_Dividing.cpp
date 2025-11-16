// Problem: CF 1107 A - Digits Sequence Dividing
// https://codeforces.com/contest/1107/problem/A

/*
 * Problem: Digits Sequence Dividing
 * 
 * Approach:
 * The key idea is to find a way to split the digit string into at least two parts such that each part, when interpreted as an integer,
 * is strictly greater than the previous one.
 * 
 * Strategy:
 * - If the string has length 1, it's impossible to split into at least two parts → NO
 * - If the string has length 2, check if s[0] < s[1]. If not, return NO.
 * - Otherwise, we can always split the string into 2 parts:
 *   - First part: single digit s[0]
 *   - Second part: substring from s[1] to end
 * 
 * This works because even if the first digit is greater than or equal to the second digit,
 * we can still potentially find a valid split with more than two numbers.
 * 
 * However, for the current implementation, it only considers splitting into exactly two parts,
 * so it may not be suitable for all cases. A more robust solution would involve trying different splits.
 * But given the constraints and this greedy approach suffices for the problem as stated.
 * 
 * Time Complexity: O(n) where n is the length of the string (due to string operations)
 * Space Complexity: O(n) for storing the string and intermediate substrings
 * 
 * Techniques: Greedy, String manipulation
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  while (n--) {
    long len;
    std::cin >> len;
    std::string s;
    std::cin >> s;
    if (s.size() <= 1) {
      // Cannot split into at least 2 parts
      std::cout << "NO\n";
    }
    if (s.size() <= 2 && s[0] >= s[1]) {
      // If the first two digits are not in increasing order, no valid split
      std::cout << "NO\n";
    } else {
      // Split into two parts: first digit and the rest
      std::cout << "YES\n2\n" << s[0] << " " << s.substr(1) << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/