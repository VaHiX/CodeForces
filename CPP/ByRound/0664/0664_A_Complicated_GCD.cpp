// Problem: CF 664 A - Complicated GCD
// https://codeforces.com/contest/664/problem/A

/*
 * Problem: Complicated GCD
 * 
 * Purpose: Find the greatest common divisor (GCD) of all integers in the range [a, b].
 * 
 * Algorithm: 
 *   - If a == b, then GCD of all numbers in the range is simply a (or b).
 *   - Otherwise, if a < b, then the range contains at least two different numbers.
 *     For any two distinct integers, their GCD is at most 1.
 *     Hence, in such cases, the result is always 1.
 * 
 * Time Complexity: O(n) where n is the length of the string representation of the numbers.
 *                    Comparison of two strings of equal length takes linear time.
 * Space Complexity: O(1) - only using a constant amount of extra space (not counting input size).
 */

#include <iostream>
#include <string>

int main() {
  std::string a, b;
  std::cin >> a >> b;
  std::cout << (a == b ? a : "1") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/