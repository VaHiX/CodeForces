// Problem: CF 448 B - Suffix Structures
// https://codeforces.com/contest/448/problem/B

/*
Algorithm: Suffix Structures
Purpose: Determine if string `s` can be transformed into string `t` using suffix automaton (remove characters) or suffix array (swap characters).
Techniques: 
- Check if `t` is a subsequence of `s` (suffix automaton operation).
- Count character frequencies to determine if `s` contains enough characters for `t` and whether swaps are sufficient (suffix array operation).
Time Complexity: O(n), where n is the length of the longer string.
Space Complexity: O(1), since we use a fixed-size vector of 26 elements for character counting.

Approach:
1. First check if `t` is a subsequence of `s` (using prefix matching); if yes, automaton is sufficient.
2. Else, compare character frequency counts:
   - If all counts are zero, then `s` and `t` are anagrams → array is sufficient.
   - If any count is negative, then `t` has more of a character than `s` → need tree.
   - Otherwise, use both automaton and array.

*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string first;
  getline(std::cin, first);
  std::string second;
  getline(std::cin, second);
  int index = 0;
  for (int p = 0; p < first.size(); p++) {
    if (first[p] == second[index]) {
      ++index;
    }
  }
  if (index >= second.size()) {
    puts("automaton");
  } else {
    const int N = 26;
    std::vector<int> countVec(N, 0);
    for (int p = 0; p < first.size(); p++) {
      ++countVec[first[p] - 'a'];
    }
    for (int p = 0; p < second.size(); p++) {
      --countVec[second[p] - 'a'];
    }
    bool array(1), tree(0);
    for (int p = 0; p < N; p++) {
      if (countVec[p] != 0) {
        array = 0;
      };
      if (countVec[p] < 0) {
        tree = 1;
        break;
      }
    }
    if (array) {
      puts("array");
    } else if (!tree) {
      puts("both");
    } else {
      puts("need tree");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/