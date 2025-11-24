// Problem: CF 526 A - King of Thieves
// https://codeforces.com/contest/526/problem/A

/*
Algorithm: King of Thieves
Approach:
- The problem asks to find if there exists a sequence of 5 platforms (positions) such that the differences between consecutive positions are equal (i.e., arithmetic progression of length 5).
- We iterate over all possible starting positions (b) which are platforms ('*').
- For each starting position, we try all possible jump sizes (j).
- We check if there are 4 more platforms at positions b+j, b+2j, b+3j, b+4j.
- If all these positions are valid platforms, then a valid sequence of 5 platforms exists.

Time Complexity: O(n^3)
- Outer loop: O(n)
- Inner loop (jump size): O(n)
- Innermost validation: O(1) (since we check only 4 jumps)
Space Complexity: O(1)
- Only using a constant amount of extra space (variables and string ans).

*/
#include <cstdio>
#include <iostream>
#include <string>

int main() {
  int n;
  scanf("%d\n", &n);
  std::string s;
  getline(std::cin, s);
  std::string ans = "no";
  for (int b = 0; b < s.size(); b++) {
    if (ans == "yes") {
      break;
    }
    if (s[b] == '.') {
      continue;
    }
    for (int j = 1; j < s.size(); j++) {
      bool possible = 1;
      for (int u = 1; u <= 4; u++) {
        if (b + u * j >= s.size() || s[b + u * j] == '.') {
          possible = 0;
          break;
        }
      }
      if (possible) {
        ans = "yes";
        break;
      }
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/