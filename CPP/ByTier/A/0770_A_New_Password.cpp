// Problem: CF 770 A - New Password
// https://codeforces.com/contest/770/problem/A

/*
Purpose: This code generates a password of length `n` using exactly `k` distinct lowercase Latin letters such that no two consecutive characters are the same.

Algorithm/Techniques:
- The approach uses a cyclic repetition of the first `k` lowercase letters.
- For each position `p` in the password, the character is determined by `(p % k)`, which ensures that:
  - We cycle through the letters from 'a' to 'a'+(k-1)
  - No two adjacent positions have the same character due to the modulo operation
- This guarantees exactly `k` distinct letters and satisfies all constraints.

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <iostream>
#include <string>

int main() {
  int n, k;
  std::cin >> n >> k;
  std::string s;
  for (int p = 0; p < n; p++) {
    s += 'a' + (p % k);  // Append character cyclically from 'a' to 'a'+(k-1)
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/