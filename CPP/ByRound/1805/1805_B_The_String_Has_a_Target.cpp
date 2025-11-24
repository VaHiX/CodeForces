// Problem: CF 1805 B - The String Has a Target
// https://codeforces.com/contest/1805/problem/B

/*
B. The String Has a Target
Algorithm: Greedy
Purpose: Given a string, we can perform exactly one operation of moving any character to the beginning of the string. We aim to find the lexicographically smallest possible result after this operation.

Approach:
- For each test case, find the smallest character in the string.
- If there are multiple occurrences of the smallest character, choose the one with the smallest index so that when moved to the front, it results in the lexicographically smallest string.
- Move that character to the beginning and print the new string.

Time Complexity: O(n) per test case, where n is the length of the string. We scan the string twice (once to find minimum, once to output).
Space Complexity: O(1) additional space, not counting input/output storage.

Input:
- t: number of test cases
- For each test case:
  - n: length of string
  - s: string of lowercase letters

Output:
- For each test case, the lexicographically smallest string achievable after one operation.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long idx(0);                    // Initialize index of the smallest character
    char cur(s[0]);                 // Start with first character as current smallest
    for (long p = 1; p < s.size(); p++) {  // Iterate through string to find smallest
      if (s[p] <= cur) {            // If we find a smaller or equal character
        cur = s[p];                 // Update smallest character
        idx = p;                    // Update index of the smallest
      }
    }
    std::cout << s[idx]             // Output smallest character at the beginning
              << s.substr(0, idx)   // Append substring before the smallest character
              << s.substr(idx + 1, s.size())  // Append substring after the smallest character
              << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/