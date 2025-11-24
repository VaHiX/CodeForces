// Problem: CF 1291 A - Even But Not Even
// https://codeforces.com/contest/1291/problem/A

/*
Purpose: This code solves the problem of making a number "ebne" (even but not even) by deleting some digits.
An ebne number has a digit sum divisible by 2, but the number itself is not divisible by 2.
The algorithm:
1. Calculate the count of odd digits in the input string.
2. If there are less than 2 odd digits, it's impossible to make an ebne number -> output -1.
3. Otherwise, find the rightmost odd digit that can be excluded so that:
   - The remaining number's digit sum is still even.
   - The resulting number is not divisible by 2 (i.e., ends with an odd digit).
4. Output the number formed by taking all digits up to and including this selected odd digit.

Algorithm:
- Time Complexity: O(n) where n is the length of the input string.
- Space Complexity: O(1) for extra variables (excluding input storage).

Techniques used:
- Greedy approach to select the rightmost odd digit to exclude.
- Digit parity checking using modulo 2.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0);
    // Count the number of odd digits in the string
    for (long p = 0; p < s.size(); p++) {
      cnt += ((s[p] - '0') % 2);
    }
    // If there are less than 2 odd digits, impossible to form ebne number
    if (cnt < 2) {
      std::cout << "-1" << std::endl;
      continue;
    }
    long pos(n - 1);
    // cnt % 2 gives us the parity of the sum of all digits.
    // If it's even, we want to remove one odd digit to make it odd (so that sum is even).
    // If it's odd, we want to remove one odd digit to make it even.
    cnt %= 2;
    // Traverse from right to left to find the rightmost odd digit to keep
    for (long p = s.size() - 1; p >= 0; p--) {
      if ((s[p] - '0') % 2 == 0) {
        // Skip even digits
        continue;
      }
      // If we have already removed one odd digit (cnt == 1), we stop
      if (cnt) {
        cnt = 0;
      } else {
        // Mark the position of the last odd digit we'll keep
        pos = p;
        break;
      }
    }
    // Print the resulting number including all digits up to pos
    for (long p = 0; p <= pos; p++) {
      std::cout << s[p];
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/