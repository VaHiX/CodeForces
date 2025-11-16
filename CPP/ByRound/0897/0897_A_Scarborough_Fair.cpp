// Problem: CF 897 A - Scarborough Fair
// https://codeforces.com/contest/897/problem/A

/*
 * Problem: Scarborough Fair
 * Purpose: Perform a series of character replacements on a string within given ranges.
 * Algorithm/Techniques: Direct simulation of operations
 *
 * Time Complexity: O(n * m), where n is the length of the string and m is the number of operations.
 *                    In the worst case, each operation may traverse the entire string.
 *
 * Space Complexity: O(n), to store the string of length n.
 */

#include <iostream>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::string s;
  std::cin >> s;
  while (m--) {
    long l, r;
    char c1, c2;
    std::cin >> l >> r >> c1 >> c2;
    for (long p = l - 1; p < r; p++) {
      s[p] = (s[p] == c1) ? c2 : s[p];  // Replace c1 with c2 if match found
    }
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/