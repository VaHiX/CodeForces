// Problem: CF 2000 C - Numeric String Template
// https://codeforces.com/contest/2000/problem/C

/*
C. Numeric String Template
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: This problem checks if a string matches a numeric template by ensuring a bijective mapping exists between the numbers in the array and the characters in the string.

Approach:
- For each string, we maintain two maps:
  - numtochar: maps numbers from the array to characters in the string
  - chartonum: maps characters from the string to numbers in the array
- We scan both the array and the string simultaneously:
  - If a number has not been seen before, we assign it to a character.
  - If a number has been seen before, we verify it is mapped to the same character.
  - Similarly for characters: ensure they are consistently mapped to the same number.
- If any inconsistency is found during the process, the match fails.

Time Complexity: O(n + sum of string lengths across all test cases)
Space Complexity: O(n) - for storing mappings

*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      std::cin >> a[p];
    }
    long m;
    std::cin >> m;
    while (m--) {
      std::map<long, char> numtochar;     // Maps numbers from array to characters
      std::map<char, long> chartonum;     // Maps characters to numbers from array
      std::string s;
      std::cin >> s;
      if (s.size() != n) {
        std::cout << "NO" << std::endl;
        continue;
      }
      bool res(true);
      for (long p = 0; res && p < s.size(); p++) {
        long f(a[p]);         // Current number from the array
        char g(s[p]);         // Current character from the string
        // If one mapping exists but not the other, mapping is inconsistent
        if (numtochar.count(f) ^ chartonum.count(g)) {
          res = false;
        }
        // If number hasn't been mapped yet, create mappings
        if (!numtochar.count(f)) {
          numtochar[f] = g;
          chartonum[g] = f;
        } else if (numtochar[f] != g || chartonum[g] != f) {
          // Check consistency of existing mappings
          res = false;
        }
      }
      std::cout << (res ? "YES" : "NO") << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/