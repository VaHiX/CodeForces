// Problem: CF 1303 C - Perfect Keyboard
// https://codeforces.com/contest/1303/problem/C

/*
 * Problem: C. Perfect Keyboard
 * 
 * Purpose: Determine if a given string can be typed using a single-row keyboard layout,
 *          where each adjacent pair of characters in the string must be adjacent on the keyboard.
 * 
 * Algorithm:
 * 1. Build a graph where each character is a node and edges represent adjacency.
 * 2. For each adjacent pair in the string (excluding same characters), add an edge.
 * 3. Check if the graph is a valid path (at most 2 connections per node, with 1 start node).
 * 4. Construct the keyboard layout by traversing the path and adding remaining characters.
 * 
 * Time Complexity: O(n + 26) = O(n), where n is the length of string s.
 * Space Complexity: O(26 * 26) = O(1), fixed space for adjacency list.
 */

#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <string>

int main() {
  const int B = 26;
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<std::set<int>> f(B); // adjacency list for characters
    bool single(true);
    for (long p = 0; p < s.size(); p++) {
      int x = s[p] - 'a';
      if (p > 0) {
        int y = s[p - 1] - 'a';
        if (y != x) {
          f[x].insert(y);
          f[y].insert(x);
          single = false;
        }
      }
      if (p + 1 < s.size()) {
        int y = s[p + 1] - 'a';
        if (y != x) {
          f[x].insert(y);
          f[y].insert(x);
          single = false;
        }
      }
    }
    if (single) {
      // If only one unique character, arrange all letters in abc order
      std::string res = "";
      for (long p = 0; p < B; p++) {
        res += (char)('a' + p);
      }
      std::cout << "YES" << std::endl << res << std::endl;
      continue;
    }
    bool possible(true);
    int start(-1);
    for (long p = 0; p < B; p++) {
      if (f[p].size() > 2) {
        possible = false;
        break;
      }
      if (f[p].size() == 1) {
        start = p; // Find starting node (with only 1 neighbor)
      }
    }
    possible = possible && (start >= 0);
    if (!possible) {
      std::cout << "NO" << std::endl;
      continue;
    } else {
      std::vector<bool> done(B, 0); // track visited characters
      int cur(start), prev(start);
      std::string res("");
      while (!done[cur]) {
        done[cur] = true;
        res = (char)('a' + cur) + res; // prepend current character to result
        std::set<int> g = f[cur];
        int first = *g.begin();
        int last = *g.rbegin();
        if (!done[first]) {
          cur = first;
        } else if (!done[last]) {
          cur = last;
        } else {
          break; // No unvisited neighbor
        }
      }
      for (long p = 0; p < B; p++) {
        if (done[p]) {
          continue;
        }
        res = res + (char)('a' + p); // append remaining characters
      }
      std::cout << "YES" << std::endl;
      std::cout << res << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/