// Problem: CF 2003 E2 - Turtle and Inversions (Hard Version)
// https://codeforces.com/contest/2003/problem/E2

/*
E2. Turtle and Inversions (Hard Version)
Purpose:
  Given intervals [l_i, r_i], find the maximum number of inversions in a permutation such that for each interval,
  there exists a k_i in [l_i, r_i) where:
    a_i = max_{j=l_i}^{k_i} p_j
    b_i = min_{j=k_i+1}^{r_i} p_j
  And max_i(a_i) < min_i(b_i).

Algorithms/Techniques:
  - Difference array technique to count interval overlaps.
  - Greedy assignment of values based on constraints.
  - Sliding window approach to compute valid ranges.

Time Complexity:
  O(n + m) per test case, due to processing each element once and maintaining difference arrays.
Space Complexity:
  O(n) for storing the difference arrays and boolean flags.

*/
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 5e3 + 20;
int cnt_l[N], cnt_r[N], cnt[N]; // Difference arrays for interval coverage
bool must_l[N], must_r[N];     // Flags indicating if we need to maintain constraints at each point
int n, m;

// Check if there exists an edge between positions x and y such that
// some interval covers the segment (x, y)
inline bool has_esh(int x, int y) {
  if (x > y) {
    x += y;
    y = x - y;
    x = x - y;
  }
  return (cnt[x] - cnt_r[x] > 0);
}

// Get next valid position in direction d from index ind
inline int get_next(int ind, int d) {
  bool is_l = true;
  if (must_r[ind])
    is_l = false;
  while (true) {
    ind += d;
    if (ind > n || ind <= 0)
      return -1;
    if ((is_l && must_l[ind]) || (!is_l && must_r[ind]))
      break;
  }
  return ind;
}

inline void solve() {
  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    must_l[i] = must_r[i] = false;
    cnt_l[i] = cnt_r[i] = cnt[i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    cnt_l[l]++;
    cnt_r[r]++;
    must_l[l] = true;
    must_r[r] = true;
  }

  // Build the difference array to compute point coverage
  int cur = 0;
  for (int i = 1; i <= n; i++) {
    cur += cnt_l[i];
    cnt[i] = cur;
    cur -= cnt_r[i];
  }

  // Propagate must flags from left to right
  for (int i = 2; i <= n; i++) {
    if (has_esh(i - 1, i))
      must_r[i] |= must_r[i - 1];
  }

  // Propagate must flags from right to left
  for (int i = n - 1; i >= 1; i--) {
    if (has_esh(i, i + 1))
      must_l[i] |= must_l[i + 1];
  }

  // If any position is both must_l and must_r, impossible to construct permutation
  for (int i = 1; i <= n; i++) {
    if (must_l[i] && must_r[i]) {
      cout << -1 << '\n';
      return;
    }
  }

  // Start with total possible inversions: n*(n-1)/2
  ll ans = 1ll * n * (n - 1) / 2;

  int cur_r = n + 1, cur_l = 0;
  must_l[0] = must_r[n + 1] = true;
  must_r[0] = must_l[n + 1] = false;

  // Compute the minimum valid gaps to subtract from the total inversion count
  while (true) {
    cur_l = get_next(cur_l, 1), cur_r = get_next(cur_r, -1);
    if (min(cur_l, cur_r) == -1 || cur_l > cur_r)
      break;
    ans -= cur_r - cur_l; // Subtract the invalid pairs
  }
  cout << ans << '\n';
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int tt;
  cin >> tt;
  while (tt--)
    solve();
}


// https://github.com/VaHiX/codeForces/