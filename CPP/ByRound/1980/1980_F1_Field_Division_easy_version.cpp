// Problem: CF 1980 F1 - Field Division (easy version)
// https://codeforces.com/contest/1980/problem/F1

/*
Algorithm/Techniques: 
The solution uses a sweep line approach combined with sorting and preprocessing to efficiently compute the maximum area Alice can obtain.
We sort the fountains by their column (y) and then process them from left to right. For each group of fountains with the same column, we calculate the maximum area that can be enclosed by a path that avoids these fountains.
Time Complexity: O(k log k) due to sorting.
Space Complexity: O(k) for storing the fountains and auxiliary arrays.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

#define eb emplace_back
#define all(a) a.begin(), a.end()
#define rep(i, s, t) for (int i = (s); i <= (t); i++)
#define dep(i, t, s) for (int i = (t); i >= (s); i--)
#define For(i, n) for (int i = 0; i < (n); i++)
using namespace std;
using LL = long long;
using Pii = pair<int, int>;
using arr2 = array<int, 2>;
using arr3 = array<int, 3>;
const int N = 2e5 + 10, inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;
int n, m, k, h1[N], h2[N];
struct Node {
  int x, y, id;
  void input() { cin >> x >> y; }
  bool operator<(const Node &o) const {
    if (y != o.y)
      return y < o.y;
    return x > o.x;
  }
} a[N];
int pos[N], pre[N];
void solve() {
  cin >> n >> m >> k;
  rep(i, 1, k) a[i].input(), a[i].id = i;
  sort(a + 1, a + 1 + k);
  rep(i, 1, k) pos[a[i].id] = i;
  rep(i, 1, k) {
    if (a[i - 1].y != a[i].y) {
      pre[i] = a[pre[i - 1]].x >= a[i].x ? pre[i - 1] : i;
    } else {
      pre[i] = pre[i - 1];
    }
  }
  int lst = 0;
  LL ans = 0;
  a[0].y = 1;
  rep(i, 1, k) if (pre[i] == i) {
    ans += 1LL * (a[i].y - a[lst].y) * (n - a[lst].x);
    lst = i;
  }
  a[0].y = 0;
  ans += 1LL * (m + 1 - a[lst].y) * (n - a[lst].x);
  cout << ans << '\n';
  rep(i, 1, k) cout << (pre[pos[i]] == pos[i]) << ' ';
  cout << '\n';
}
int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/