// Problem: CF 1771 D - Hossam and (sub-)palindromic tree
// https://codeforces.com/contest/1771/problem/D

/*
 * Problem: Hossam and (sub-)palindromic tree
 * 
 * Purpose: Given a tree with labeled vertices, find the length of the longest 
 *          maximal sub-palindrome among all possible paths from any vertex v to u.
 *          A sub-palindrome is a subsequence that is a palindrome.
 * 
 * Approach:
 * - For each leaf node, perform DFS to traverse downward and build up the path string.
 * - Use dynamic programming to compute the longest palindromic subsequence (LPS) 
 *   for each prefix of the path from a leaf to root.
 * - The DP state dp[l][r] represents the length of the longest palindromic 
 *   subsequence in the substring from index l to r (1-indexed).
 * - For each leaf, we update the maximum LPS found so far.
 * 
 * Time Complexity: O(n^3) in worst case, due to nested loops over all paths from leaves.
 * Space Complexity: O(n^2) for the DP table and recursion stack.
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int ans, dp[2005][2005], last;
char s[2005], a[2005];
vector<int> g[2005];

// DFS to traverse from a leaf node upward, building path and computing LPS
void dfs(int x, int fa, int dep) {
  a[dep] = s[x]; // Store current character in path buffer

  // If current node is a leaf (only one neighbor)
  if (g[x].size() == 1) {
    // Initialize DP table for current path prefix
    for (int i = last + 1; i <= dep; i++)
      dp[i][i] = 1; // Single character is a palindrome of length 1
    
    // Fill DP table for all substrings in current path
    for (int len = 2; len <= dep; len++)
      for (int l = max(1, last - len + 2); l + len - 1 <= dep; l++) {
        int r = l + len - 1;
        // Start with max of excluding left or right character
        dp[l][r] = max(dp[l][r - 1], dp[l + 1][r]);
        
        // If characters match, add 2 to inner palindrome length
        if (a[l] == a[r])
          dp[l][r] = max(dp[l][r], dp[l + 1][r - 1] + 2);
      }
    
    // Update global answer with maximum found so far
    ans = max(ans, dp[1][dep]);
  }

  // Continue DFS to neighbors except parent
  for (int v : g[x])
    if (v != fa)
      dfs(v, x, dep + 1), last = dep;
}

int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%s", &n, s + 1); // Read tree size and node labels
    ans = 0, last = 0;

    // Reset adjacency list for this test case
    for (int i = 1; i <= n; i++)
      g[i].clear();

    // Read edges and construct adjacency list
    for (int i = 1, u, v; i < n; i++) {
      scanf("%d%d", &u, &v);
      g[u].push_back(v);
      g[v].push_back(u);
    }

    // Start DFS from all leaf nodes
    for (int i = 1; i <= n; i++)
      if (g[i].size() == 1)
        dfs(i, 0, 1);

    // Handle special case of single node
    printf("%d\n", n == 1 ? 1 : ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/