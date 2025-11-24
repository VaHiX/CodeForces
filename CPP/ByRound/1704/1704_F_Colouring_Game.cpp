// Problem: CF 1704 F - Colouring Game
// https://codeforces.com/contest/1704/problem/F

/*
Algorithm/Techniques: 
This problem is a classic game theory problem involving nim-like gameplay with specific rules.
The approach uses:
1. **Nim Game Theory**: The game can be broken down into independent segments (groups of same-colored cells), and each group contributes to the overall XOR (nim-sum) of the game.
2. **Precomputed SG Values**: An array `sg` is used, which stores the Sprague-Grundy values for different group lengths. These values help determine the outcome of the game.
3. **Segmentation**: The string is segmented by color changes into groups of consecutive red or blue cells.
4. **Special Case Handling**: Based on the net count of red vs blue cells (`d`), the winner is decided directly if `d != 0`.

Time Complexity: O(n) per test case due to linear traversal of the string and constant-time operations for SG lookup.
Space Complexity: O(1) since the precomputed `sg` array is fixed and does not depend on input size; only a constant amount of extra space is used.
*/

#include <stdio.h>
#include <iostream>

using namespace std;

// Precomputed Sprague-Grundy values for group lengths
const int sg[87] = {0, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 0, 5, 2,
                    2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 2, 7, 4, 0,
                    1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2, 3,
                    3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8, 1, 1,
                    2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9};

int t, n, d, ans;
char s[500005];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cin >> t;
  while (t--) {
    // Read input string and set boundary condition
    cin >> n >> s + 1, s[n + 1] = s[n];
    
    // Count net red - blue cells
    d = 0;
    for (int i = 1; i <= n; i++)
      s[i] == 'R' ? d++ : d--;
    
    // Process segments of same-colored cells to compute nim-sum
    ans = 0;
    for (int i = 1, cnt = 0; i <= n + 1; i++) {
      if (s[i] == s[i - 1])
        // XOR with Sprague-Grundy value for current segment length
        ans ^= sg[cnt <= 52 ? cnt : (cnt - 53) % 34 + 53], cnt = 1;
      else
        cnt++;
    }
    
    // Determine winner based on net balance and nim-sum
    puts(d ? d > 0 ? "Alice" : "Bob" : ans ? "Alice" : "Bob"), d = ans = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/