// Problem: CF 1241 B - Strings Equalization
// https://codeforces.com/contest/1241/problem/B

/*
B. Strings Equalization
Algorithm: Check if two strings can be made equal by swapping adjacent characters.
Approach: 
    - For each query, check if there exists at least one common character between the two strings.
    - If so, it's possible to rearrange both strings to be equal since we can swap adjacent characters.
Time Complexity: O(n) where n is the length of the strings (due to set insertion and lookup)
Space Complexity: O(1) since there are at most 26 unique lowercase letters
*/
#include <iostream>
#include <set>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    std::string s, t;
    std::cin >> s >> t;
    bool possible(false);
    std::set<char> x;  // Set to store unique characters of string s
    for (long p = 0; p < s.size(); p++) {
      x.insert(s[p]);  // Insert each character of s into set x
    }
    std::set<char> y;  // Set to store unique characters of string t
    for (long p = 0; p < t.size(); p++) {
      y.insert(t[p]);  // Insert each character of t into set y
    }
    // Check if any character from s exists in t
    for (std::set<char>::iterator it = x.begin(); it != x.end(); it++) {
      if (y.count(*it)) {  // If common character found
        possible = true;
        break;
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/