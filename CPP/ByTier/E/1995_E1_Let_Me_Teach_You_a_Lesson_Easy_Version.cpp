// Problem: CF 1995 E1 - Let Me Teach You a Lesson (Easy Version)
// https://codeforces.com/contest/1995/problem/E1

/*
Algorithm: 
This problem requires minimizing the difference between the maximum and minimum sum of pairs of knights sitting opposite each other in a circle. 
The key insight is that we can only swap opposite knights (i and i+n), so the pairs (i, i+n) can be rearranged in two ways: either i and i+n stay as they are, or they are swapped.
For even n, we can compute all possible sums and find the minimum of max - min.
For odd n, the problem becomes more complex involving binary search and segment tree to determine valid configurations.

Time Complexity: O(n^2) for odd n due to sorting and sliding window technique, O(n) for even n.
Space Complexity: O(n) for storing state vectors and segment tree.
*/

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define N 200010
typedef long long ll;
int n, a[N];
struct Matrix {
  bool g[2][2];
  friend Matrix operator*(const Matrix &a, const Matrix &b) {
    return (Matrix){{{a.g[0][0] && b.g[0][0] || a.g[0][1] && b.g[1][0],
                      a.g[0][0] && b.g[0][1] || a.g[0][1] && b.g[1][1]},
                     {a.g[1][0] && b.g[0][0] || a.g[1][1] && b.g[1][0],
                      a.g[1][0] && b.g[0][1] || a.g[1][1] && b.g[1][1]}}};
  }
} t[N << 2];
#define ls u << 1
#define rs u << 1 | 1
struct State {
  int p, w, x, y;
};
inline void update(int u) { t[u] = t[ls] * t[rs]; }
void _modify(int u, int L, int R, int p, State z) {
  if (L == R) {
    t[u].g[z.x][z.y] ^= 1;
    return;
  }
  int mid = (L + R) >> 1;
  p <= mid ? _modify(ls, L, mid, p, z) : _modify(rs, mid + 1, R, p, z);
  update(u);
}
void Modify(int p, State z) { _modify(1, 1, n, p, z); }
bool OK() { return t[1].g[0][0] | t[1].g[1][1]; }
void Solve() {
  cin >> n;
  for (int i = 1; i <= n * 2; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n << 2; ++i) {
    memset(t[i].g, 0, sizeof(t[i].g));
  }
  if (n % 2 == 0) {
    // For even n, directly calculate min max difference without complex logic
    int mx = 0, mn = INT_MAX;
    for (int i = 1; i <= n; i += 2) {
      int x = min(a[i], a[i + n]) + max(a[i + 1], a[i + n + 1]);
      int y = max(a[i], a[i + n]) + min(a[i + 1], a[i + n + 1]);
      mx = max(mx, max(x, y));
      mn = min(mn, min(x, y));
    }
    cout << mx - mn << '\n';
    return;
  }
  // For odd n, generate all possible configurations and use sliding window with segment tree
  vector<State> c;
  for (int i = 1; i <= n; ++i) {
    if (i & 1) {
      // Process odd positions
      if (i == n) {
        // Special case for last element (i=n)
        c.push_back({i, a[i] + a[i + 1], 0, 0});
        c.push_back({i, a[i + n] + a[i + 1], 1, 0});
        c.push_back({i, a[i] + a[1], 0, 1});
        c.push_back({i, a[i + n] + a[1], 1, 1});
      } else {
        // General case for odd positions
        c.push_back({i, a[i] + a[i + 1], 0, 0});
        c.push_back({i, a[i + n] + a[i + 1], 1, 0});
        c.push_back({i, a[i] + a[i + n + 1], 0, 1});
        c.push_back({i, a[i + n] + a[i + n + 1], 1, 1});
      }
    } else {
      // Process even positions
      c.push_back({i, a[i] + a[i + 1], 1, 1});
      c.push_back({i, a[i + n] + a[i + 1], 0, 1});
      c.push_back({i, a[i] + a[i + n + 1], 1, 0});
      c.push_back({i, a[i + n] + a[i + n + 1], 0, 0});
    }
  }
  // Sort configurations based on weights
  sort(c.begin(), c.end(), [&](State a, State b) { return a.w < b.w; });
  int ans = INT_MAX;
  for (int i = 0, j = 0; i < (int)c.size(); ++i) {
    // Slide window to find valid combination and update answer
    while (j < (int)c.size() && !OK()) {
      Modify(c[j].p, c[j]);
      ++j;
    }
    if (!OK())
      break;
    ans = min(ans, c[j - 1].w - c[i].w);
    Modify(c[i].p, c[i]);
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/