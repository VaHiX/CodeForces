// Problem: CF 1748 E - Yet Another Array Counting Problem
// https://codeforces.com/contest/1748/problem/E

/*
Algorithm: Segment Tree with Dynamic Programming
Time Complexity: O(n * m)
Space Complexity: O(n * m)

The solution uses a segment tree-like approach with dynamic programming to count valid arrays b.
We build a tree where each node represents a segment and the leftmost maximum position.
The dp[x][i] represents number of ways to fill the segment ending at x such that the leftmost
maximum is at position i.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 200010, mod = 1e9 + 7;
int t, n, m, lc[N], rc[N], a[N], s[N], top;
vector<long long> dp[N];

// DFS to calculate dp values for each node in the tree
void dfs(int x) {
  if (lc[x])
    dfs(lc[x]);  // Process left child
  if (rc[x])
    dfs(rc[x]);  // Process right child
  // For each possible maximum value, calculate the number of valid arrays
  for (int i = 1; i <= m; i++) {
    // dp[x][i] = (dp[left][i-1] * dp[right][i] + dp[x][i-1]) % mod
    dp[x][i] = (dp[lc[x]][i - 1] * dp[rc[x]][i] % mod + dp[x][i - 1]) % mod;
  }
}

void solve() {
  cin >> n >> m;
  dp[0].resize(m + 1);  // Initialize base case
  for (int i = 0; i <= m; i++)
    dp[0][i] = 1;
  top = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    dp[i].resize(m + 1);
    dp[i][0] = 0;  // No way to have maximum 0
    lc[i] = rc[i] = 0;  // Reset children pointers
    // Maintain monotonic stack to build the tree structure
    while (top && a[i] > a[s[top]]) {
      lc[i] = s[top--];  // Build left child links
    }
    if (top) {
      rc[s[top]] = i;  // Set right child of previous element
    }
    s[++top] = i;  // Push current index to stack
  }
  dfs(s[1]);  // Start DFS from root (the maximum element in stack)
  cout << dp[s[1]][m] << endl;  // Output the final answer
}

int main() {
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/