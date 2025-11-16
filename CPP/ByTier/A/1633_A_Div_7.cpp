// Problem: CF 1633 A - Div. 7
// https://codeforces.com/contest/1633/problem/A

/*
Algorithm: Greedy approach to make the number divisible by 7 with minimum changes.
Approach:
1. For each digit from left to right, calculate the current modulo 7 of the number formed so far.
2. For the last digit, adjust it to make the entire number divisible by 7.
   - If the current last digit is greater than or equal to the required adjustment, decrease it.
   - Otherwise, increase it by (7 - required adjustment) to maintain the minimum digit changes.
3. Ensure no leading zeros are introduced.

Time Complexity: O(n) where n is the length of the string representation of the number.
Space Complexity: O(1) excluding the input string storage.

*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long n = s.size();
    long mod(0);
    for (long p = 0; p < n; p++) {
      mod = 10 * mod + (s[p] - '0');
      mod %= 7;
    }
    s[n - 1] =
        (s[n - 1] >= (mod + '0')) ? (s[n - 1] - mod) : (s[n - 1] + 7 - mod);
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/