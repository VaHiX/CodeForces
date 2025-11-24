// Problem: CF 1913 B - Swap and Delete
// https://codeforces.com/contest/1913/problem/B

/*
B. Swap and Delete
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given a binary string s, we want to make it "good" by performing operations:
- Delete one character (costs 1 coin)
- Swap any two characters (free)

A string t is good if for each position i, t[i] != s[i].

Algorithm:
We use a greedy approach:
1. Count total 0s and 1s.
2. Traverse the string and simulate swaps or deletions:
   - When encountering a '1', try to use a saved '0' to avoid conflict (greedy).
   - Similarly for '0' using '1'.
   - If no saved character is available, we must delete from current position forward.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long z(0), a(0); // z counts 0s, a counts 1s
    for (long p = 0; p < s.size(); p++) {
      z += (s[p] == '0');   // count zeros
      a += (s[p] == '1');   // count ones
    }
    long ans(0);
    for (long p = 0; !ans && p < s.size(); p++) {
      if (s[p] == '1') {
        if (z > 0) {
          --z;  // use a saved zero to avoid conflict
        } else {
          ans = s.size() - p;  // must delete everything from here on
          break;
        }
      } else if (s[p] == '0') {
        if (a > 0) {
          --a;  // use a saved one to avoid conflict
        } else {
          ans = s.size() - p;  // must delete everything from here on
          break;
        }
      }
    }
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/