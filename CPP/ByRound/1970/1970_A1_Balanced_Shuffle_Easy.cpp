// Problem: CF 1970 A1 - Balanced Shuffle (Easy)
// https://codeforces.com/contest/1970/problem/A1

/*
Problem: Balanced Shuffle

The task is to compute the "balanced shuffle" of a given balanced parentheses sequence.

Approach:
1. For each character in the input string, calculate the prefix balance (number of '(' minus number of ')') up to that point.
2. Store these balances along with their original indices.
3. Sort the entries based on:
   - Primary key: prefix balance (ascending)
   - Secondary key: position (descending, to break ties)
4. Reconstruct the output string by placing characters in the sorted order of positions.

Algorithms/Techniques:
- Prefix sum calculation
- Custom sorting with multi-key comparison
- Stable reconstruction based on sorted indices

Time Complexity: O(n log n) due to sorting where n is the length of input string.
Space Complexity: O(n) for storing the vector of pairs and the output string.

Input:
A balanced parentheses sequence of length <= 500000.

Output:
The balanced shuffle of the input sequence.

Example:
Input: (()(()))
Output: ()(()())
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Custom comparator for sorting
// Sort by prefix balance ascending, and by position descending if balances are equal
bool cmp(std::pair<long, long> a, std::pair<long, long> b) {
  if (a.first == b.first) {
    return a.second > b.second; // Descending order of position for tie-breaking
  } else {
    return a.first < b.first; // Ascending order of prefix balance
  }
}

int main() {
  std::string s;
  std::cin >> s;
  
  // Vector to store (prefix_balance, original_position) pairs
  std::vector<std::pair<long, long>> v(s.size());
  
  long cnt(0); // Running balance counter
  for (long p = 0; p < s.size(); p++) {
    v[p] = std::make_pair(cnt, p); // Store current balance and position
    cnt += (s[p] == '(') - (s[p] == ')'); // Update balance: +1 for '(', -1 for ')'
  }
  
  sort(v.begin(), v.end(), cmp); // Sort according to custom comparator
  
  std::string t(s.size(), '.'); // Initialize result string with dots
  for (long p = 0; p < v.size(); p++) {
    t[p] = s[v[p].second]; // Reconstruct the string using sorted positions
  }
  
  std::cout << t << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/