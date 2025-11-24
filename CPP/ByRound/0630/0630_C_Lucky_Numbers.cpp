// Problem: CF 630 C - Lucky Numbers
// https://codeforces.com/contest/630/problem/C

/*
 * Purpose: Calculate the maximum number of lucky numbers that can be formed
 *          using digits 7 and 8 only, with length not exceeding n digits.
 * 
 * Algorithm: For each digit position, we have 2 choices (7 or 8). So for numbers
 *            with exactly k digits, there are 2^k possible combinations.
 *            Total combinations for lengths 1 to n = 2^1 + 2^2 + ... + 2^n
 *            This is a geometric series sum = 2^(n+1) - 2
 *            We subtract 2 because we don't count the empty string and the
 *            string "0" (which is not a valid lucky number).
 * 
 * Time Complexity: O(n) - single loop from 0 to n
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

#include <stdint.h>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int64_t res(1);
  for (int p = 0; p <= n; p++) {
    res *= 2;  // Multiply by 2 for each digit position (2 choices: 7 or 8)
  }
  res -= 2;  // Subtract 2 to exclude invalid cases (empty string and "0")
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/