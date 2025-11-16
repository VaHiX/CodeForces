// Problem: CF 1499 B - Binary Removals
// https://codeforces.com/contest/1499/problem/B

/*
B. Binary Removals
Algorithm: Greedy approach to check if we can remove some non-adjacent characters 
           to make the string sorted (non-decreasing).
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for tracking

The key insight:
- If there are two consecutive '0's followed by two consecutive '1's,
  we cannot make a sorted string by removing non-adjacent characters.
- The algorithm checks for such patterns in the string.

Sample Input/Output:
Input:
5
10101011011
0000
11111
110
1100
Output:
YES
YES
YES
YES
NO
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long z(-1), a(-1);
    for (long p = 1; p < s.size(); p++) {
      if (s[p - 1] == '0' && s[p] == '0') { // Check for two consecutive zeros
        z = p;
      }
      if (s[p - 1] == '1' && s[p] == '1' && a < 0) { // Check for first occurrence of two consecutive ones
        a = p;
      }
    }
    bool res = !(z > 0 && a > 0 && z > a); // If there is a zero-zero pattern after a one-one pattern, return NO (because it's impossible to sort)
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/