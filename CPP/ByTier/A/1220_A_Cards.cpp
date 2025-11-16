// Problem: CF 1220 A - Cards
// https://codeforces.com/contest/1220/problem/A

/*
 * Problem: Cards
 * Purpose: Rearrange letters to form the maximum possible binary number.
 *          Each 'z','e','r','o','n' can be part of "zero" (0) or "one" (1).
 *          We want the largest number, so we place all 1s before 0s.
 *
 * Algorithm: Count occurrences of specific letters:
 *            - 'n', 'e', 'o' form "one"
 *            - 'z', 'e', 'r', 'o' form "zero"
 *            - We count 'n' for ones and 'z' for zeros
 *            - Then print all 1s followed by all 0s
 *
 * Time Complexity: O(n) - single pass through the string
 * Space Complexity: O(1) - only using a few variables, not dependent on input size
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long z(0), a(0); // z counts 'z' for zeros, a counts 'n' for ones
  for (long p = 0; p < s.size(); p++) {
    a += (s[p] == 'n'); // increment a if character is 'n'
    z += (s[p] == 'z'); // increment z if character is 'z'
  }
  for (long p = 0; p < a; p++) { // print all 1s (based on 'n' count)
    std::cout << "1 ";
  }
  for (long p = 0; p < z; p++) { // print all 0s (based on 'z' count)
    std::cout << "0 ";
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/