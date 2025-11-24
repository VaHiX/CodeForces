// Problem: CF 988 B - Substrings Sort
// https://codeforces.com/contest/988/problem/B

/*
 * Problem: B. Substrings Sort
 * 
 * Purpose: Rearrange a list of strings such that each string is a substring of all strings that come after it.
 * 
 * Algorithm: 
 * 1. Sort the strings by length in ascending order.
 * 2. Check if each string is a substring of the next one.
 * 3. If all checks pass, output "YES" and the sorted list; otherwise output "NO".
 * 
 * Time Complexity: O(n * m * log(n) + n * m)
 *   - Sorting takes O(n * log(n) * m) where m is the average string length
 *   - Loop for checking substrings takes O(n * m)
 * 
 * Space Complexity: O(n * m)
 *   - Storage for the vector of strings
 * 
 * Techniques:
 * - Sorting by string length
 * - Using find() method to check substring relationship
 * 
 * Note: The algorithm assumes that if strings are sorted by length, then for any valid arrangement,
 * the shorter string should be a prefix of the longer one (or at least a substring).
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// Comparator to sort strings by their lengths in ascending order
bool lengthCompare(std::string s, std::string t) { return s.size() < t.size(); }

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> v(n);
  for (long p = 0; p < n; p++) {
    std::cin >> v[p];
  }
  
  // Sort the strings by their length
  sort(v.begin(), v.end(), lengthCompare);
  
  bool possible(true);
  // Check if each string is a substring of the next one
  for (long p = 1; p < n; p++) {
    if (v[p].find(v[p - 1]) == std::string::npos) {
      possible = false;
      break;
    }
  }
  
  if (possible) {
    std::cout << "YES" << std::endl;
    for (long p = 0; p < n; p++) {
      std::cout << v[p] << std::endl;
    }
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/