// Problem: CF 2138 C1 - Maple and Tree Beauty (Easy Version)
// https://codeforces.com/contest/2138/problem/C1

/*
Problem: C1. Maple and Tree Beauty (Easy Version)
Algorithms/Techniques: Tree traversal, dynamic programming with bitset optimization, greedy packing of items into knapsack-like problem.

Time Complexity: O(n * log n) per test case due to sorting and bitset operations.
Space Complexity: O(n) for storing tree structure, depth counts, and bitset.

This code determines the maximum beauty (longest common subsequence length of names of all leaves)
of a rooted tree with k zeros and n-k ones assigned optimally to vertices.
It uses dynamic programming with bitset to efficiently compute possible sums,
and tries to find an assignment of k zeros that maximizes the LCS of leaf names.
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
bitset<200005> dp; // bitset for dynamic programming to track possible sums of counts
vector<int> q, p;  // q stores sorted depth counts; p stores packed weights for knapsack DP

void Solve() {
  cin >> n >> k;
  dp.reset(); // reset the dp bitset to all zeros
  for (int i = 1; i <= n; i++)
    sum[i] = cnt[i] = 0;
  dep[1] = 1;
  cnt[1] = 1;
  for (int i = 2, f; i <= n; i++) {
    cin >> f;
    dep[i] = dep[f] + 1;   // compute depth of each node
    cnt[dep[i]]++;         // count nodes at each depth level
    sum[f]++;              // track number of children for each node
  }
  D = n;
  for (int i = 1; i <= n; i++)
    if (!sum[i])
      D = min(D, dep[i]); // find minimum depth among leaves

  q.clear();
  p.clear();
  for (int i = 1; i <= D; i++)
    q.push_back(cnt[i]);
  sort(q.begin(), q.end()); // sort counts by depth levels ascending

  // Pack items greedily using binary decomposition to optimize subset sum DP
  for (int i = 0; i < q.size(); i++) {
    int j = i;
    while (j < q.size() && q[j] == q[i])
      j++;
    j--;
    int t = j - i + 1; // number of items with same count
    for (int z = 1; z <= t; z <<= 1) { // use powers of two to efficiently pack the group
      p.push_back(z * q[i]);
      t -= z;
    }
    if (t)
      p.push_back(t * q[i]);
    i = j;
  }

  dp[0] = 1; // base case for DP: we can form sum of 0 with nothing
  res = 0;
  for (auto x : p) { // iterate over packed item weights and update dp
    res += x;
    dp |= (dp << x); // bitshift to simulate addition of new values in dp
  }

  if (res <= k || res <= n - k) {
    cout << D << endl; // can assign all zeros or ones to get required distribution
    return;
  }

  for (int i = 0; i <= res; i++)
    if (dp[i] && i <= k && res - i <= n - k) { // check if a valid split exists
      cout << D << endl;
      return;
    }
  cout << D - 1 << endl; // default to one less if we can't do better
  return;
}


// https://github.com/VaHiX/codeForces/