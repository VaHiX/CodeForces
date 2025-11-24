// Problem: CF 1701 E - Text Editor
// https://codeforces.com/contest/1701/problem/E

/*
Algorithm: Dynamic Programming + Sliding Window Approach
Purpose: Find minimum moves to transform string s into string t using editor operations.
Time Complexity: O(n * m) per test case, where n and m are lengths of strings s and t.
Space Complexity: O(n * m) for the dp table a[5005][5005].

The solution uses:
1. A 2D DP table to find longest common subsequence (LCS) in reverse.
2. Then it uses a sliding window approach to find the optimal position to start matching.
3. The answer is calculated considering the cost of:
   - Deleting unmatched characters from s
   - Moving cursor around
   - Matching characters from t

The key insight is that after finding the LCS, we compute how many operations 
are needed to place the cursor at the right position to match the current character of t.
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int T, n, m;
char s[5005], t[5005];
int a[5005][5005];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s%s", &n, &m, s + 1, t + 1); // Read inputs, 1-indexed
    // Initialize dp table
    for (int i = 1; i <= n + 1; i++)
      for (int j = 1; j <= m + 1; j++)
        a[i][j] = 0;
    // Compute LCS in reverse order (from end to start)
    for (int i = n; i >= 1; i--)
      for (int j = m; j >= 1; j--)
        if (s[i] == t[j])
          a[i][j] = a[i + 1][j + 1] + 1;
    // Calculate minimum moves: number of deletions plus optimal cursor position
    int ans = n - a[1][1], p = 1;
    for (int i = 1; i <= n; i++) {
      // Advance p if current character matches
      if (p <= n && s[i] == t[p])
        p++;
      // Try all possible positions for cursor to start matching
      for (int j = 0; j < p; j++)
        // Compute operations: deletions + cursor moves
        ans = min(ans, n - a[i + 1][j + 1] + i - j + 1);
    }
    // If not all characters of t were matched, impossible
    if (p <= m)
      ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/