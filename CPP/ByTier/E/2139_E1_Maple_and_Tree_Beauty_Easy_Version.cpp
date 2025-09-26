// Problem: CF 2139 E1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2139/problem/E1

/*
E1. Maple and Tree Beauty (Easy Version)
Algorithms/Techniques: DFS traversal, dynamic programming with bitset optimization, tree parsing

Time Complexity: O(n^2) per test case due to the DP step with bitset and nested loops.
Space Complexity: O(n) for storing tree structure, depth info, and hash table.

This solution attempts to maximize the beauty of a labeled tree by choosing how to assign 0s and 1s 
to vertices such that the length of the longest common subsequence (LCS) of names of all leaves is maximized.
It uses DFS to compute depths and structure. Then DP with bitset is used to efficiently track 
which numbers of zeros can be achieved, and finally checks which assignment gives valid LCS.

The approach:
- Build tree from parent information
- Perform DFS to calculate depth of each node and count leaf depths
- Use bitset-based DP for subset sum-like problem to determine possible zero counts
- For each valid distribution of zeros, compute minimum leaf depth (which affects LCS bound)
- Determine whether it's feasible to achieve the required number of zeros
- Return the answer accordingly
*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
int ans, dep[1005], hashh[1005]; // ans stores min depth found so far, dep[i] node depths, hashh[i] count of nodes at depth i
vector<int> son[1005]; // son[u] contains children of node u

void dfs(int u) { // DFS traversal to calculate node depths and find leaf depths
  for (auto v : son[u]) { // For each child
    dep[v] = dep[u] + 1; // Set depth of child
    dfs(v); // Recursively explore child
  }
  if (son[u].empty()) // If u is a leaf
    ans = min(ans, dep[u]); // Update minimum depth among leaves
  hashh[dep[u]]++; // Increment counter for nodes at this depth
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, k, cnt, flag;
  cin >> T;
  while (T--) {
    bitset<1005> dp; // DP bitset to track possible number of zeros
    dp.set(0); // Initially set 0 zero count as achievable
    cin >> n >> k;
    ans = n; 
    cnt = 0;
    flag = 0;
    for (int i = 0; i <= n; i++)
      hashh[i] = 0; // Reset hash table
    for (int i = 2, s; i <= n; i++) // Read parent of each node from 2 to n
      cin >> s, son[s].push_back(i); // Build tree structure
    dfs(1); // Start DFS from root (node 1)
    for (int i = 0; i <= n; i++) {
      if (dep[i] > ans) // Count nodes deeper than minimum leaf depth
        cnt++;
      if (i <= ans && hashh[i]) // If this depth is within min depth bound and has nodes
        dp |= dp << hashh[i]; // Update DP bitset with possible new zero counts
    }
    for (int i = 0; !flag && i <= n; i++) { // Check for valid k in range [0, k]
      if (dp.test(i) && k - i <= cnt && k - i >= 0) // Is a valid assignment of zeros?
        flag = 1; // Mark it as found
    }
    cout << (flag ? ans + 1 : ans) << "\n"; // Output result based on feasibility
    for (int i = 1; i <= n; i++)
      son[i].clear(); // Clear tree structure for next test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/