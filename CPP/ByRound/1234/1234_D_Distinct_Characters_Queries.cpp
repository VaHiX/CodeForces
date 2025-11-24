// Problem: CF 1234 D - Distinct Characters Queries
// https://codeforces.com/contest/1234/problem/D

/*
D. Distinct Characters Queries
Algorithm/Technique: 
    - Using a vector of sets to track positions of each character in the string.
    - For update query (type 1), we remove the old position from the set of its character and add new position for the new character.
    - For count query (type 2), we iterate through all 26 lowercase letters and use binary search (lower_bound, upper_bound) to check if any occurrence exists in the given range [left, right].
Time Complexity: O(q * B * log(n)) where B=26 (number of letters), n is length of string, q is number of queries.
Space Complexity: O(n + B * n) = O(n) for storing string and sets of positions.

Code Description:
This program handles two types of operations on a string:
1. Update a character at a given position.
2. Count distinct characters in a substring.
It uses a vector of sets where each set stores the indices of a specific character in the string.
*/

#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  const long B = 26;
  std::string s;
  std::cin >> s;
  std::vector<std::set<long>> v(B); // Vector of sets for each character
  for (long p = 0; p < s.size(); p++) {
    v[s[p] - 'a'].insert(p); // Insert position of each character into corresponding set
  }
  long q;
  std::cin >> q;
  while (q--) {
    long w;
    std::cin >> w;
    if (w == 1) {
      long pos;
      char c;
      std::cin >> pos >> c;
      --pos;
      v[s[pos] - 'a'].erase(pos); // Remove old position from old character's set
      s[pos] = c;                 // Update string
      v[s[pos] - 'a'].insert(pos); // Insert new position into new character's set
    } else if (w == 2) {
      long left, right;
      std::cin >> left >> right;
      --left;
      --right;
      long cnt(0);
      for (long p = 0; p < B; p++) {
        std::set<long>::iterator ita = v[p].lower_bound(left);   // First position >= left
        std::set<long>::iterator itb = v[p].upper_bound(right);  // First position > right
        cnt += (ita != itb);  // If there’s at least one element in range, increment count
      }
      std::cout << cnt << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/