// Problem: CF 1923 F - Shrink-Reverse
// https://codeforces.com/contest/1923/problem/F

/*
Algorithm: Greedy + Hashing + Binary Search
Time Complexity: O(n * log n)
Space Complexity: O(n)

The solution works by analyzing the positions of '1's in the string to minimize the final value.
It uses hashing to compare substrings efficiently and binary search to find optimal swaps.
The approach prioritizes placing '1's as late as possible to minimize the value,
but allows up to k operations to manipulate the string.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define S cerr << "SYT AK IOI" << endl;
#define M cerr << "MKF AK IOI" << endl;
#define CONNECT_BASE(x, y) x##y
#define CONNECT(x, y) CONNECT_BASE(x, y)
#define DEBUG_BASE(x) cerr << #x << '=' << x << ' '
#define DEB_1(x) DEBUG_BASE(x)
#define DEB_2(x, y) DEB_1(x), DEB_1(y)
#define DEB_3(x, y, z) DEB_1(x), DEB_2(y, z)
#define DEB_4(x, y, z, w) DEB_1(x), DEB_3(y, z, w)
#define DEB_5(a, b, c, d, e) DEB_1(a), DEB_4(b, c, d, e)
#define DEB_6(a, b, c, d, e, f) DEB_1(a), DEB_5(b, c, d, e, f)
#define COUNT_BASE(_1, _2, _3, _4, _5, _6, x, ...) x
#define COUNT(...) COUNT_BASE(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define D(...)                                                                 \
  std::cerr << "[In Line " << __LINE__ << "]: ",                               \
      CONNECT(DEB_, COUNT(__VA_ARGS__))(__VA_ARGS__), cerr << '\n'
#define NAME(x) #x
#define INNAME(x) NAME(x)
using ll = long long;
using pii = pair<int, int>;
using uint = unsigned int;
using ull = unsigned long long;
mt19937 rd(0 ^ (*new int));
#define int long long
#define pb(x) push_back(x)
#define F(i, a, b) for (int i = (a), i##end = (b); i <= (i##end); ++i)
#define UF(i, a, b) for (int i = (a), i##end = (b); i >= (i##end); --i)
#define gc() getchar()
#define ret return
#define pc putchar
#define popcount(x) __builtin_popcount(x)
const int mod = 1e9 + 7;
inline void init();
inline void IO();
const int N = 5e5 + 5;
int n, k;
vector<int> v;
inline int qpow(int a, int b, int p) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  ret res;
}
pii ans;
int bas;
ull hs[N], hzs[N];
bool fg = 0;
ull pw[N];
inline void mian() {
  bas = 233;
  bas = bas | 1;
  cin >> n >> k;
  string s;
  cin >> s;
  s = " " + s;
  pw[0] = 1;
  F(i, 1, n) hs[i] = hs[i - 1] * bas + s[i], pw[i] = pw[i - 1] * bas;
  UF(i, n, 1) hzs[i] = hzs[i + 1] * bas + s[i];
  v.push_back(0);
  F(i, 1, n) if (s[i] == '1') v.push_back(i);
  if (v.size() == 1) {
    cout << 0;
    ret;
  }
  int m = v.size() - 1;
  if (k >= v.size() - 1) {
    cout << (qpow(2, v.size() - 1, mod) - 1 + mod) % mod << endl;
    ret;
  }
  ans = {min(n - m + 1, v[k + 1]), n};
  k--;
  F(i, 1, m) {
    if (i > k + 1)
      break;
    int L = v[i], R = v[m - k + i - 1];
    if (R - L + 1 <= m) {
      cout << (qpow(2, m, mod) - 1 + mod) % mod << endl;
      ret;
    }
    if (R - L + 1 < ans.second - ans.first + 1) {
      ans.second = R, ans.first = L;
      fg = 1;
      continue;
    }
    if (R - L == ans.second - ans.first) {
      if (!fg) {
        int l = 0, r = R - L;
        while (r > l) {
          int mid = (l + r + 1) >> 1;
          ull bas = pw[R - L - mid + 1];
          if (hzs[L + mid] - hzs[R + 1] * bas ==
              hs[ans.second - mid] - hs[ans.first - 1] * bas)
            r = mid - 1;
          else
            l = mid;
        }
        if (s[L + l] == '0') {
          fg = 1;
          ans = {L, R};
          continue;
        }
      } else {
        int L2 = ans.first, R2 = ans.second;
        int l = 0, r = R - L;
        while (r > l) {
          int mid = (l + r + 1) >> 1;
          ull bas = pw[R - L - mid + 1];
          if (hzs[L + mid] - hzs[R + 1] * bas ==
              hzs[L2 + mid] - hzs[R2 + 1] * bas)
            r = mid - 1;
          else
            l = mid;
        }
        if (s[L + l] == '0') {
          fg = 1;
          ans = {L, R};
          continue;
        }
      }
    }
  }
  if (!fg) {
    int sum = 0;
    F(i, ans.first, ans.second) {
      if (s[i] == '1')
        sum++;
    }
    sum = m - sum;
    UF(i, ans.second, ans.first) {
      if (!sum)
        break;
      if (s[i] == '0')
        s[i] = '1', sum--;
    }
    int sss = 0;
    F(i, ans.first, ans.second) sss = (sss * 2 + s[i] - 48) % mod;
    cout << sss;
  } else {
    int sum = 0;
    F(i, ans.first, ans.second) {
      if (s[i] == '1')
        sum++;
    }
    sum = m - sum;
    F(i, ans.first, ans.second) {
      if (!sum)
        break;
      if (s[i] == '0')
        s[i] = '1', sum--;
    }
    int sss = 0;
    UF(i, ans.second, ans.first) sss = (sss * 2 + s[i] - 48) % mod;
    cout << sss;
  }
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
#ifdef multitest
  cin >> T;
#endif
  init();
  while (T--)
    mian();
  return 0;
}
inline void init() {}
#define FILEIO std
inline void IO() {
#ifdef FILEIO
  freopen(INNAME(FILEIO) ".in", "r", stdin),
      freopen(INNAME(FILEIO) ".out", "w", stdout);
#endif
}


// https://github.com/VaHiX/CodeForces/