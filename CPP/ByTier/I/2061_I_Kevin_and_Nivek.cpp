// Problem: CF 2061 I - Kevin and Nivek
// https://codeforces.com/contest/2061/problem/I

/*
Code Purpose:
This code solves the problem of finding the minimum time required for Kevin to win at least k matches out of n matches,
where each match is either of Type 1 (requires spending time a[i]) or Type 2 (depends on historical records).
It uses a divide-and-conquer approach with dynamic programming and preprocessing of prefix sums for optimization.

Algorithms/Techniques:
- Divide and Conquer DP
- Convex Hull Trick (simplified version)
- Prefix Sums
- Segment Tree / Range Query Optimization

Time Complexity: O(n log^2 n) per test case
Space Complexity: O(n) for auxiliary arrays and recursion stack
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
typedef long long ll;
const int maxn = 300005;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int T, n, p[maxn];
ll dp[maxn], buf[maxn], gg[maxn];

// Function to compute the valid range for index l and length r
pair<int, int> gq(int l, int r) {
  return make_pair(max(0, l - (r - 1) / 2), min(l, (r - 1) / 2));
}

// Optimized recursive function to update dp values by dividing the problem space
void efz(int l, int r, int x, int tl, int tr, int gc) {
  if (l > r || tl > tr)
    return;
  int mid = l + r >> 1, cd = 0; // Midpoint and best index
  ll mn = inf;
  for (int i = max(tl, mid - gc); i <= min(tr, mid); ++i) {
    ll tmp = buf[i] + gg[mid - i]; // Compute the minimum value considering current segment
    if (mn > tmp)
      mn = tmp, cd = i;
  }
  dp[mid + x] = min(dp[mid + x], mn); // Update the dp with new minimum
  efz(l, mid - 1, x, tl, cd, gc);     // Recursively solve left side
  efz(mid + 1, r, x, cd, tr, gc);     // Recursively solve right side
}

// Main DP solver that divides the array and computes optimal times
void solve(int l, int r) {
  int cl = gq(l, r).first, cr = gq(l, r).second; // Compute valid range for current segment
  if (l + 1 == r) {
    if (p[r] == -1)
      dp[cl + 1] = min(dp[cl + 1], dp[cl]); // If match is type 2, no time spent needed
    else
      dp[cl + 1] = min(dp[cl + 1], dp[cl] + p[r]); // If match is type 1, add time cost
    return;
  }
  vector<ll> vc; // Vector to store current dp values
  int mid = l + r >> 1;
  for (int i = cl; i <= cr; ++i)
    vc.push_back(dp[i]); // Populate with earlier computed values

  solve(l, mid); // Recurse on left half

  int cnt = 0, cm = 0;
  for (int i = l + 1; i <= mid; ++i) {
    if (p[i] >= 0)
      gg[++cnt] = p[i]; // Store positive cost for prefix sum
    else
      ++cm; // Count negative (type 2 match costs)
  }
  sort(gg + 1, gg + cnt + 1); // Sort the costs for efficient querying later
  for (int i = 2; i <= cnt; ++i)
    gg[i] += gg[i - 1]; // Build prefix sum

  int tul = gq(l, mid).first, tur = gq(l, mid).second;
  for (int i = cl; i <= cr; ++i)
    buf[i] = vc[i - cl]; // Copy previous dp values into buffer
  efz(cl, tul - 1 + cnt, 0, cl, tul - 1, cnt); // Apply update on left part
  efz(tur + 1, cr + cnt, cm, tur + 1, cr, cnt); // Apply update on right part

  vc.clear();
  for (int i = cl; i <= cr + mid - l; ++i)
    vc.push_back(dp[i]); // Re-populate vector with updated values

  solve(mid, r); // Recurse on right half
  cnt = cm = 0;
  for (int i = mid + 1; i <= r; ++i) {
    if (p[i] >= 0)
      gg[++cnt] = p[i]; // Store positive costs
    else
      ++cm; // Count negative costs again
  }
  sort(gg + 1, gg + cnt + 1); // Sort prefix sum again
  for (int i = 2; i <= cnt; ++i)
    gg[i] += gg[i - 1];

  tul = gq(mid, r).first, tur = gq(mid, r).second;
  for (int i = cl; i <= cr + mid - l; ++i)
    buf[i] = vc[i - cl]; // Copy again after further recursion step
  efz(cl, tul - 1 + cnt, 0, cl, tul - 1, cnt);
  efz(tur + 1, cr + mid - l + cnt, cm, tur + 1, cr + mid - l, cnt);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> p[i], dp[i] = inf; // Initialize all dp entries to infinity
    solve(0, n);       // Start solving from full range
    for (int i = 0; i <= n; ++i) // Output results
      cout << dp[i] << ' ';
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/