// Problem: CF 1859 C - Another Permutation Problem
// https://codeforces.com/contest/1859/problem/C

/*
 * Problem: Another Permutation Problem
 * Algorithm: Brute-force with optimization
 * Time Complexity: O(n^3), where n is the length of the permutation
 * Space Complexity: O(n), for storing the permutation array
 *
 * The idea is to try all possible ways to split the permutation into two parts:
 * - First part: elements from 1 to x (in order)
 * - Second part: elements from n down to (n - x) (in reverse order)
 * For each such split, compute the cost and keep track of the maximum.
 */

#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
#define rep(i, a, n) for (int i = (a); i < (n); ++i)
#define per(i, a, n) for (int i = (a); i > (n); --i)
#define pb emplace_back
#define mp make_pair
#define clr(a, b) memset(a, b, sizeof(a))
#define all(x) (x).begin(), (x).end()
#define lowbit(x) (x & -x)
#define fi first
#define se second
#define lson o << 1
#define rson o << 1 | 1
#define gmid l[o] + r[o] >> 1
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ui = unsigned int;
constexpr int mod = 998244353;
constexpr int inf = 0x3f3f3f3f;
constexpr double EPS = 1e-8;
const double PI = acos(-1.0);
constexpr int N = 510;
int T, n, a[N];

void _main() {
  cin >> T;
  while (T--) {
    cin >> n;
    int ans = 0;
    // Try all possible splits of the permutation
    rep(x, 0, n + 1) {
      // Build the first part with values from 1 to x
      rep(i, 1, x + 1) a[i] = i;
      // Build the second part with values from n down to (n - x)
      int m = n;
      rep(i, x + 1, n + 1) a[i] = m--;
      int cur = 0, mx = 0;
      // Compute the cost for current configuration
      rep(i, 1, n + 1) {
        int v = i * a[i];  // Value of term i * a[i]
        cur += v;          // Add to sum
        mx = max(mx, v);   // Track maximum value
      }
      ans = max(ans, cur - mx); // Update maximum cost
    }
    cout << ans << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  _main();
  return 0;
}


// https://github.com/VaHiX/CodeForces/