// Problem: CF 2139 E2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2139/problem/E2

/*
E2. Maple and Tree Beauty (Hard Version)
Algorithms/Techniques: Tree traversal, Dynamic Programming on subset sums, Bitset optimization

Time Complexity: O(n log n + n * sum of n across all test cases)
Space Complexity: O(n)

This problem involves finding the maximum "beauty" of a tree, which is defined as 
the length of the longest common subsequence (LCS) of names of all leaves. The name 
of each vertex is formed by concatenating labels from root to that vertex. Labels can 
be either 0 or 1, and we have exactly k zeros and n-k ones to place.

The solution uses dynamic programming with bitsets for efficient subset sum calculations.
Key steps:
1. Parse tree structure and compute depths and degrees
2. Identify leaf depths
3. Count how many vertices are at each depth level
4. Generate possible contribution values using binary decomposition technique
5. Use DP with bitset to find valid sums of label configurations
6. Determine maximum LCS by checking if we can achieve enough zeros in prefix

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
    deg[fa[i]]++;
    deg[i]++;
    dep[i] = dep[fa[i]] + 1;
    cnt[dep[i]]++;
  }
  int maxdep = *std::max_element(dep.begin(), dep.end());
  int leafdep = maxdep;
  for (int i = 2; i <= n; ++i) {
    if (deg[i] == 1) {
      leafdep = std::min(leafdep, dep[i]);
    }
  }
  std::vector<int> a;
  std::vector<int> num(n + 1);
  for (int i = 1; i <= leafdep; ++i) {
    num[cnt[i]]++;
  }
  for (int i = 1; i <= n; ++i) {
    if (num[i]) {
      int x = num[i];
      for (int p = 1; p <= x; p <<= 1) {
        a.push_back(p * i);
        x -= p;
      }
      if (x) {
        a.push_back(x * i);
      }
    }
  }
  std::bitset<200005> dp;
  dp[0] = 1;
  for (auto x : a) {
    dp |= dp << x;
  }
  int sum = std::accumulate(cnt.begin(), cnt.begin() + leafdep + 1, 0);
  int ans = leafdep - 1;
  for (int i = std::max(0, sum - (n - k)); i <= k; ++i) {
    if (dp.test(i)) {
      ans++;
      break;
    }
  }
  std::cout << ans << "\n";
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


// https://github.com/VaHiX/CodeForces/