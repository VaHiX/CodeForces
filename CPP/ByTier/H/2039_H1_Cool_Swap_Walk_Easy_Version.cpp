// Problem: CF 2039 H1 - Cool Swap Walk (Easy Version)
// https://codeforces.com/contest/2039/problem/H1

/*
Algorithm: Cool Swap Walk
Purpose: Sort an array using operations defined by paths from (1,1) to (n,n) in an n×n grid.
         Each step in path swaps elements at positions defined by current grid coordinates.
         Path must consist of only right (R) and down (D) moves.
Time Complexity: O(n^3) - For sorting and path manipulation
Space Complexity: O(n^2) - For storing paths and temporary arrays

Techniques:
- Greedy approach with path manipulation
- Sorting with custom comparator
- Grid path simulation with swaps
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
#define ll long long
#define ull unsigned long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(), (x).end()
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return f ? -x : x;
}
#define mod 1000000007
struct modint {
  unsigned int x;
  modint(int o = 0) { x = o; }
  modint &operator=(int o) { return x = o, *this; }
  modint &operator+=(modint o) {
    return x = x + o.x >= mod ? x + o.x - mod : x + o.x, *this;
  }
  modint &operator-=(modint o) {
    return x = x < o.x ? x - o.x + mod : x - o.x, *this;
  }
  modint &operator*=(modint o) { return x = 1ll * x * o.x % mod, *this; }
  modint &operator^=(int b) {
    modint a = *this, c = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1)
        c *= a;
    return x = c.x, *this;
  }
  modint &operator/=(modint o) { return *this *= o ^= mod - 2; }
  friend modint operator+(modint a, modint b) { return a += b; }
  friend modint operator-(modint a, modint b) { return a -= b; }
  friend modint operator*(modint a, modint b) { return a *= b; }
  friend modint operator/(modint a, modint b) { return a /= b; }
  friend modint operator^(modint a, int b) { return a ^= b; }
  friend bool operator==(modint a, modint b) { return a.x == b.x; }
  friend bool operator!=(modint a, modint b) { return a.x != b.x; }
  bool operator!() { return !x; }
  modint operator-() { return x ? mod - x : 0; }
  bool operator<(const modint &b) const { return x < b.x; }
};
inline modint qpow(modint x, int y) { return x ^ y; }
vector<modint> fac, ifac, iv;
inline void initC(int n) {
  if (iv.empty())
    fac = ifac = iv = vector<modint>(2, 1);
  int m = iv.size();
  ++n;
  if (m >= n)
    return;
  iv.resize(n), fac.resize(n), ifac.resize(n);
  For(i, m, n - 1) {
    iv[i] = iv[mod % i] * (mod - mod / i);
    fac[i] = fac[i - 1] * i, ifac[i] = ifac[i - 1] * iv[i];
  }
}
inline modint C(int n, int m) {
  if (m < 0 || n < m)
    return 0;
  return initC(n), fac[n] * ifac[m] * ifac[n - m];
}
inline modint sign(int n) { return (n & 1) ? (mod - 1) : (1); }
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;
#define maxn 2000005
#define inf 0x3f3f3f3f
int n, p[maxn], pp[maxn];
vector<string> out;
void oper(string s) {
  out.pb(s);
  int x = 1, y = 1;
  for (auto ch : s) {
    if (ch == 'R')
      ++x;
    else
      ++y;
    swap(p[x], p[y]);
  }
}
void work() {
  n = read();
  For(i, 1, n) p[i] = read(), pp[i] = i;
  sort(pp + 1, pp + n + 1, [&](int x, int y) { return p[x] < p[y]; });
  For(i, 1, n) p[pp[i]] = i;
  out.clear();
  while (!is_sorted(p + 1, p + n + 1)) {
    string s;
    For(i, 1, n - 1) s += "RD";  // Initial path: going right and down alternately
    for (int i = 2; i + 1 <= n; i += 2)  // For every pair of adjacent elements
      if (p[i] > p[i + 1] && p[i + 1] != 1) {  // If not sorted and not in correct position
        int u = i * 2 - 3;  // Index calculation for swapping
        swap(s[u], s[u + 1]);  // Adjust path to get correct swap
      }
    oper(s);
    if (out.size() > 2 * n + 4) {  // Enforce maximum number of moves
      puts("???");
      exit(0);
    }
  }
  cout << out.size() << "\n";
  for (auto s : out)
    cout << s << "\n";
}
signed main() {
  int T = 1;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/