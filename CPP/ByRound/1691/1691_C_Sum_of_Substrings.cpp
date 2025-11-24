// Problem: CF 1691 C - Sum of Substrings
// https://codeforces.com/contest/1691/problem/C

/*
 * Problem: C. Sum of Substrings
 * 
 * Algorithm/Technique:
 * - Greedily minimize the sum of adjacent digit pairs by moving '1's to the left to reduce the value of substrings.
 * - For a binary string, we compute the sum of all adjacent 2-digit numbers (treated as base-10).
 * - To minimize f(s), prioritize placing '1's as far left as possible to reduce the contribution of high-value substrings.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(n) for storing positions of '1's.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 1e5 + 10;
int t, n, k, cnt, ans, v[N];
char s[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%s", &n, &k, s);
    cnt = 0; // Reset counter for positions of '1'
    for (int i = 0; i < n; i++)
      if (s[i] == '1')
        v[++cnt] = i; // Store positions of all '1's
    
    ans = cnt * 11; // Base value if all pairs are "11" (11 + 11 + ... = 11 * count of 1s)

    // If we can move the rightmost '1' to the left (to reduce the value of its pair),
    // check if we have enough operations and update accordingly
    if (cnt && k >= n - 1 - v[cnt])
      k -= n - 1 - v[cnt--], ans -= 10; // Move rightmost '1', reduce its contribution by 10 (from 11 to 1)

    // If we can move the leftmost '1' even further left (to reduce contribution of its pair),
    // check again and adjust
    if (cnt && k >= v[1])
      ans--; // Reduce contribution by 1 (from 11 to 10 or 01, if pair contains 1)

    printf("%d\n", ans);
    cnt = ans = 0; // Reset for next test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/