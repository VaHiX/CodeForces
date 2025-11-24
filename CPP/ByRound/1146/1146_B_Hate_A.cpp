// Problem: CF 1146 B - Hate "A"
// https://codeforces.com/contest/1146/problem/B

// B. Hate "A"
// Purpose: Given a string t, find a string s such that t = s + s', where s' is s with all 'a' characters removed.
// Algorithm: 
// 1. Count total number of 'a's in t.
// 2. Determine how many non-'a' characters should be in the first part of s (other = (n - cnt) / 2).
// 3. Try to construct s by taking characters from t, ensuring we split correctly so that s + s' equals t.
// Time complexity: O(n), where n is the length of string t
// Space complexity: O(n), for storing the input and output strings

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long cnt(0);
  // Count number of 'a's in the string
  for (long p = 0; p < s.size(); p++) {
    cnt += (s[p] == 'a');
  }
  // Calculate how many non-'a' characters should be in s
  long other = (s.size() - cnt) / 2;
  std::string sa(""), sb("");
  // Construct parts of the string
  for (long p = 0; p < s.size() && (cnt || other); p++) {
    sa += s[p];
    if (s[p] == 'a') {
      --cnt;
    } else {
      --other;
      sb += s[p];
    }
  }
  // Check if we've formed a valid decomposition
  if (sa + sb == s) {
    std::cout << sa << std::endl;
  } else {
    std::cout << ":(" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/