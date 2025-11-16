// Problem: CF 931 E - Game with String
// https://codeforces.com/contest/931/problem/E

/*
Algorithm: Game with String
Purpose: To compute the probability that Vasya can uniquely determine the cyclic shift k
         after opening two letters (first and one additional) optimally.

Approach:
- For each possible first letter (character) in the string:
  - Find all positions where that character appears
  - For each possible shift amount p (1 to len-1):
    - Count how many distinct characters appear at positions (pos + p) % len
      for all positions pos where the character occurs
    - Track maximum number of unique characters seen for any shift p
  - Add the average of maximum unique counts across all characters
- Final answer is total / len

Time Complexity: O(n^2) where n is length of string. 
Space Complexity: O(n) for storing character positions and maps.
*/
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  std::map<char, std::vector<long>> m; // Map character to list of its positions
  for (long p = 0; p < s.size(); p++) {
    m[s[p]].push_back(p);
  }
  double total(0.0);
  for (std::map<char, std::vector<long>>::iterator it = m.begin();
       it != m.end(); it++) {
    char ch = it->first;
    std::vector<long> v = it->second;
    long mxu(0);
    for (long p = 1; p < s.size(); p++) {
      long unique(0);
      std::map<char, long> sm; // Map to count occurrences of characters at shifted positions
      for (long u = 0; u < v.size(); u++) {
        char tc = s[(v[u] + p) % s.size()]; // Get character at shifted position
        ++sm[tc];
        if (sm[tc] == 1) {
          ++unique; // First occurrence of tc
        } else if (sm[tc] == 2) {
          --unique; // Second occurrence means we lose one unique character
        }
      }
      mxu = (mxu > unique) ? mxu : unique; // Keep maximum unique count
    }
    total += 1.0 * mxu / s.size(); // Add normalized contribution to total
  }
  printf("%.8lf\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/