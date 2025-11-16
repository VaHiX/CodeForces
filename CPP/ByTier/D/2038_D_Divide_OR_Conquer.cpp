// Problem: CF 2038 D - Divide OR Conquer
// https://codeforces.com/contest/2038/problem/D

/*
D. Divide OR Conquer
Algorithms/Techniques: 
- Sparse Table for Range Bitwise OR queries
- Dynamic Programming with Memoization on segments
- Binary Search to find valid segment boundaries

Time Complexity: O(n log n)
Space Complexity: O(n log n)

Given an array of integers, count the number of ways to split it into contiguous segments such that the bitwise OR of each segment is non-decreasing.
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define rep(i, l, r) for (int i = l, _ = r; i <= _; ++i)
#define per(i, r, l) for (int i = r, _ = l; i >= _; --i)
#define iter(x, v) for (int _p = head[x], v; v = ver[_p], _p; _p = nxt[_p])
#define ll long long
#define lowbit(x) ((x) & -(x))
template <typename T> inline void chkmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> inline void chkmax(T &x, T y) { x = x > y ? x : y; }
const int mod = 998244353;
int n, a[200010], g[200010][21], lo[200010], f[200010][32];
vector<int> v[200010];

// Sparse table query for range OR
inline int query(int l, int r) {
  int now = lo[r - l + 1];
  return g[l][now] | g[r - (1 << now) + 1][now];
}

// Binary search to find the first index where value >= val in sorted vector v[id]
inline int ID(int id, int val) {
  int l = 0, r = (int)v[id].size() - 1, ans = -1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (v[id][mid] >= val)
      ans = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  rep(i, 1, n) cin >> a[i], g[i][0] = a[i]; // Initialize sparse table with original values

  rep(i, 2, n) lo[i] = lo[i >> 1] + 1; // Precompute log values for sparse table

  rep(i, 1, lo[n]) per(j, n, 1) 
    g[j][i] = g[j][i - 1] | g[min(j + (1 << (i - 1)), n)][i - 1]; // Build sparse table for range OR queries

  rep(i, 1, n) {
    v[i].push_back(a[i]); // Start new vector with current element
    int pre = a[i];
    rep(j, 0, (int)v[i - 1].size() - 1) { // Generate all possible OR values from previous state
      int now = v[i - 1][j] | a[i]; // Merge current element with previous OR value
      if (now != pre)
        pre = now, v[i].push_back(now); // Add new OR value if it's different
    }
  }

  f[1][0] = 1; // Initialization of DP with first element

  rep(i, 1, n) rep(j, 0, (int)v[i].size() - 1) if (f[i][j]) { // Traverse through all segments and OR values
    int val = v[i][j]; 
    if (i < n) // Extend current segment to next element and update DP state
      (f[i + 1][ID(i + 1, val | a[i + 1])] += f[i][j]) %= mod;
    
    int l = i + 1, r = n, ans = n + 1; 
    // Binary search to find the leftmost index that satisfies query constraint
    while (l <= r) {
      int mid = l + r >> 1;
      if (query(i + 1, mid) >= val)
        ans = mid, r = mid - 1;
      else
        l = mid + 1;
    }
    if (ans <= n) // Update dp for valid segment ending at 'ans'
      (f[ans][ID(ans, query(i + 1, ans))] += f[i][j]) %= mod;
  }

  ll tot = 0;
  rep(i, 0, (int)v[n].size() - 1) tot += f[n][i]; // Sum up all valid ways to split the entire array
  cout << tot % mod << '\n';
  cout << flush;
  return 0;
}


// https://github.com/VaHiX/codeForces/