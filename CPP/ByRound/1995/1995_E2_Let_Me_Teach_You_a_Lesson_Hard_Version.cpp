// Problem: CF 1995 E2 - Let Me Teach You a Lesson (Hard Version)
// https://codeforces.com/contest/1995/problem/E2

/* 
 * E2. Let Me Teach You a Lesson (Hard Version)
 *
 * Problem Description:
 * Arthur wants to minimize the difference between the maximum and minimum total intelligence
 * of pairs of knights sitting at opposite desks in a circle, where knights can be swapped
 * only if they are at opposite positions.
 *
 * Algorithm/Techniques:
 * - For even n: The optimal solution is obtained by considering all pair combinations
 *   and directly computing the minimal difference as the maximum of those differences.
 * - For odd n: A sliding window approach with bitset-based operations is used to efficiently
 *   track valid combinations that minimize the difference.
 *
 * Time Complexity: O(n log n) per test case due to sorting and linear scanning.
 * Space Complexity: O(n) for storing data structures like arrays and bitsets.
 */

#include <algorithm>
#include <bitset>
#include <iostream>
#include <utility>
#define ls i << 1
#define rs i << 1 | 1
#define fi first
#define se second
#define min amin
#define max amax
#define eb emplace_back
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 2E5 + 10;
const int inf = 2E9;
const int p = 998244353;
template <typename T = int> T read() {
  T x;
  cin >> x;
  return x;
}
template <typename U, typename V> U min(const U &x, const V &y) {
  return x < y ? x : y;
}
template <typename U, typename V> U max(const U &x, const V &y) {
  return x < y ? y : x;
}
template <typename U, typename... V> U min(const U &x, const V &...y) {
  return min(x, min(y...));
}
template <typename U, typename... V> U max(const U &x, const V &...y) {
  return max(x, max(y...));
}
template <typename U, typename V> bool cmin(U &x, const V &y) {
  return x > y ? x = y, true : false;
}
template <typename U, typename V> bool cmax(U &x, const V &y) {
  return x < y ? x = y, true : false;
}
template <typename T> T qpow(T x, int n) {
  T y = 1;
  for (; n; n >>= 1, x *= x)
    if (n & 1)
      y *= x;
  return y;
}
struct mint {
  int v;
  mint() : v() {}
  mint(const int &x) : v(x < 0 ? x + p : x) {}
  mint &operator+=(const mint &x) { return (v += x.v) < p ? 0 : v -= p, *this; }
  mint &operator-=(const mint &x) { return (v -= x.v) < 0 ? v += p : 0, *this; }
  mint &operator*=(const mint &x) { return v = ll(v) * x.v % p, *this; }
  mint operator+(const mint &x) const { return mint(*this) += x; }
  mint operator-(const mint &x) const { return mint(*this) -= x; }
  mint operator*(const mint &x) const { return mint(*this) *= x; }
  mint inv() const { return qpow(*this, p - 2); }
  bool operator==(const mint &x) const { return v == x.v; }
  friend istream &operator>>(istream &is, mint &x) { return is >> x.v; }
  friend ostream &operator<<(ostream &os, const mint &x) { return os << x.v; }
};
using ay = bitset<4>;
int a[N], c[N], n;
struct node {
  int i, k, x;
  bool operator<(const node &t) const { return x < t.x; }
} q[N << 1];
ay f[N];
void mg(ay &x, ay &y, ay &z) {
  x[0] = y[0] && z[0] || y[1] && z[2];
  x[1] = y[0] && z[1] || y[1] && z[3];
  x[2] = y[2] && z[0] || y[3] && z[2];
  x[3] = y[2] && z[1] || y[3] && z[3];
}
void modify(int i, int k) {
  i += n;
  f[i].flip(k);
  while (i >>= 1)
    mg(f[i], f[ls], f[rs]);
}
int solve() {
  cin >> n;
  int m = n << 1;
  for (int i = 0; i < m; ++i)
    cin >> a[i];
  if (~n & 1) { // If n is even
    int mn = inf, mx = 0;
    for (int i = 0; i < n; i += 2) {
      int x1 = a[i] + a[i + 1], y1 = a[i + n] + a[i + n + 1],
          x2 = a[i] + a[i + n + 1], y2 = a[i + n] + a[i + 1];
      if (x1 > y1)
        swap(x1, y1);
      if (x2 > y2)
        swap(x2, y2);
      if (x1 > x2)
        cmin(mn, x1), cmax(mx, y1);
      else
        cmin(mn, x2), cmax(mx, y2);
    }
    return mx - mn;
  }
  if (n == 1)
    return 0;
  for (int i = 0, j = 0; i < m; ++i, j & 1 ? j < n ? j += n : j -= n : ++j)
    c[i] = a[j];
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int x0 = i << 1, y0 = x0 | 1, x1 = x0 ? x0 - 1 : m - 1,
        y1 = y0 == m - 1 ? 0 : y0 + 1;
    q[s++] = {i, 0, c[x0] + c[y0]};
    q[s++] = {i, 1, c[x0] + c[y1]};
    q[s++] = {i, 2, c[x1] + c[y0]};
    q[s++] = {i, 3, c[x1] + c[y1]};
  }
  sort(q, q + s); // Sorting queries by value
  int mn = inf;
  for (int l = 0, r = -1;;) {
    if (f[1][0] || f[1][3]) { // Check if valid configuration exists in window
      cmin(mn, q[r].x - q[l].x);
      modify(q[l].i, q[l].k); // Remove element from left side of window
      ++l;
    } else {
      if (++r == s) // Expand window to right
        break;
      modify(q[r].i, q[r].k);
    }
  }
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < 4; ++j)
      f[i][j] = false;
  }
  return mn;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--)
    cout << solve() << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/