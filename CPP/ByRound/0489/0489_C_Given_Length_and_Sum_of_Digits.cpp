// Problem: CF 489 C - Given Length and Sum of Digits...
// https://codeforces.com/contest/489/problem/C

/*
 * Problem: Find the smallest and largest m-digit numbers with digit sum s.
 * 
 * Algorithm:
 * - For minimum number: Greedily place the smallest valid digit at each position,
 *   ensuring that the remaining positions can still form a valid number.
 * - For maximum number: Greedily place the largest valid digit at each position.
 * 
 * Time Complexity: O(m * 10) = O(m), since we iterate over digits 0-9 for each of the m positions.
 * Space Complexity: O(m), for storing the resulting strings.
 */

#include <cstdio>
#include <iostream>
#include <string>

// Check if a sum s is possible for a number with m digits
bool possible(int m, int s) { 
    return (s >= 0) && (s <= 9 * m); 
}

int main() {
  int m, s;
  scanf("%d %d", &m, &s);
  std::string min(""), max("");
  int sum = s;
  
  // If sum is 0 but number has more than 1 digit, no valid number exists
  // If sum exceeds maximum possible sum (9 * m), no valid number exists
  if ((s <= 0 && m > 1) || (s > 9 * m)) {
    puts("-1 -1");
    return 0;
  }
  
  // Build the minimum number
  for (int pos = 0; pos < m; pos++) {
    for (int digit = 0; digit <= 9; digit++) {
      // For first digit, we allow 0 only if it's the only digit (m == 1)
      // For other digits, we avoid leading zeros
      // Check if placing 'digit' at this position leads to a valid remaining sum
      if ((pos > 0 || digit > 0 || (m == 1 && digit == 0)) &&
          possible(m - pos - 1, sum - digit)) {
        min += ('0' + digit);
        sum -= digit;
        break;
      }
    }
  }
  
  sum = s;
  // Build the maximum number
  for (int pos = 0; pos < m; pos++) {
    for (int digit = 9; digit >= 0; digit--) {
      // Check if placing 'digit' at this position leads to a valid remaining sum
      if (possible(m - pos - 1, sum - digit)) {
        max += ('0' + digit);
        sum -= digit;
        break;
      }
    }
  }
  
  std::cout << min << " " << max << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/