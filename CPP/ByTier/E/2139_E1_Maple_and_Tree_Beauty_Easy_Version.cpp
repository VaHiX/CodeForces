// Problem: CF 2139 E1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2139/problem/E1

/*
E1. Maple and Tree Beauty (Easy Version)

Purpose:
This code solves the problem of finding the maximum "beauty" of a labeled rooted tree,
where beauty is defined as the length of the longest common subsequence (LCS) of all leaf node names.
Each node is labeled with either 0 or 1, such that there are exactly k zeros and n-k ones.
The solution uses DFS to traverse the tree, computes depths of nodes,
and employs dynamic programming with bitsets to determine valid labelings.

Algorithms:
- Tree traversal using DFS
- Dynamic Programming with Bitset optimization for subset sum-like problem
- Greedy or optimal assignment strategy using depth information

Time Complexity: O(n^2)
Space Complexity: O(n)

*/
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
int ans, dep[1005], hashh[1005];  // ans: answer, dep: depth of each node, hashh: frequency count of depths
vector<int> son[1005];  // son[u]: list of children of node u

void dfs(int u) {
  for (auto v : son[u]) {  // traverse all children of u
    dep[v] = dep[u] + 1;   // set depth of child v
    dfs(v);                // recursively call dfs on child
  }
  if (son[u].empty())      // if node u is a leaf
    ans = min(ans, dep[u]);  // update minimal depth among leaves (used for initial computation)
  hashh[dep[u]]++;         // increment count of nodes at this depth level
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, k, cnt, flag;
  cin >> T;
  while (T--) {
    bitset<1005> dp;   // dp[i] indicates whether sum i is achievable
    dp.set(0);         // base case: sum 0 is achievable
    cin >> n >> k;
    ans = n;
    cnt = 0;
    flag = 0;
    for (int i = 0; i <= n; i++)
      hashh[i] = 0;    // reset array to 0
    for (int i = 2, s; i <= n; i++)
      cin >> s, son[s].push_back(i);  // build the tree structure from parent info
    dfs(1);            // start DFS from root (node 1)
    for (int i = 0; i <= n; i++) {
      if (dep[i] > ans)   // count how many nodes have depth above min leaf depth
        cnt++;
      if (i <= ans && hashh[i])   // if valid depth and there's at least one node at that level
        dp |= dp << hashh[i];     // update dp with new possible sums (bitwise OR with shifted version)
    }
    for (int i = 0; !flag && i <= n; i++) {  // look for valid k in range [0, n]
      if (dp.test(i) && k - i <= cnt && k - i >= 0)  // check if sum i is possible and complement k-i fits
        flag = 1;    // found a valid assignment
    }
    cout << (flag ? ans + 1 : ans) << "\n";  // output according to condition
    for (int i = 1; i <= n; i++)
      son[i].clear();   // clear children list for next test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/