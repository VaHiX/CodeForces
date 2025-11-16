// Problem: CF 1633 B - Minority
// https://codeforces.com/contest/1633/problem/B

/*
B. Minority
Problem Description:
Given a binary string, we must choose exactly one contiguous substring and remove all characters that are in the minority (i.e., less frequent) in that substring. The goal is to maximize the number of characters removed.

Algorithm:
- For each test case, iterate through the string and count '0's and '1's.
- If counts differ, remove the minority character (smaller count).
- If counts are equal, we cannot remove anything from this substring.
- We aim to find the optimal contiguous substring that maximizes the number of removed characters.

Time Complexity: O(n) where n is the total length of all strings across test cases.
Space Complexity: O(1) excluding input storage.

Techniques:
- Linear scan of string
- Counting characters in substring
- Greedy approach to maximize removals

*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long a(0), z(0);
    for (long p = 0; p < s.size(); p++) {
      z += (s[p] == '0');  // Count number of '0's
      a += (s[p] == '1');  // Count number of '1's
    }
    if (a != z) {
      std::cout << (a < z ? a : z) << std::endl;  // Remove minority character count
    } else {
      std::cout << (a - 1) << std::endl;  // Equal counts, remove one less than either
    }
  }
}


// https://github.com/VaHiX/codeForces/