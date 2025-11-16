// Problem: CF 1616 B - Mirror in the String
// https://codeforces.com/contest/1616/problem/B

/*
B. Mirror in the String
Algorithm: Greedy approach to find the optimal mirror position k that minimizes the lexicographically 
           resulting string after mirroring s[0..k] and appending its reverse.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) due to string operations and storage of substrings.

Approach:
- For each test case, we try to construct a mirrored string by choosing k optimally.
- We iterate through the string to find the longest prefix that is non-increasing (i.e., each character 
  is greater than or equal to the next one) – this ensures we are building a palindrome-like structure
  when mirrored.
- If such a prefix exists, we take the mirror of it and compare with just the first two characters of s 
  appended to itself as a fallback. The lexicographically smaller result is output.

Key Points:
- We add 'z' at the end of s to make loop logic cleaner (avoids needing to check boundaries manually).
- We build string v (initially "s[0]s[0]") and compare against constructed mirrored string w.
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s += 'z'; // Append sentinel to avoid boundary checks
    std::string v(2, s[0]); // Default answer: first letter repeated twice
    long len(0);
    for (long p = 0; p + 1 < s.size(); p++) {
      len = p + 1;
      if (s[p] < s[p + 1]) {
        break;
      };
    }
    std::string t(s.substr(0, len)); // Extract prefix up to non-increasing point
    std::string w(t);
    std::reverse(t.begin(), t.end()); // Reverse the prefix to simulate mirror effect
    w = w + t; // Combine original prefix with its reverse
    if (w < v) {
      std::cout << w << std::endl;
    } else {
      std::cout << v << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/