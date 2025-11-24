// Problem: CF 2138 C1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2138/problem/C1

/*
C1. Maple and Tree Beauty (Easy Version)
Algorithms/Techniques: Tree traversal, Dynamic Programming with bitset optimization, Binary search on answer, Subset sum optimization using binary representation

Time Complexity: O(n log n + n * k) where n is the number of nodes and k is the number of zeros.
Space Complexity: O(n) for storing tree structure, depth, cnt arrays and bitset DP.

This problem involves finding the maximum beauty of a labeled rooted tree,
where beauty is defined as the length of the longest common subsequence
of all leaf names. The solution uses dynamic programming with bitset optimization
to efficiently check if there exists a subset of depths that can form valid
labeled configurations.
*/
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
#define endl '\n'
void init();
void Solve();
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  init();
  cin >> T;
  while (T--)
    Solve();
  return 0;
}
void init() {}
int n, k, dep[200005], cnt[200005], sum[200005], D, res;
bitset<200005> dp;
vector<int> q, p;
void Solve() {
  cin >> n >> k;
  dp.reset(); // Reset the bitset for DP
  for (int i = 1; i <= n; i++)
    sum[i] = cnt[i] = 0;
  dep[1] = 1; 
  cnt[1] = 1;
  for (int i = 2, f; i <= n; i++) {
    cin >> f;
    dep[i] = dep[f] + 1;
    cnt[dep[i]]++; // Count nodes at each depth
    sum[f]++;
  }
  D = n; // Initialize minimum depth to maximum possible value
  for (int i = 1; i <= n; i++)
    if (!sum[i])
      D = min(D, dep[i]); // Find the smallest depth of a leaf
  
  q.clear(); // Store unique counts of depths
  p.clear(); // Store optimized values for subset DP
  for (int i = 1; i <= D; i++)
    q.push_back(cnt[i]);
  sort(q.begin(), q.end());
  for (int i = 0; i < q.size(); i++) {
    int j = i;
    while (j < q.size() && q[j] == q[i])
      j++;
    j--; // Count how many elements in the group
    int t = j - i + 1; // Count of same values
    for (int z = 1; z <= t; z <<= 1) {
      p.push_back(z * q[i]); // Use binary representation to split into powers of two
      t -= z;
    }
    if (t)
      p.push_back(t * q[i]);
    i = j; // Move the index forward after processing this group
  }
  dp[0] = 1; // Base case for subset sum - sum 0 is achievable
  res = 0;
  for (auto x : p) {
    res += x;
    dp |= (dp << x); // Update bitset to reflect new possible sums
  }
  if (res <= k || res <= n - k) { // Early termination: if all zeros or all ones can be distributed
    cout << D << endl;
    return;
  }
  for (int i = 0; i <= res; i++)
    if (dp[i] && i <= k && res - i <= n - k) { // Check if there's valid splitting of zeros and ones
      cout << D << endl;
      return;
    }
  cout << D - 1 << endl; // If no valid distribution, reduce the answer by one level
  return;
}


// https://github.com/VaHiX/CodeForces/