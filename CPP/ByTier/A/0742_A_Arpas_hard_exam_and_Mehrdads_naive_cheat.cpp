// Problem: CF 742 A - Arpa’s hard exam and Mehrdad’s naive cheat
// https://codeforces.com/contest/742/problem/A

/*
 * Purpose: To compute the last digit of 1378^n efficiently.
 * Algorithm: Pattern recognition in the last digits of powers of 1378.
 *            Since only the last digit of the base affects the last digit of powers,
 *            we observe that the last digit of 1378^n follows a cycle of length 4:
 *            8^1 -> 8, 8^2 -> 4, 8^3 -> 2, 8^4 -> 6, 8^5 -> 8 (cycle repeats).
 *            So, we use modulo 4 to determine the position in the cycle.
 * Time Complexity: O(1) - Constant time operation.
 * Space Complexity: O(1) - Constant space used.
 */
#include <iostream>
int main() {
  long n;
  std::cin >> n;
  int ans(0);
  if (n == 0) {
    ans = 1; // Any number to the power 0 is 1
  } else if (n % 4 == 1) {
    ans = 8; // Last digit pattern: 8
  } else if (n % 4 == 2) {
    ans = 4; // Last digit pattern: 4
  } else if (n % 4 == 3) {
    ans = 2; // Last digit pattern: 2
  } else if (n % 4 == 0) {
    ans = 6; // Last digit pattern: 6
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/