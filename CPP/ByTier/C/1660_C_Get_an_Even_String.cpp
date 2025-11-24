// Problem: CF 1660 C - Get an Even String
// https://codeforces.com/contest/1660/problem/C

/*
C. Get an Even String
Algorithm: Greedy approach with set usage
Time Complexity: O(n) where n is the length of the string (each character is processed once)
Space Complexity: O(1) since the set stores at most 26 characters (lowercase Latin letters)

A string is even if it can be split into pairs of identical characters.
The algorithm processes the string from left to right and greedily removes
characters to form valid pairs. When a character is encountered that already
exists in the current set, we form a pair and clear the set for next pair.
Otherwise, we add the character to the set.

Key steps:
1. For each character in string:
   - If character already exists in set, remove it (form a pair) and clear set
   - Else, insert character into set
2. At end of string, remaining characters in set are unpaired and must be removed
*/

#include <iostream>
#include <set>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long rem(s.size()); // Initialize remaining characters to total length
    std::set<char> obs; // Set to track unpaired characters
    for (long p = 0; p < s.size(); p++) {
      if (obs.count(s[p])) { // If character is already in set, form a pair
        rem -= 2; // Reduce count by 2 (both characters of the pair)
        obs.clear(); // Clear set for next pair
      } else {
        obs.insert(s[p]); // Add character to set
      }
    }
    std::cout << rem << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/