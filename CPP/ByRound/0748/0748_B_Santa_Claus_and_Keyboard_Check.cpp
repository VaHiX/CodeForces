// Problem: CF 748 B - Santa Claus and Keyboard Check
// https://codeforces.com/contest/748/problem/B

/*
 * Problem: Santa Claus and Keyboard Check
 * 
 * Purpose: Determine which pairs of keys on Santa's keyboard are swapped such that
 *          typing the string 't' would produce the correct pattern 's'. Each key 
 *          is either in its place or swapped with exactly one other key.
 * 
 * Algorithm:
 *   - Compare each character in 's' and 't' at the same position.
 *   - If characters match, mark the character as unchanged.
 *   - If they don't match, check if they have an existing swap mapping.
 *   - If no mapping exists and characters aren't already set as unchanged, create new mapping.
 *   - Validate consistency in mappings to avoid contradictions.
 *   - Output the number of valid swaps and the pairs involved.
 * 
 * Time Complexity: O(n), where n is the length of the strings 's' and 't'.
 * Space Complexity: O(1), at most 26 characters for mapping and set storage.
 */

#include <stddef.h>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

int main() {
  std::string s, t;
  std::cin >> s >> t;
  bool possible = (s.size() == t.size()); // Ensure both strings have equal length
  std::map<char, char> swap;              // Maps each character to its swapped partner
  std::set<char> unchanged;               // Tracks characters that are in correct position

  // Iterate through each character in the strings
  for (size_t p = 0; p < s.size(); p++) {
    if (!possible) {
      break;
    }
    if (s[p] == t[p]) {
      // If characters match, ensure no prior swap exists for this character
      if (swap.count(s[p]) > 0) {
        possible = 0;
        break;
      } else {
        unchanged.insert(s[p]); // Mark unchanged
      }
    } else if (swap.count(s[p]) > 0 || swap.count(t[p]) > 0) {
      // If either character was already mapped, validate consistency
      if (swap[s[p]] != t[p] || swap[t[p]] != s[p]) {
        possible = 0;
        break;
      }
    } else if (unchanged.count(s[p]) > 0 || unchanged.count(t[p]) > 0) {
      // If either character was marked as unchanged, contradiction
      possible = 0;
      break;
    } else {
      // Create new mapping between characters
      swap[s[p]] = t[p];
      swap[t[p]] = s[p];
    }
  }

  if (possible) {
    // Output number of pairs and the pairs themselves
    std::cout << (swap.size() / 2) << std::endl;
    std::set<char> used; // Keep track of used characters to prevent double printing
    for (std::map<char, char>::iterator mapIter = swap.begin();
         mapIter != swap.end(); mapIter++) {
      char u = mapIter->first;
      char v = mapIter->second;
      if (used.count(u) > 0 || used.count(v) > 0) {
        continue; // Skip if already printed
      }
      used.insert(u);
      used.insert(v);
      std::cout << u << " " << v << std::endl;
    }
  } else {
    std::cout << "-1" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/