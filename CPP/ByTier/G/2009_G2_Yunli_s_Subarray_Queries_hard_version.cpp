// Problem: CF 2009 G2 - Yunli's Subarray Queries (hard version)
// https://codeforces.com/contest/2009/problem/G2

/*
G2. Yunli's Subarray Queries (hard version)
Algorithms/Techniques: Sliding window, monotonic stack, binary search
Time Complexity: O(n + q)
Space Complexity: O(n)

This problem uses a sliding window technique to compute the minimum number of operations needed
to form a consecutive subarray of length k for all prefixes of the array. Then, it answers queries
by using a monotonic stack and prefix sums to efficiently compute range sums.
*/

#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#define for0(i, n) for (i = 0; i < (n); i++)
#define for1(i, n) for (i = 1; i <= (n); i++)
#define forlr(i, l, r) for (i = (l); i <= (r); i++)
using namespace std;
typedef long long ll;
const int N = 400010;
int T, n, k, q, a[N], dp[N], t[N], pos;
int st[N], top, r[N];
ll sum[N], ans[N], g[N];
vector<int> v[N];

int main() {
  int i, x, y, z;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &k, &q);
    for1(i, n) scanf("%d", &a[i]);
    pos = 0;
    t[0] = n;
    top = 0;
    for1(i, 2 * n + 1) {
      dp[i] = 0;
      t[i] = 0;
      g[i] = 0;
      v[i].clear();
    }
    for1(i, n) {
      if (i > k) {
        // Remove the contribution of element going out of window
        t[dp[a[i - k] + n - i + k]]--;
        dp[a[i - k] + n - i + k]--;
        t[dp[a[i - k] + n - i + k]]++;
      }
      // Add contribution of new element entering window
      t[dp[a[i] + n - i]]--;
      dp[a[i] + n - i]++;
      t[dp[a[i] + n - i]]++;
      pos++;
      while (!t[pos])
        pos--;
      g[i] = k - pos;
    }
    for1(i, q) {
      scanf("%d%d", &x, &r[i]);
      v[x + k - 1].push_back(i);
    }
    st[0] = n + 1;
    g[n + 1] = -1;
    for (i = n; i >= k; i--) {
      while (g[i] <= g[st[top]])
        top--;
      sum[top + 1] = (st[top] - i) * g[i] + sum[top];
      st[++top] = i;
      for (int tem : v[i]) {
        y = r[tem];
        z = lower_bound(st, st + top + 1, y + 1, greater<int>()) - st;
        if (!z)
          ans[tem] = sum[top];
        else
          ans[tem] = sum[top] - (st[z - 1] - y - 1) * g[st[z]] - sum[z - 1];
      }
    }
    for1(i, q) printf("%lld\n", ans[i]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/