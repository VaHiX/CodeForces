// Problem: CF 1956 D - Nene and the Mex Operator
// https://codeforces.com/contest/1956/problem/D

/*
Algorithm: Dynamic Programming with Memoization + Greedy Construction
Techniques: 
- Divide and Conquer using DP
- MEX (Minimum Excluded) concept
- Optimal substructure: split interval and solve recursively

Time Complexity: O(N^3) where N <= 18
Space Complexity: O(N^2) for DP table and auxiliary arrays

The key insight is to determine the optimal way to split the array into subsegments such that applying MEX operation on them maximizes the sum.
We use a recursive DP approach where dp[l][r] represents the maximum possible sum for subarray [l, r].
For each segment, we either:
1. Apply MEX operation on the whole segment (this gives us MEX * length)
2. Split into two parts and solve recursively

After computing the optimal DP solution, we reconstruct the operations using the parent pointers.
*/

#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
#define pb push_back
#define mp make_pair
#define f1 first
#define s2 second
#define fastio                                                                 \
  ios ::sync_with_stdio(0);                                                    \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define debug(x) cerr << "[" << #x << "]: " << x << "\n";
using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using pl = pair<ll, ll>;
const ld PI = 4 * atan((ld)1);
const int MAX = 20;
int N;
int ar[MAX];
int dp[MAX][MAX];
int par[MAX][MAX];
int solve(int l, int r) {
  if (dp[l][r] != -1)
    return dp[l][r];
  // Initialize with sum of current segment
  dp[l][r] = accumulate(ar + l, ar + r + 1, 0);
  if ((r - l + 1) * (r - l + 1) > dp[l][r])
    dp[l][r] = (r - l + 1) * (r - l + 1), par[l][r] = 0;
  for (int i = l; i <= r; ++i) {
    int tmp = solve(l, i) + solve(i + 1, r);
    if (tmp > dp[l][r])
      dp[l][r] = tmp, par[l][r] = i;
  }
  return dp[l][r];
}
vector<ii> ops;
void construct(int l, int r) {
  // Convert all elements to 0 first to be able to apply MEX properly later
  for (int i = l; i <= r; ++i)
    if (ar[i])
      ops.pb({i, i}), ar[i] = 0;
  int t = r - l + 1;
  for (int i = t - 1; i >= 1; --i)
    construct(l, l + i - 1);
  ops.pb({l, r});
  for (int i = l; i <= r; ++i)
    ar[i] = t;
}
void getOps(int l, int r) {
  if (par[l][r] == -1)
    return;
  if (par[l][r] == 0) {
    construct(l, r);
    return;
  }
  getOps(l, par[l][r]);
  getOps(par[l][r] + 1, r);
}
void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> ar[i];
  memset(dp, -1, sizeof(dp));
  memset(par, -1, sizeof(par));
  cout << solve(1, N) << '\n';
  getOps(1, N);
  cout << ops.size() << '\n';
  for (auto [l, r] : ops)
    cout << l << " " << r << '\n';
}
int main() {
  fastio;
  int TC = 1;
  while (TC--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/