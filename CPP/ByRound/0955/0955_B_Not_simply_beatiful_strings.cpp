// Problem: CF 955 B - Not simply beatiful strings
// https://codeforces.com/contest/955/problem/B

/*
Purpose: Determine if a string can be split into two non-empty subsequences,
         each of which can be rearranged to form two consecutive groups of equal characters.
         This is equivalent to checking if we can partition the string into two "adorable" parts.

Algorithms/Techniques:
- Frequency count of characters using a map
- Analysis based on number of unique characters and their frequencies

Time Complexity: O(n), where n is the length of the string. 
                 We iterate through the string once to count characters, 
                 and then iterate through the map (at most 26 characters for lowercase letters).

Space Complexity: O(1), since the map stores at most 26 characters (constant space).

*/
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  std::string s;
  std::cin >> s;
  std::map<char, long> cm; // Count frequency of each character
  for (long p = 0; p < s.size(); p++) {
    ++cm[s[p]];
  }
  bool one(false); // Flag to check if any character appears exactly once
  for (std::map<char, long>::iterator it = cm.begin(); it != cm.end(); it++) {
    if (it->second == 1) {
      one = true;
    }
  }
  // If string length is less than 4 or more than 4 unique characters or only 1 unique character
  if (s.size() < 4 || cm.size() > 4 || cm.size() == 1) {
    std::cout << "No" << std::endl;
  } else if (cm.size() >= 3) {
    // If there are 3 or more unique characters, it's always possible to split
    std::cout << "Yes" << std::endl;
  } else if (one) {
    // If there are exactly 2 unique characters and one of them appears only once,
    // it's impossible to make both parts adorable
    std::cout << "No" << std::endl;
  } else {
    // If there are exactly 2 unique characters and both appear more than once,
    // it's possible to split into two adorable parts
    std::cout << "Yes" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/