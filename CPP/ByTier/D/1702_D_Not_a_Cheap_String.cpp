// Problem: CF 1702 D - Not a Cheap String
// https://codeforces.com/contest/1702/problem/D

/*
Algorithm: Greedy approach
- Calculate total price of the string
- Sort characters in descending order by price (to remove highest priced characters first)
- Keep removing characters until total price <= target
- Output remaining characters in original order

Time Complexity: O(n log n) due to sorting, where n is the length of string
Space Complexity: O(n) for storing character info and boolean vector

Techniques:
- Greedy selection: remove highest value characters first to minimize deletions
- Preprocessing: calculate character values and their positions
- Vector-based tracking: use boolean vector to mark which characters to keep
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long target;
    std::cin >> target;
    long total(0);
    std::vector<std::pair<long, long>> w(s.size());
    for (long p = 0; p < s.size(); p++) {
      w[p] = std::make_pair(s[p] - 'a' + 1, p); // Store (price, original_index)
      total += w[p].first; // Calculate total price
    }
    sort(w.rbegin(), w.rend()); // Sort by price in descending order (highest first)
    std::vector<bool> v(s.size(), 1); // Mark which characters to keep (initially all keep)
    for (long p = 0; (target < total) && p < s.size(); p++) {
      total -= w[p].first; // Reduce total by removing this character's price
      v[w[p].second] = 0; // Mark this character for deletion
    }
    for (long p = 0; p < s.size(); p++) {
      if (!v[p]) { // If marked for deletion, skip
        continue;
      }
      std::cout << s[p]; // Print remaining characters in original order
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/