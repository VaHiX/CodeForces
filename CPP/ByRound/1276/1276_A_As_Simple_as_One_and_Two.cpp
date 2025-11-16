// Problem: CF 1276 A - As Simple as One and Two
// https://codeforces.com/contest/1276/problem/A

/*
Algorithm: Greedy string matching with substring detection
Techniques: Sliding window, greedy optimization

Time Complexity: O(n) where n is the length of the string. Each character is processed a constant number of times.
Space Complexity: O(k) where k is the number of positions to remove. The space is used to store the result vector r.

The approach uses a greedy method to find and remove overlapping or adjacent substrings "one" and "two".
We slide through the string and detect these patterns, removing the minimal set of characters to eliminate all occurrences.
*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> r;
    char bb(s[0]), b(s[1]);
    for (long p = 2; p < s.size(); p++) {
      // Check for "one" substring
      if (bb == 'o' && b == 'n' && s[p] == 'e') {
        r.push_back(p - 1); // Mark the 'n' position for removal
        b = s[p]; // Update b to the last character of the matched substring
      } else if (bb == 't' && b == 'w' && s[p] == 'o') {
        // Check for "two" substring
        if (p + 1 < s.size() && s[p + 1] == 'n') {
          // Handle case where "ton" could be part of a longer pattern
          // We avoid removing 'o' if that would create an overlap.
          r.push_back(p); // Mark the 'w' position for removal to avoid creating invalid substrings
        } else {
          r.push_back(p - 1); // Mark the 'w' position for removal
          b = s[p]; // Update b for the next iteration
        }
      } else {
        // Move the sliding window forward
        bb = b;
        b = s[p];
      }
    }
    std::cout << r.size() << std::endl;
    for (long p = 0; p < r.size(); p++) {
      std::cout << (1 + r[p]) << " "; // Print 1-based indices
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/