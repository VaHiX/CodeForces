// Problem: CF 2172 K - Kindergarten Homework
// https://codeforces.com/contest/2172/problem/K

/*
 * Problem: K. Kindergarten Homework - Number Search
 * 
 * Approach:
 * 1. For each cell in the grid that contains a digit, we explore all 8 directions (horizontal, vertical, diagonal).
 * 2. For each direction, we construct valid mathematical expressions by reading consecutive characters.
 * 3. An expression is valid if it follows the format: numbers separated by '+' or '*' operations.
 * 4. We use a stack to handle operator precedence (multiplication before addition).
 * 5. As we build each expression, we evaluate its value and count occurrences in a frequency array.
 * 6. For each query, we simply return the precomputed count for that number.
 * 
 * Time Complexity: O(n * m * max(n, m) + q)
 *   - n * m: iterate through each cell
 *   - max(n, m): for each cell, we may traverse up to max(n, m) characters in one direction
 *   - q: number of queries
 * Space Complexity: O(n * m + q)
 *   - Grid storage: O(n * m)
 *   - Count array and query storage: O(q)
 */

#include <stdint.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
#ifdef LonggVuz
#include <LonggVuz.h>
#else
#define debug(...)
#endif
template <class X, class Y> bool maxi(X &a, const Y &b) {
  return b > a ? a = b, 1 : 0;
}
template <class X, class Y> bool mini(X &a, const Y &b) {
  return b < a ? a = b, 1 : 0;
}
#define el cout << '\n'
#define fUp(i, a, b, c) for (int32_t i = a; i <= b; i += c)
#define fdn(i, a, b, c) for (int32_t i = a; i >= b; i -= c)
#define fo(i, a, b) for (int32_t i = a; i <= b; i++)
#define fd(i, a, b) for (int32_t i = a; i >= b; i--)
#define out(x) return void(cout << (x))
#define all(x) begin(x), end(x)
#define len(x) (int)(x).size()
#define vec vector
#define pub push_back
#define pob pop_back
#define dub double
#define int int64_t
const int mod = 1e9 + 7;
const int oo = 1e18 + 7;
const int mxn = 1e6 + 7;
int n, m, q, cnt[mxn];
char a[1005][1005];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
vec<int> val;
stack<int> st;
void edit(int i, int j, int x, int y) {
  while (!st.empty())
    st.pop();
  val.clear();
  val.pub(0);
  int s = -1, cur = 0;
  while (1 <= i and i <= n and 1 <= j and j <= m) {
    if ('1' <= a[i][j] and a[i][j] <= '9') {
      int v = val.back();
      val.pob();
      v = v * 10 + a[i][j] - '0';
      if (v > 1e6)
        return;
      val.pub(v);
    } else if (a[i][j] == '+') {
      if (val.back() == 0)
        return;
      if (s == -1) {
        st.push(val.back());
        cur += val.back();
      } else {
        cur -= st.top();
        st.top() *= val.back();
        cur += st.top();
      }
      if (st.top() > 1e6)
        return;
      val.pub(-1);
      val.pub(0);
      s = -1;
    } else {
      if (val.back() == 0)
        return;
      if (s == -1) {
        st.push(val.back());
        cur += val.back();
      } else {
        cur -= st.top();
        st.top() *= val.back();
        cur += st.top();
      }
      if (st.top() > 1e6)
        return;
      val.pub(-2);
      val.pub(0);
      s = -2;
    }
    if (cur > 1e6)
      return;
    if (val.back() > 0) {
      if (s == -1) {
        cur += val.back();
        if (cur > 1e6)
          return;
        ++cnt[cur];
        cur -= val.back();
      } else {
        cur = cur - st.top() + st.top() * val.back();
        if (cur > 1e6)
          return;
        ++cnt[cur];
        cur = cur - st.top() * val.back() + st.top();
      }
    }
    i += x;
    j += y;
  }
}
inline void LonggVuz() {
  cin >> n >> m >> q;
  fo(i, 1, n) fo(j, 1, m) { cin >> a[i][j]; }
  fo(i, 1, n) fo(j, 1, m) if ('1' <= a[i][j] and a[i][j] <= '9') {
    fo(k, 0, 7) { edit(i, j, dx[k], dy[k]); }
    cnt[a[i][j] - '0'] -= 7;
  }
  while (q--) {
    int x;
    cin >> x;
    cout << cnt[x], el;
  }
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
#ifdef LonggVuz
  freopen("longgvuz.inp", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  signed orz = 1;
  if (false)
    cin >> orz;
  while (orz-- > 0) {
    LonggVuz();
    if (orz)
      el;
  }
  cerr << "Execution Time: " << clock() << "ms\n";
}


// https://github.com/VaHiX/CodeForces/