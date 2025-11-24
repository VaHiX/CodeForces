// Problem: CF 1266 A - Competitive Programmer
// https://codeforces.com/contest/1266/problem/A

/*
* Problem: Determine if digits of a given number can be rearranged to form a number divisible by 60.
* Algorithm:
*   - A number is divisible by 60 if and only if it's divisible by both 3 and 20.
*   - For divisibility by 3: sum of digits must be divisible by 3.
*   - For divisibility by 20: last two digits must form a number divisible by 20.
*   - Additionally, the entire number should contain at least one zero (to make it divisible by 20).
*   - To check if any permutation of digits makes a valid number:
*     * The number of zeros must be at least 1.
*     * There must be at least one even digit (to satisfy divisibility by 20's requirement).
*     * Sum of all digits must be divisible by 3.
* Time Complexity: O(n * m) where n is the number of test cases and m is average length of each string.
* Space Complexity: O(1) excluding input storage.
*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  while (n--) {
    std::string s;
    std::cin >> s;
    long v(0), z(0), t(0); // v: flag for even digit, z: flag for zero, t: sum of digits
    for (long p = 0; p < s.size(); p++) {
      long d = (s[p] - '0'); // convert char to int
      t += d;
      if ((!d) && (!z)) { // if digit is 0 and no zero seen yet
        z = 1;
      } else if (d % 2 == 0) { // if even digit
        v = 1;
      }
    }
    bool ans = (z && v && (t % 3 == 0)) || (s == "0"); // check conditions or special case "0"
    std::cout << (ans ? "red" : "cyan") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/