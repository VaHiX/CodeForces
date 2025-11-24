// Problem: CF 2161 D - Locked Out
// https://codeforces.com/contest/2161/problem/D

/*
Purpose: This code solves the problem of finding the minimum number of elements to remove from an array to make it "good".
         An array is good if there do not exist indices i < j such that a[j] - a[i] = 1.
         The approach uses dynamic programming with sorting and binary search to efficiently compute the longest subsequence
         that avoids consecutive elements, and then subtracts it from total length.

Algorithms/Techniques:
- Sorting and custom comparator to order elements by value and then by position.
- Dynamic Programming with state transition based on previous valid elements.
- Binary search to efficiently find positions in sorted array.
- Prefix maximum tracking for DP states.

Time Complexity: O(n log n) per test case due to sorting and binary search operations.
Space Complexity: O(n) for auxiliary arrays and vectors.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define FOR(i, j, k) for (int i = j; i <= k; ++i)
#define ROF(i, j, k) for (int i = j; i >= k; --i)
#define pc putchar
#define fi first
#define se second
#define emp emplace_back
#define ll long long
template <typename T> void rd(T &x) {
  bool flag = 0;
  char c = getchar();
  for (; c < '0' || '9' < c; flag |= (c == '-'), c = getchar())
    ;
  for (x = 0; '0' <= c && c <= '9';
       x = (x << 3) + (x << 1) + (c ^ 48), c = getchar())
    ;
  x = (flag) ? (-x) : x;
}
template <typename T> void pr(T x) {
  if (x > 9)
    pr(x / 10);
  putchar(x % 10 + '0');
}
template <typename T> void write(T x) { pr(x), pc(' '); }
template <typename T> void writen(T x) { pr(x), pc('\n'); }
const int N = 3e5 + 10;
int n, a[N];
struct node {
  int val, pos;
  bool operator<(const node &tt) const {
    if (val != tt.val)
      return val < tt.val;
    return pos > tt.pos;
  }
};
int R[N];
int dp[N], pre[N];
bool qwq[N];
void solve() {
  rd(n);
  FOR(i, 1, n) dp[i] = pre[i] = 0;
  vector<node> vec(n + 1);
  FOR(i, 1, n) rd(a[i]), vec[i] = node{a[i], i};
  sort(vec.begin(), vec.end());
  FOR(i, 1, n) R[i] = qwq[i] = 0;
  FOR(i, 1, n) R[vec[i].val] = i, qwq[vec[i].val] = 1;
  FOR(i, 1, n) if (!R[i]) R[i] = R[i - 1];
  FOR(i, 1, n) {
    // Compute current dp[i] based on dp of elements at val-2
    dp[i] = pre[R[vec[i].val - 2]] + 1;
    // Check if there exists a previous element with value val-1
    if (qwq[vec[i].val - 1]) {
      int l = R[vec[i].val - 2], r = R[vec[i].val - 1], pos = l;
      ++l;
      while (l <= r) {
        int mid = l + r >> 1;
        // Find the rightmost element with value val-1 that has position greater than current
        if (vec[mid].pos > vec[i].pos)
          pos = mid, l = mid + 1;
        else
          r = mid - 1;
      }
      dp[i] = max(dp[i], pre[pos] + 1);
    }
    // If previous element is same value, we can extend the sequence
    if (vec[i - 1].val == vec[i].val)
      dp[i] = max(dp[i], dp[i - 1] + 1);
    // Update prefix maximum
    pre[i] = max(pre[i - 1], dp[i]);
  }
  int ans = 0;
  FOR(i, 1, n) ans = max(ans, dp[i]);
  writen(n - ans);
}
signed main() {
#ifdef LOCAL
  freopen("1.in", "r", stdin);
#endif
  int T;
  rd(T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/