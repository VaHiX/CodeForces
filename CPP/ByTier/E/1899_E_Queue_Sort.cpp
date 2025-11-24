// Problem: CF 1899 E - Queue Sort
// https://codeforces.com/contest/1899/problem/E

/*
Algorithm: Queue Sort
Approach:
1. Find the minimum element in the array.
2. Try each position where the minimum element occurs.
3. For each such position, check if the subarray from that position to the end is non-decreasing.
4. If it is, the number of operations needed is (position - 1).
5. If no such position is found, return -1.

Time Complexity: O(n^2) in worst case due to checking subarrays.
Space Complexity: O(1) excluding input storage.

Techniques:
- Linear scan through array for minimum element
- Subarray validation for non-decreasing order
- Greedy approach to find optimal starting point

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

#define NDEBUG
#pragma GCC optimize(2)
using std::cin, std::cout;
using ll = long long;
using db = double;
void Main(void);
int main(void) {
  std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#if defined(TEXT_IO) and defined(LOCAL) and not defined(ONLINE_JUDGE)
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  Main();
  return 0;
}
namespace my {
#if defined(LOCAL) and not defined(ONLINE_JUDGE)
#include "D:\VScodeFile\LOCAL\debug.h"

#define DBG(x) std::cerr << "! " #x " = " << (x) << std::endl
#else
#define dbg(...) ((void)0)
#define DBG(...) ((void)0)
#endif
#define VE std::vector
#define STR std::string
#define HEAP std::priority_queue
#define PLL std::pair<ll, ll>
#define fi first
#define se second
#define EDL '\n'
#define WS ' '
#define SDP(x) std::fixed << std::setprecision(x)
#define SZ(x) ((ll)x.size())
#define FOR(i, l, r) for (ll i = (l); i <= (r); ++i)
#define ROF(i, r, l) for (ll i = (r); i >= (l); --i)
constexpr int inf = 0x3f3f3f3f;
constexpr ll INF = 0x3f3f3f3f3f3f3f3fLL;
} // namespace my
using namespace my;
namespace fastIO {
constexpr ll BUF_SZ = 1e5 + 5;
bool IOrun = true;
char NC(void) {
  static char buf[BUF_SZ], *p = buf + BUF_SZ, *ed = buf + BUF_SZ;
  if (p != ed)
    return *p++;
  p = buf;
  ed = buf + fread(buf, 1, BUF_SZ, stdin);
  if (p == ed) {
    IOrun = false;
    return -1;
  }
  return *p++;
}
bool BLK(char c) { return c == WS or c == EDL or c == '\r' or c == '\t'; }
template <class T> bool FIN(T &x) {
  bool sign = false;
  char c = NC();
  x = 0;
  while (BLK(c))
    c = NC();
  if (not IOrun)
    return false;
  if (c == '-') {
    sign = true;
    c = NC();
  }
  while ('0' <= c and c <= '9') {
    x = x * 10 + c - '0';
    c = NC();
  }
  if (sign)
    x = -x;
  return true;
}
bool FIN(db &x) {
  bool sign = false;
  char c = NC();
  x = 0;
  while (BLK(c))
    c = NC();
  if (not IOrun)
    return false;
  if (c == '-') {
    sign = true;
    c = NC();
  }
  while ('0' <= c and c <= '9') {
    x = x * 10 + c - '0';
    c = NC();
  }
  if (c == '.') {
    db w = 1.0;
    c = NC();
    while ('0' <= c and c <= '9') {
      w /= 10.0;
      x += w * (c - '0');
      c = NC();
    }
  }
  if (sign)
    x = -x;
  return true;
}
bool FIN(char &c) {
  c = NC();
  while (BLK(c))
    c = NC();
  if (not IOrun) {
    c = -1;
    return false;
  }
  return true;
}
bool FIN(char *s) {
  char c = NC();
  while (BLK(c))
    c = NC();
  if (not IOrun)
    return false;
  while (IOrun and not BLK(c)) {
    *s++ = c;
    c = NC();
  }
  *s = 0;
  return true;
}
bool LIN(char *s) {
  char c = NC();
  while (BLK(c))
    c = NC();
  if (not IOrun)
    return false;
  while (IOrun and c != EDL) {
    *s++ = c;
    c = NC();
  }
  *s = 0;
  return true;
}
template <class T, class... Y> bool FIN(T &x, Y &...o) {
  return FIN(x) and FIN(o...);
}
void FIN(int *a, ll l, ll r) {
  FOR(i, l, r)
  FIN(a[i]);
  return;
}
void FIN(ll *a, ll l, ll r) {
  FOR(i, l, r)
  FIN(a[i]);
  return;
}
void FIN(db *a, ll l, ll r) {
  FOR(i, l, r)
  FIN(a[i]);
  return;
}
void FIN(char *a, ll l, ll r) {
  FOR(i, l, r)
  FIN(a[i]);
  return;
}
} // namespace fastIO
using fastIO::FIN, fastIO::LIN;
constexpr db EPS = 1.0e-9;
constexpr ll MOD = 998244353LL;
constexpr ll SZ = 2e5 + 5;
ll n;
ll a[SZ];
ll b[SZ];
void Run(void) {
  FIN(n);
  FIN(a, 1, n);
  ll mn = INF;
  FOR(i, 1, n)
  mn = std::min(mn, a[i]);
  FOR(i, 1, n) {
    if (a[i] == mn) {
      bool ok = true;
      FOR(j, i, n - 1) {
        if (a[j] > a[j + 1]) {
          ok = false;
          break;
        }
      }
      if (ok)
        cout << i - 1 << EDL;
      else
        cout << -1 << EDL;
      return;
    }
  }
  return;
}
void Main(void) {
  ll t;
  FIN(t);
  while (t--)
    Run();
  return;
}


// https://github.com/VaHiX/CodeForces/