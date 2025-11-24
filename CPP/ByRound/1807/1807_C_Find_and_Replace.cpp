// Problem: CF 1807 C - Find and Replace
// https://codeforces.com/contest/1807/problem/C

/*
C. Find and Replace
time limit per test1 second
memory limit per test256 megabytes

Algorithm/Techniques: Greedy with character mapping
Approach:
- For each character in the string, we determine whether it should map to '0' or '1' based on its position (even/odd).
- We use a vector of size 26 to track the expected parity ('0' or '1') for each character.
- If a character has been seen before and its assigned parity differs from current position's parity, it's impossible to form an alternating string.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) since the vector size is fixed at 26 (constant space)

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<int> a(26, -1); // Track the parity (0 or 1) assigned to each character
    bool ans(true);
    for (long p = 0; ans && p < s.size(); p++) {
      int x = s[p] - 'a'; // Convert char to index (0-25)
      if (a[x] < 0) {
        a[x] = p % 2; // Assign parity based on position
      } else if (a[x] != p % 2) {
        ans = false; // Conflict in parity assignment
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/