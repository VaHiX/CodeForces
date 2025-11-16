// Problem: CF 758 D - Ability To Convert
// https://codeforces.com/contest/758/problem/D

/*
 * Problem: Ability To Convert
 * 
 * Purpose: Given a base n and a number k in that base (represented as a string),
 *          find the minimum decimal number x such that when x is converted to base n,
 *          it results in k.
 * 
 * Algorithm:
 *   - The idea is to reverse the conversion process.
 *   - We process the digits of k from right to left.
 *   - For each position, we attempt to merge digits into a larger number
 *     (up to the base n) to minimize the final result.
 *   - If merging is possible (i.e., sum < n), we continue merging with higher powers.
 *   - When merging is no longer possible, we add the accumulated value to the result
 *     and increment the power of the base.
 *   - The merging approach tries to use the largest possible segment that is less than n.
 * 
 * Time Complexity: O(d) where d is the number of digits in k (at most 60)
 * Space Complexity: O(d) for storing the digits
 */

#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> digits;
  for (size_t p = 0; p < s.size(); p++) {
    digits.push_back(s[p] - '0');  // Convert char to int digit
  }
  int64_t start(digits.size() - 1), ind(digits.size()), current(0), bt(1),
      mult(1), number(0);
  while (ind >= 0) {
    if (ind > 0 && current + bt * digits[ind - 1] < n) {
      // Try to merge the next digit if it doesn't exceed base n
      current += bt * digits[--ind];
      if (bt <= 1e17) {
        bt *= 10;  // Increase the base for decimal place values
      }
    } else {
      // Cannot merge anymore, finalize current segment
      while (digits[ind] == 0 && ind < start) {
        ++ind;  // Skip leading zeros
      }
      bt = 1;  // Reset base multiplier
      number += mult * current;  // Add the accumulated value to result
      current = 0;
      mult *= n;  // Increase power of base
      start = ind - 1;
      if (ind <= 0) {
        break;  // Finished processing all digits
      }
    }
  }
  std::cout << number << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/