// Problem: CF 1575 A - Another Sorting Problem
// https://codeforces.com/contest/1575/problem/A

/*
 * Problem: Sort strings in "asc-desc-ending" order.
 * 
 * Description:
 * Given n strings of length m, sort them according to a custom lexicographical order:
 * - Odd-indexed characters are compared ascendingly (a < b < ... < z)
 * - Even-indexed characters are compared descendingly (z > y > ... > a)
 * 
 * Algorithm:
 * 1. For each string, transform it by flipping even-positioned characters (0-indexed) 
 *    using 'A' + ('Z' - char), so that they sort descendingly in the comparison.
 * 2. Sort the transformed strings lexicographically ascending.
 * 3. Output original indices of sorted strings.
 * 
 * Time Complexity: O(n * m * log(n)) due to sorting n strings of length m
 * Space Complexity: O(n * m) for storing the transformed strings
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m;
  std::cin >> n >> m;
  std::vector<std::pair<std::string, long>> v(n);
  for (long p = 0; p < n; p++) {
    std::string s;
    std::cin >> s;
    // Transform even-indexed characters to make them sort descendingly in comparison
    for (long u = 1; u < s.size(); u += 2) {
      s[u] = 'A' + ('Z' - s[u]);
    }
    v[p].first = s;   // Store transformed string
    v[p].second = p + 1; // Store original index (1-based)
  }
  sort(v.begin(), v.end()); // Sort using custom comparison via transformed strings
  for (long p = 0; p < n; p++) {
    std::cout << v[p].second << " "; // Output original indices in sorted order
  }
  std::cout << std::endl;
}


// https://github.com/VaHiX/codeForces/