// Problem: CF 1981 B - Turtle and an Infinite Sequence
// https://codeforces.com/contest/1981/problem/B

/*
Purpose: This program computes the value of a_n after m seconds in a sequence that evolves according to a bitwise OR update rule.

Algorithms/Techniques:
- Bit manipulation and properties of OR operation
- Efficient computation using the lowbit function and bit shifts
- Observing pattern in how values propagate and merge over time

Time Complexity: O(log m) per test case, due to iteration through bits using lowbit
Space Complexity: O(1), only using a few variables for computation

*/

#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define se second
#define fi first
#define endl "\n"
#define INF 0x3f3f3f3f
#define ll long long
#define LINF 1ll << 60
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define IOS                                                                    \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0)
const double PI = acos(-1.0);
const int N = 4e5 + 5;
const int mod = 998244353;
#define int long long
int lowbit(int x) { return x & (-x); }
void solve() {
  int n, m;
  cin >> n >> m;
  if (n == 0) {
    int res = 0;
    int now = 1;
    while (now <= m) {
      res |= now;            // Accumulate all bits up to m using OR
      now += lowbit(now);    // Move to next relevant bit position
    }
    cout << res << endl;
  } else {
    int r = n + m;               // Right boundary of range affected by n after m steps
    int l = max(1ll * 0, n - m); // Left boundary of range affected by n after m steps
    int res = n | r;             // Initialize result with OR of n and r
    int bit = 0;
    while ((l | (1ll << bit)) <= r) {
      res |= (l | (1ll << bit)); // Add more bits to result based on current range
      bit++;
    }
    cout << res << endl;
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/