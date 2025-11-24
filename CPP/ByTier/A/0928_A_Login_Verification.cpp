// Problem: CF 928 A - Login Verification
// https://codeforces.com/contest/928/problem/A

#include <ctype.h>
#include <iostream>
#include <string>

/*
 * Problem: Check if a new login is similar to any existing login.
 * Two logins are similar if one can be transformed to another using:
 * 1. Case change (upper <-> lower)
 * 2. 'O' <-> '0'
 * 3. '1' <-> 'l' <-> 'I'
 *
 * Time Complexity: O(n * m), where n is number of existing logins and m is average login length.
 * Space Complexity: O(m), for storing the input strings.
 */
int main() {
  std::string s;
  std::cin >> s;
  long n;
  std::cin >> n;
  bool possible(true);
  while (n--) {
    std::string t;
    std::cin >> t;
    if (s.size() != t.size()) {
      continue;  // Different lengths cannot be similar
    }
    bool similar(true);
    for (long p = 0; p < s.size(); p++) {
      // If characters are the same (case insensitive), continue
      if (tolower(s[p]) == tolower(t[p])) {
        continue;
      }
      // Check for 'O' and '0' equivalence
      if (tolower(s[p]) == 'o' && t[p] == '0') {
        continue;
      }
      if (tolower(t[p]) == 'o' && s[p] == '0') {
        continue;
      }
      // Check for '1' and 'l'/'I' equivalence
      if (s[p] == '1' && tolower(t[p]) == 'l') {
        continue;
      }
      if (s[p] == '1' && tolower(t[p]) == 'i') {
        continue;
      }
      if (tolower(s[p]) == 'i' && t[p] == '1') {
        continue;
      }
      if (tolower(s[p]) == 'i' && tolower(t[p]) == 'l') {
        continue;
      }
      if (tolower(s[p]) == 'l' && t[p] == '1') {
        continue;
      }
      if (tolower(s[p]) == 'l' && tolower(t[p]) == 'i') {
        continue;
      }
      similar = false;
      break;
    }
    if (similar) {
      possible = false;
      break;
    }
  }
  std::cout << (possible ? "Yes" : "No") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/