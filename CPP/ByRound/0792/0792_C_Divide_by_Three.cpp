// Problem: CF 792 C - Divide by Three
// https://codeforces.com/contest/792/problem/C

/*
 * Problem: Divide by Three
 * 
 * Purpose: Transform a given number into a "beautiful" number by erasing 
 *          the minimum number of digits. A beautiful number must:
 *          1. Not have leading zeros (except for "0" itself)
 *          2. Be a multiple of 3
 * 
 * Algorithm:
 * 1. First check if the original number is already divisible by 3.
 *    If yes, output the original number.
 * 2. If not, try to remove one digit to make it divisible by 3.
 *    If removing a single digit still leads to leading zeros, 
 *    try removing two digits.
 * 3. The key insight is that a number is divisible by 3 if and only if 
 *    the sum of its digits is divisible by 3.
 * 4. When removing digits:
 *    - To avoid leading zeros, remove from the left side if possible.
 *    - If removal of one digit still results in invalid number,
 *      try removing two digits, ensuring valid result.
 * 
 * Time Complexity: O(n), where n is the length of input string.
 * Space Complexity: O(n), for storing intermediate strings and variables.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  int n(0);
  bool hasZero(false);
  // Calculate the sum of digits modulo 3 and check for presence of zero
  for (int p = 0; p < s.size(); p++) {
    n = 10 * n + (s[p] - '0');
    n %= 3;
    hasZero |= (s[p] == '0');
  }
  // If the number is already divisible by 3, output it
  if (n == 0) {
    std::cout << s << std::endl;
    return 0;
  }
  long posA(-1), posB(-1);
  std::string tA(""), tB("");
  // Search for a digit whose remainder equals n (the deficit to make it divisible by 3)
  for (int p = s.size() - 1; p >= 0; p--) {
    if ((s[p] - '0') % 3 == n) {
      posA = p;
      break;
    }
  }
  // If such digit exists and is not the first (to avoid leading zeros), remove it
  if (posA > 0) {
    for (int p = 0; p < s.size(); p++) {
      if (p == posA) {
        continue;
      };
      std::cout << s[p];
    }
    std::cout << std::endl;
    return 0;
  } else if (posA == 0) {
    // If the first digit is the one to remove, 
    // skip all leading zeros and output the rest
    long ind(1);
    while (s[ind] == '0') {
      ++ind;
    }
    for (int p = ind; p < s.size(); p++) {
      tA += s[p];
    }
    if (tA.size() == 0 && hasZero) {
      tA = "0";
    }
  }
  // Reset variables and look for two digits whose sum modulo 3 equals 3 - n
  posA = posB = -1;
  int nB = 3 - n;
  for (int p = s.size() - 1; p >= 0; p--) {
    if (((s[p] - '0') % 3 == nB) && (posA < 0)) {
      posA = p;
    } else if (((s[p] - '0') % 3 == nB) && (posA > 0)) {
      posB = p;
    }
    if (posA >= 0 && posB >= 0) {
      break;
    }
  }
  // If no valid pair found, impossible to make beautiful
  if ((tA.size() <= 0) && (posA < 0 || posB < 0 || s.size() <= 2)) {
    std::cout << "-1" << std::endl;
    return 0;
  }
  if (posA >= 0 && posB >= 0) {
    // If two valid positions found, remove them
    if (posB > 0) {
      for (int p = 0; p < s.size(); p++) {
        if (p == posA || p == posB) {
          continue;
        };
        tB += s[p];
      }
    } else {
      // Special case for first digit
      long ind(1);
      while (s[ind] == '0') {
        ++ind;
      }
      if (ind == posA) {
        ++ind;
        while (s[ind] == '0') {
          ++ind;
        }
      }
      for (int p = ind; p < s.size(); p++) {
        if (p == posA || p == posB) {
          continue;
        };
        tB += s[p];
      }
    }
    if (tB.size() == 0 && hasZero) {
      tB = "0";
    }
  }
  // Output the better (longer) result
  if (tA.size() <= 0 && tB.size() <= 0) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << ((tA.size() > tB.size()) ? tA : tB) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/