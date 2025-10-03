// Problem: CF 2139 E2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2139/problem/E2

/*
E2. Maple and Tree Beauty (Hard Version)

Algorithms/Techniques: 
- Tree traversal and depth calculation
- Dynamic programming with bitset for subset sum optimization
- Greedy approach to distribute zeros/ones to maximize LCP of leaf names
- Binary search or direct check on possible subsequence lengths

Time Complexity: O(n * log n) per test case, dominated by the DP with bitset.
Space Complexity: O(n), for storing tree structure, depths, counts and DP array.

*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;

void solve() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> fa(n + 1);
  std::vector<int> deg(n + 1);
  std::vector<int> dep(n + 1);
  std::vector<int> cnt(n + 1);
  dep[1] = 1;
  for (int i = 2; i <= n; ++i) {
    std::cin >> fa[i];
    deg[fa[i]]++; // increment parent's degree
    deg[i]++;     // increment node's degree
    dep[i] = dep[fa[i]] + 1; // compute depth of node i
    cnt[dep[i]]++; // count nodes at each depth level
  }
  int maxdep = *std::max_element(dep.begin(), dep.end()); // maximum depth in tree
  int leafdep = maxdep;
  for (int i = 2; i <= n; ++i) {
    if (deg[i] == 1) { // if node is a leaf (only parent connected)
      leafdep = std::min(leafdep, dep[i]); // find the minimum depth among leaves
    }
  }

  std::vector<int> a; // for storing compressed weights for DP
  std::vector<int> num(n + 1);
  for (int i = 1; i <= leafdep; ++i) {
    num[cnt[i]]++; // count how many depths have same number of nodes
  }
  for (int i = 1; i <= n; ++i) {
    if (num[i]) { // if some depths have 'i' nodes, process them
      int x = num[i];
      for (int p = 1; p <= x; p <<= 1) { // binary decomposition of count
        a.push_back(p * i); // add decomposed weight
        x -= p;
      }
      if (x) {
        a.push_back(x * i); // remaining part after binary decomposition
      }
    }
  }

  std::bitset<200005> dp; // DP bitmask for subset sum
  dp[0] = 1; // initial state: zero sum possible
  for (auto x : a) {
    dp |= dp << x; // propagate all sums using current weight
  }
  
  int sum = std::accumulate(cnt.begin(), cnt.begin() + leafdep + 1, 0); 
  // total number of nodes up to the shallowest leaf level
  
  int ans = leafdep - 1; // base answer starts from previous level

  for (int i = std::max(0, sum - (n - k)); i <= k; ++i) {
    if (dp.test(i)) { // check if sum 'i' can be achieved
      ans++;
      break; // take first valid one since we want maximum beauty
    }
  }

  std::cout << ans << "\n"; // output result for current test case
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/