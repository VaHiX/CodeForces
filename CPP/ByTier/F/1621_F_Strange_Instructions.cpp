// Problem: CF 1621 F - Strange Instructions
// https://codeforces.com/contest/1621/problem/F

/*
Algorithm: Dynamic Programming with Greedy Strategy
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the lengths of zero segments

This solution processes a binary string and performs operations to maximize profit:
1. Replace "00" with "0" to gain 'a' coins.
2. Replace "11" with "1" to gain 'b' coins.
3. Remove '0' from any position to pay 'c' coins.

Constraint: No two consecutive operations with same parity (1,2,3) are allowed.

Approach:
- Count how many "00" and "11" substrings we have.
- Use the operation of replacing "00" and "11" to get maximum benefit (if a+b > c).
- Greedily decide which zero segments to remove based on cost vs benefit.
- Apply greedy algorithm to determine optimal removal of '0's.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int t, n, a, b, c, c00, c11, c101, cmn, len[N], cnt, r;
char s[N];
ll ans;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d", &n, &a, &b, &c);
    scanf("%s", s + 1);
    c00 = c11 = c101 = ans = 0;
    // Count occurrences of consecutive "00" and "11"
    for (int i = 1; i < n; i++) {
      if (s[i] == '0' && s[i + 1] == '0')
        c00++;
      if (s[i] == '1' && s[i + 1] == '1')
        c11++;
    }
    cmn = min(c00, c11); // Minimum of pairs that can be reduced
    c00 -= cmn, c11 -= cmn; // remaining pairs after reduction
    ans = 1ll * (a + b) * cmn; // benefit from reducing both types

    // If remaining 00 or 11, take one more step
    if (c00)
      ans += a, c00--;
    if (c11)
      ans += b, c11--;

    // Decide if it's advantageous to remove 0s and consider pattern "101"
    if (b > c) {
      cnt = 0;
      // Identify groups of zeros separated by ones
      for (int l = 1; l <= n; l = r + 1) {
        r = l;
        while (s[r] == '0' && r <= n)
          r++;
        if (l != 1 && r != n + 1 && r > l)
          len[++cnt] = r - l - 1; // store gap between 1s
      }
      sort(len + 1, len + cnt + 1); // sort gaps for greedy selection
      for (int i = 1; i <= cnt; i++) {
        if (cmn >= len[i])
          cmn -= len[i], c101++; // consume gap size using cmn
        else
          break;
      }
      // Final profit calculation
      ans += 1ll * (b - c) * (c101 + min(c11, (s[1] == '0') + (s[n] == '0')));
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/