// Problem: CF 1023 A - Single Wildcard Pattern Matching
// https://codeforces.com/contest/1023/problem/A

/*
 * Problem: Single Wildcard Pattern Matching
 * 
 * Purpose: Determine if string t matches pattern s, where s may contain at most one
 *          wildcard '*' that can be replaced with any sequence of lowercase letters.
 *
 * Algorithm:
 * 1. Check if the prefix of s matches the prefix of t from the start.
 * 2. Check if the suffix of s matches the suffix of t from the end.
 * 3. Ensure that the portion of t between the matched prefix and suffix contains
 *    only lowercase Latin letters (since wildcard can only match letters).
 * 4. Validate the constraints based on length and character matching.
 *
 * Time Complexity: O(n + m), where n is the length of s and m is the length of t.
 * Space Complexity: O(1), as we use only a constant amount of extra space.
 */

#include <iostream>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::string s, t;
  std::cin >> s >> t;
  
  // Possible is true if the length constraint is satisfied
  bool possible(s.size() <= 1 + t.size());
  
  // Pointers for matching prefix and suffix
  long sl(0), tl(0), sr(s.size() - 1), tr(t.size() - 1);
  
  // Match prefix of s and t
  while (sl < s.size() && tl < t.size() && s[sl] == t[tl]) {
    ++sl;
    ++tl;
  }
  
  // If a non-wildcard character was found in s (but not at the start),
  // then it's impossible to match
  if ((sl < s.size()) && s[sl] != '*') {
    possible = false;
  } else if (sl == s.size()) {
    // No wildcard, s must exactly match t
    possible = (s.size() == t.size());
  }
  
  // Match suffix of s and t
  while (0 <= sr && 0 <= tr && s[sr] == t[tr]) {
    --sr;
    --tr;
  }
  
  // If a non-wildcard character was found in s (but not at the end),
  // then it's impossible to match
  if ((sr >= 0) && s[sr] != '*') {
    possible = false;
  } else if (sr < 0) {
    // If we reached beginning of s, check exact size match
    possible = (s.size() == t.size());
  }
  
  // Validate that the middle part between prefix and suffix only has letters
  for (long p = tl; p <= tr; p++) {
    if (t[p] < 'a' || t[p] > 'z') {
      possible = false;
    }
  }
  
  std::cout << (possible ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/