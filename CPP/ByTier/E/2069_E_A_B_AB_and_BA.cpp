// Problem: CF 2069 E - A, B, AB and BA
// https://codeforces.com/contest/2069/problem/E

/*
E. A, B, AB and BA
Algorithm: Greedy with block grouping and optimization
Time Complexity: O(n log n) per test case due to sorting vectors
Space Complexity: O(n) for storing the string and auxiliary vectors

Task: Split a string of 'A' and 'B' into blocks of length 1 and 2 such that:
- No more than 'a' strings equal to "A"
- No more than 'b' strings equal to "B"
- No more than 'ab' strings equal to "AB"
- No more than 'ba' strings equal to "BA"
Strings "AA" and "BB" are prohibited.

Approach:
1. Count total A's and B's in the string.
2. For each maximal run of identical consecutive characters, compute how many length-2 blocks can be formed.
3. Use greedy strategy: prioritize using available 'ab' and 'ba' counts first before allocating 'A' or 'B'.
4. Optimize remaining slots to minimize resource usage for 'A' and 'B' strings.

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int T, n, a, b, c, d, cnta, cntb, cnt, trn, l, tmp;
char s[600000];
vector<int> vc, vd;
int main() {
  cin >> T;
  while (T--) {
    scanf("%s%d%d%d%d", s + 1, &a, &b, &c, &d); // Read string and limits
    vc.clear(), vd.clear(), cnta = cntb = cnt = 0, l = 1, n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
      if (s[i] == 'A')
        cnta++;
      else
        cntb++;
    }
    trn = max(cnta - a, cntb - b); // Extra A/B blocks we can't use
    for (int i = 1; i <= n; i++) {
      if (i == n || s[i] == s[i + 1]) { // End of block or same char as next
        tmp = (i - l + 1) / 2; // Length of current run divided by 2 for blocks
        if (tmp) {
          if (s[l] == s[i])
            cnt += tmp; // For runs of single chars like AAAA, count as single block
          else if (s[l] == 'A')
            vc.push_back(tmp); // Push to 'AB' groupings
          else
            vd.push_back(tmp); // Push to 'BA' groupings
        }
        l = i + 1; // Move start pointer to next char
      }
    }
    sort(vc.begin(), vc.end()); // Sort for greedy selection of minimal-length blocks
    sort(vd.begin(), vd.end());
    for (auto i : vc) {
      if (c < i) // If we can't fulfill 'AB' quota with remaining 'ab', reduce others
        cnt += i - 1;
      else
        trn -= i, c -= i; // Use up 'ab' and update surplus
    }
    for (auto i : vd) {
      if (d < i) // Similar for 'BA': compute how many extra we have
        trn -= d, i -= d, d = 0, cnt += i - 1;
      else
        trn -= i, d -= i; // Use up 'ba' quota and update surplus
    }
    if (trn <= min(c + d, cnt)) // Can we cover remaining deficit?
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/