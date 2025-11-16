// Problem: CF 2006 D - Iris and Adjacent Products
// https://codeforces.com/contest/2006/problem/D

/*
 * Problem: D. Iris and Adjacent Products
 * Algorithms/Techniques: Mo's Algorithm with square root decomposition for optimizing range queries
 * Time Complexity: O((n + q) * sqrt(n) * sqrt(k)) where n is the size of array and q is number of queries
 * Space Complexity: O(n + k)
 *
 * Task Description:
 * For each query subarray, we need to find minimum operations to make all adjacent products <= k.
 * Two types of operations allowed:
 * 1. Rearrange elements (no cost)
 * 2. Change value of an element to any integer from 1 to k (cost = 1 per operation)
 *
 * Approach:
 * - Square root decomposition with Mo's algorithm for efficient range query processing.
 * - Transforming values into a smaller range [1..sq] for optimization.
 * - Using frequency counting of transformed elements to compute how many pairs satisfy condition.
 */
#include <algorithm>
#include <cmath>
#include <iostream>

#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 1e5 + 5, B = 320;
int _, n, m, k, a[N], c[N], sq, o[N];
struct node {
  int i, l, r;
} b[N];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> _;
  while (_--) {
    cin >> n >> m >> k;
    sq = sqrt(k);
    sq = sq * 2 - (sq == k / sq); // Define effective range of transformed values
    for (int i = 1; i <= sq; i++)
      c[i] = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (a[i] > k / a[i]) // Transform large elements to small ones in the new domain
        a[i] = sq - k / a[i] + 1;
    }
    for (int i = 1; i <= m; i++)
      cin >> b[i].l >> b[i].r, b[i].i = i;
    sort(b + 1, b + m + 1, [](node x, node y) {
      return x.l / B == y.l / B ? (x.l / B & 1 ? x.r > y.r : x.r < y.r)
                                : x.l < y.l;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
      while (l > b[i].l)
        c[a[--l]]++; // Expand left boundary
      while (r < b[i].r)
        c[a[++r]]++; // Expand right boundary
      while (l < b[i].l)
        c[a[l++]]--; // Shrink left boundary
      while (r > b[i].r)
        c[a[r--]]--; // Shrink right boundary
      int ans = 0, sl = 0, sr = 0;
      for (int j = 1; j * 2 <= sq; j++) {
        sl = sl + c[j], sr = sr + c[sq - j + 1]; // Count elements contributing from both sides
        if (sr > sl) { // More larger elements than smaller ones in the current window?
          int x = (sr - sl + 1) / 2;
          if (((r - l + 1) & 1) && sl + sr == r - l + 1)
            x--; // Special handling for odd-length arrays
          sl += x, sr -= x, ans += x; // Adjust counts and increment answer if needed
        }
      }
      o[b[i].i] = ans;
    }
    for (int i = 1; i <= m; i++)
      cout << o[i] << " \n"[i == m];
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/