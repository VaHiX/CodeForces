// Problem: CF 1829 H - Don't Blame Me
// https://codeforces.com/contest/1829/problem/H

/*
Algorithm: Dynamic Programming with Bitmask
Techniques: 
- Using bit manipulation to count set bits
- Dynamic programming on bitmask to track number of subsequences ending with a specific bitwise AND result

Time Complexity: O(n * 64) = O(n) where n <= 2e5
Space Complexity: O(64) = O(1) since we only use fixed-size arrays

The approach uses dynamic programming where f[mask] represents the number of subsequences
whose bitwise AND results in 'mask'. For each new element, we update the dp array by 
combining it with existing masks. We count how many of these masks have exactly k set bits.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

#define fi first
#define se second
#define gc getchar()
#define mk make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define IT iterator
#define V vector
#define TP template <class o>
#define TPP template <typename t1, typename t2>
#define SZ(a) ((int)a.size())
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for (int i = a, i##ed_ = b; i <= i##ed_; i++)
#define REP(i, a, b) for (int i = b, i##st_ = a; i >= i##st_; i--)
#define FOR(i, n) rep(i, 1, n)
#define debug(x) cerr << #x << ' ' << '=' << ' ' << x << endl
using namespace std;
typedef double db;
typedef unsigned ui;
typedef long long ll;
typedef long double ld;
TP void qr(o &x) {
  char c = gc;
  x = 0;
  int f = 1;
  while (!isdigit(c)) {
    if (c == '-')
      f = -1;
    c = gc;
  }
  while (isdigit(c))
    x = x * 10 + c - '0', c = gc;
  x *= f;
}
template <class o, class... O> void qr(o &x, O &...y) { qr(x), qr(y...); }
TP void qw(o x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x / 10)
    qw(x / 10);
  putchar(x % 10 + '0');
}
TP void pr1(o x) { qw(x), putchar(' '); }
template <class o, class... O> void pr1(o x, O... y) { pr1(x), pr1(y...); }
TP void pr2(o x) { qw(x), putchar(10); }
template <class o, class... O> void pr2(o x, O... y) { pr2(x), pr2(y...); }
TP bool cmax(o &x, o y) { return (x < y ? x = y, 1 : 0); }
TP bool cmin(o &x, o y) { return (x > y ? x = y, 1 : 0); }
const int mod = 1e9 + 7;
TPP void ad(t1 &x, t2 y) { (x += y) >= mod && (x -= mod); }
TPP void dl(t1 &x, t2 y) { (x -= y) < 0 && (x += mod); }
const int N = 2e5 + 10, M = 64, inf = 2e9;
const ll INF = 1e15;
int n, m, ans, f[M], cnt[M];
void solve() {
  qr(n, m);
  ans = 0;
  memset(f, 0, sizeof f);
  FOR(i, n) {
    int x;
    qr(x);
    rep(j, 0, M - 1) ad(f[j & x], f[j]);  // Update dp by combining current element with all previous masks
    ad(f[x], 1);  // Add the new single element as a subsequence
  }
  rep(i, 0, M - 1) if (cnt[i] == m) ad(ans, f[i]);  // Count those masks with exactly k set bits
  pr2(ans);
}
int main() {
#ifndef ONLINE_JUDGE
  clock_t start_time = clock();
#endif
  int T = 1;
  qr(T);
  FOR(i, M - 1) cnt[i] = cnt[i & (i - 1)] + 1;  // Precompute number of set bits for all numbers 0..63
  while (T--)
    solve();
#ifndef ONLINE_JUDGE
  cerr << 1.0 * (clock() - start_time) / CLOCKS_PER_SEC << ' ' << 's' << endl;
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/