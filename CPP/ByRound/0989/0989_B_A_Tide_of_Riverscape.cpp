// Problem: CF 989 B - A Tide of Riverscape
// https://codeforces.com/contest/989/problem/B

/*
 * Problem: B. A Tide of Riverscape
 * 
 * Algorithm/Techniques: Greedy approach with period checking
 * 
 * Time Complexity: O(n * k) where n is the length of string and k is the period
 * Space Complexity: O(1) excluding the input string storage
 * 
 * The solution works by iterating through all possible starting positions (0 to k-1)
 * for a period of length k. For each such starting position, we check if there is a 
 * conflict with the character at position (start + k). If there is, we make a change 
 * to ensure that the two characters are different in order to break the period k.
 * 
 * After fixing conflicts, we fill in the remaining '.' characters with '1'.
 * If any change was made, we output the modified string; otherwise, we output "No".
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  bool possible(false);
  for (long start = 0; start < k; start++) {
    if (start + k >= n) {
      continue;
    }
    bool pass(false);
    for (long u = start + k; u < n; u += k) {
      // If both characters are '.' or they are different, there's a conflict
      if ((s[start] == '.' && s[u] == '.') || s[u] != s[start]) {
        // If s[start] and s[u] are equal but both not '.', this is not a conflict
        // But since we are in this block, we know they are different or one is '.'
        if (s[start] == s[u]) {
          // If s[start] and s[u] are both '.', we decide to make them different
          s[start] = '0';
          s[u] = '1';
        } else if (s[start] == '.') {
          // If only s[start] is '.', decide based on s[u]
          s[start] = (s[u] == '0') ? '1' : '0';
        } else if (s[u] == '.') {
          // If only s[u] is '.', decide based on s[start]
          s[u] = (s[start] == '0') ? '1' : '0';
        }
        pass = true;
      }
    }
    possible |= pass;
  }
  // Fill all remaining '.' with '1' to ensure we have a complete string
  for (long p = 0; p < n; p++) {
    if (s[p] == '.') {
      s[p] = '1';
    }
  }
  if (possible) {
    std::cout << s << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/