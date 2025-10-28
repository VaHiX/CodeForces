// Problem: CF 1512 C - A-B Palindrome
// https://codeforces.com/contest/1512/problem/C

/*
C. A-B Palindrome
Algorithm: Greedy approach to construct palindrome with exact count of '0' and '1'
Time Complexity: O(n) per test case, where n is the length of string s
Space Complexity: O(n) for storing the string s

Approach:
1. First pass: resolve known character pairs (non-'?') and count how many '0's and '1's we already have.
2. Second pass: fill remaining '?' characters by greedily choosing '0' or '1' to meet target counts,
   ensuring palindrome property is maintained.

Steps:
1. Iterate through the string and validate palindromic constraints for corresponding pairs.
2. Count existing '0' and '1' in valid positions.
3. Fill unmatched '?' with values to achieve a, b counts while maintaining palindrome structure.

This greedy fill ensures that we use the minimal required number of new characters to meet count restrictions,
and always prioritize filling based on availability to reach target a,b.
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long a, b;
    std::cin >> a >> b;
    std::string s;
    std::cin >> s;
    long n = s.size();
    bool possible(true);
    long z(0), d(0);
    
    // First pass: resolve known pairs and count existing 0s and 1s
    for (long p = 0; 2 * p < n; p++) {
      if (s[p] != '?' && s[n - 1 - p] != '?' && s[p] != s[n - 1 - p]) {
        possible = false;
        break;
      } else if (s[p] == s[n - 1 - p] && s[p] != '?') {
        z += (1 + (p != n - 1 - p)) * (s[p] == '0'); // Add contribution to count of 0s
        d += (1 + (p != n - 1 - p)) * (s[p] == '1'); // Add contribution to count of 1s
      } else if (s[p] == '?' && s[n - 1 - p] != '?') {
        s[p] = s[n - 1 - p]; // Set the pair to match
        z += (1 + (p != n - 1 - p)) * (s[p] == '0');
        d += (1 + (p != n - 1 - p)) * (s[p] == '1');
      } else if (s[n - 1 - p] == '?' && s[p] != '?') {
        s[n - 1 - p] = s[p]; // Set the pair to match
        z += (1 + (p != n - 1 - p)) * (s[p] == '0');
        d += (1 + (p != n - 1 - p)) * (s[p] == '1');
      }
    }
    
    // Second pass: fill remaining '?' characters greedily
    for (long p = 0; 2 * p < n; p++) {
      if (s[p] == '?' && s[n - 1 - p] == '?' && p != n - 1 - p) {
        // Both are '?', and not the middle element
        if (z <= a - 2) {
          s[p] = s[n - 1 - p] = '0';
          z += 2;
        } else if (d <= b - 2) {
          s[p] = s[n - 1 - p] = '1';
          d += 2;
        }
      } else if (s[p] == '?' && s[n - 1 - p] == '?' && p == n - 1 - p) {
        // Middle char (odd length), only one char to fill
        if (z <= a - 1) {
          s[p] = '0';
          ++z;
        } else if (d <= b - 1) {
          s[p] = '1';
          ++d;
        }
      }
    }
    
    // Check whether counts match target
    if (z != a) {
      possible = false;
    }
    if (d != b) {
      possible = false;
    }
    
    std::cout << (possible ? s : "-1") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/