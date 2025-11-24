// Problem: CF 1165 C - Good String
// https://codeforces.com/contest/1165/problem/C

/*
C. Good String
Algorithm: Greedy string construction
Time complexity: O(n)
Space complexity: O(n)

Let's call (yet again) a string good if its length is even, and every character in odd position of this string is different from the next character (the first character is different from the second, the third is different from the fourth, and so on). For example, the strings good, string and xyyx are good strings, and the strings bad, aa and aabc are not good. 
Note that the empty string is considered good.
You are given a string s, you have to delete minimum number of characters from this string so that it becomes good.

The approach is to build a new string character by character:
1. For each character in input string, if it's the same as the last character in our result and we're at an odd position (after 0), skip it to avoid consecutive same characters.
2. Add all other characters to make the result "good" - no two adjacent characters are equal.

Then, ensure that the final result has even length by removing the last character if needed.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<char> t;
  for (long p = 0; p < s.size(); p++) {
    // If we already have an odd number of characters in result t,
    // and current character equals the last character in result,
    // skip it to prevent consecutive same characters
    if ((t.size() % 2) && s[p] == t.back()) {
      continue;
    }
    t.push_back(s[p]);  // Add current character to result
  }
  // If final length is odd, we must make it even by removing last character
  if (t.size() % 2) {
    t.pop_back();
  }
  std::cout << (s.size() - t.size()) << std::endl;  // Number of deletions
  for (long p = 0; p < t.size(); p++) {
    std::cout << t[p];
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/