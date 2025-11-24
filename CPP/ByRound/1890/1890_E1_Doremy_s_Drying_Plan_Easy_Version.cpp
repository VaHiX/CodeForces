// Problem: CF 1890 E1 - Doremy's Drying Plan (Easy Version)
// https://codeforces.com/contest/1890/problem/E1

/*
 * Code Purpose: 
 *   This solution computes the maximum number of dry cities Doremy can achieve 
 *   by preventing rain on exactly k=2 days in a country with n cities and m days of rain.
 * 
 * Algorithm:
 *   1. For each day, record which cities are affected by rain.
 *   2. Track for each city: which days it is rained on (up to 3 days max due to k=2).
 *   3. Determine how many cities are dry if no rain is prevented (baseline).
 *   4. Optimize by considering which pair of days to prevent to maximize dry cities:
 *       - Single day removal: Find the day that covers the most cities.
 *       - Pair of days removal: Check combinations or overlapping intervals that cover
 *         the same cities and compute max overlap.
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <iostream>

using namespace std;
#define PII pair<int, int>
#define ll long long
#define fi first
#define se second
const int inf = 0x3f3f3f3f;
const int N = 2e5 + 2;
const int MOD = 1e9 + 7;

// Node to store the rain days for a city: a, b, c represent the 1st, 2nd, 3rd day it rains
struct node {
  int a, b, c;
} t[N];

int n, m, k;
int cnt[N]; // Count of cities covered by each day of rain
int ne[N];  // Union-find for interval merging

// Recursive function to mark segments with rain day number
int dfs(int l, int r, int val) {
  if (l > r)
    return r;
  if (ne[l] != l) {
    return ne[l] = dfs(ne[l], r, val);
  }
  if (t[l].a == 0) {
    t[l].a = val;
    dfs(l + 1, r, val);
  } else if (t[l].b == 0) {
    t[l].b = val;
    dfs(l + 1, r, val);
  } else {
    t[l].c = val;
    ne[l] = dfs(l + 1, r, val);
  }
  return ne[l];
}

void solve() {
  cin >> n >> m >> k;
  // Initialize structures
  for (int i = 1; i <= n; i++)
    ne[i] = i, t[i].a = t[i].b = t[i].c = 0;
  for (int i = 1; i <= m; i++) {
    int l, r;
    cin >> l >> r;
    dfs(l, r, i);
    cnt[i] = 0;
  }

  int ans = 0;
  // Count cities which are dry if no days are prevented
  for (int i = 1; i <= n; i++) {
    if (t[i].b == 0 && t[i].c == 0) {
      if (t[i].a == 0)
        ans++; // City is dry because never rained
      else
        cnt[t[i].a]++; // City is rained once, counted towards that day
    }
  }

  int ret, mx1 = 0, mx2 = 0;
  // Find maximum and second maximum number of cities covered by one day
  for (int i = 1; i <= m; i++)
    if (cnt[i] > mx1) {
      mx2 = mx1;
      mx1 = cnt[i];
    } else if (cnt[i] > mx2) {
      mx2 = cnt[i];
    }
  ret = mx1 + mx2;  // Best single-day removal + best other-day

  // Check all possible pairs of days that can be removed to gain more cities
  for (int i = 1; i <= n; i++) {
    if (t[i].a != 0 && t[i].b != 0 && t[i].c == 0) {
      int sum = 1; // Count of cities in interval
      int a = t[i].a, b = t[i].b; // Days that rained on this city
      // Extend while same pair of days rain the same city
      while (i + 1 <= n && ((t[i + 1].a == a && t[i + 1].b == b) || t[i + 1].c)) {
        i++;
        if (!t[i].c)
          sum++;
      }
      ret = max(ret, sum + cnt[a] + cnt[b]); // Total potential dry cities
    }
  }

  ans += ret;
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/