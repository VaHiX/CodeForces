// Problem: CF 1729 G - Cut Substrings
// https://codeforces.com/contest/1729/problem/G

/*
Algorithm: Dynamic Programming with String Matching
Purpose: To find the minimum number of operations to remove all occurrences of string t from string s,
         and count the number of different optimal sequences of operations.

Techniques:
- Dynamic Programming (DP)
- String Matching using memcmp
- State definition:
    f[i]: minimum number of moves to remove all occurrences of t from s[1..i]
    g[i]: number of ways to achieve f[i] moves for s[1..i]

Time Complexity: O(n * m * n) = O(n^2 * m), where n = len(s), m = len(t)
Space Complexity: O(n), for arrays f and g of size n+1

The algorithm works by iterating through the string s and for each position:
- If s[i-m+1..i] matches t, we compute the minimum number of moves to reach this point,
  by considering all valid previous positions that also match t.
- g[i] accumulates the number of ways to achieve that minimum.
- If there's a match, we iterate backwards to previous matches of t and update DP states.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
int f[510], g[510], t;
char s[510], p[510];
const int mod = 1e9 + 7;
int main() {
  cin >> t;
  while (t--) {
    scanf("%s%s", s + 1, p + 1);
    int n = strlen(s + 1), m = strlen(p + 1);
    for (int i = 0; i < m; i++) {
      f[i] = 0, g[i] = 1;
    }
    for (int i = m; i <= n; i++) {
      if (memcmp(s + i - m + 1, p + 1, m)) {
        // No match at current position
        f[i] = f[i - 1], g[i] = g[i - 1];
      } else {
        // Match found at current position
        f[i] = n + 1, g[i] = 0;
        for (int j = max(i - m + 1, m); j <= i; j++) {
          // Check backwards from current to see valid previous matches
          if (!memcmp(s + j - m + 1, p + 1, m)) {
            f[i] = min(f[i], f[j - m] + 1); // Update minimum moves
          }
        }
        for (int j = max(i - m + 1, m); j <= i; j++) {
          // Check again for valid ways to achieve the optimal number of moves
          if (!memcmp(s + j - m + 1, p + 1, m) && (f[i] == f[j - m] + 1)) {
            g[i] = (g[i] + g[j - m]) % mod; // Accumulate number of ways
          }
        }
      }
    }
    cout << f[n] << " " << g[n] << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/