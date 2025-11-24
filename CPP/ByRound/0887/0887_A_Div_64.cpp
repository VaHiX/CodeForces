// Problem: CF 887 A - Div. 64
// https://codeforces.com/contest/887/problem/A

/*
 * Purpose: Determine if a binary string can be transformed into a number divisible by 64
 *          by removing some digits. A number is divisible by 64 if it ends with at least 6 zeros.
 *          
 * Algorithm: 
 * 1. Traverse the string from left to right.
 * 2. Count the number of zeros that appear after the first '1'.
 * 3. If there is at least one '1' and at least 6 zeros after it, then it's possible.
 * 4. The number 64 in binary is "1000000", meaning it must end with exactly 6 zeros.
 *
 * Time Complexity: O(n), where n is the length of input string
 * Space Complexity: O(1), only using a constant amount of extra space
 */

#include <iostream>
#include <string>

int main() {
  const int N = 6;  // Number of trailing zeros required for divisibility by 64
  std::string s;
  std::cin >> s;
  bool isOne(0);  // Flag to check if we've seen a '1'
  int countz(0);  // Count of zeros after the first '1'
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '1') {
      isOne = true;  // Mark that we have seen a '1'
    } else if (s[p] == '0' && isOne) {
      ++countz;  // Count zeros only after the first '1'
    }
  }
  std::cout << ((isOne && (countz >= N)) ? "yes" : "no") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/