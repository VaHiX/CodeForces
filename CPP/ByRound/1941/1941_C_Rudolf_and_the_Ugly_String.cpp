// Problem: CF 1941 C - Rudolf and the Ugly String
// https://codeforces.com/contest/1941/problem/C

/*
C. Rudolf and the Ugly String
Purpose: 
  Given a string, remove minimum number of characters to make it "beautiful", where a beautiful string does not contain "pie" or "map" as substrings.

Algorithms/Techniques:
  - Greedy string matching with substring search
  - Multiple passes to find and mark overlapping patterns

Time Complexity: O(n^2) in worst case due to repeated string operations and searches.
Space Complexity: O(n) for storing the input string.

Note: This implementation modifies the string during processing, which can lead to inefficiencies in some cases. A more optimized approach would involve counting non-overlapping matches or using dynamic programming.

*/

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
    long cnt(0), idx(0);
    
    // First pass: Find and mark "mapie" occurrences
    while (idx != std::string::npos) {
      idx = s.find("mapie", idx);  // Find next occurrence of "mapie"
      if (idx == std::string::npos) {
        break;
      }
      ++cnt;  // Increment counter for each match found
      s[idx + 2] = '$';  // Mark the 'a' in "mapie" so it won't be part of other matches
      ++idx;  // Move index forward to continue searching
    }
    
    idx = 0;
    // Second pass: Find and mark "map" occurrences
    while (idx != std::string::npos) {
      idx = s.find("map", idx);  // Find next occurrence of "map"
      if (idx == std::string::npos) {
        break;
      }
      ++cnt;  // Increment counter for each match found
      s[++idx] = '$';  // Mark the 'a' in "map" to avoid overlap with others
    }
    
    idx = 0;
    // Third pass: Find and mark "pie" occurrences
    while (idx != std::string::npos) {
      idx = s.find("pie", idx);  // Find next occurrence of "pie"
      if (idx == std::string::npos) {
        break;
      }
      ++cnt;  // Increment counter for each match found
      s[++idx] = '$';  // Mark the 'i' in "pie" to avoid overlap with others
      ++idx;  // Move past both 'i' and 'e'
    }
    
    std::cout << cnt << std::endl;  // Output total number of deletions needed
  }
}


// https://github.com/VaHiX/codeForces/