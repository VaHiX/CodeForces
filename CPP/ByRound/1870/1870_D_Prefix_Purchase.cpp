// Problem: CF 1870 D - Prefix Purchase
// https://codeforces.com/contest/1870/problem/D

/*
Code Purpose:
This code solves the "Prefix Purchase" problem where we aim to maximize the lexicographically 
largest array 'a' by purchasing operations that add 1 to all elements from index 1 to i. 
Each operation costs c[i] coins and can be performed multiple times as long as we have enough coins.
The solution uses a greedy approach after preprocessing the cost array to ensure non-increasing order.

Algorithms/Techniques:
- Greedy algorithm with preprocessing
- Prefix minimization to ensure optimal purchasing order
- Iterative assignment from left to right to maximize lexicographical value

Time Complexity: O(n) per test case, where n is the size of the array
Space Complexity: O(n) for storing the array c

*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define ll long long
#define ld long double
#define int long long
#define endl '\n'
#define MAXN 0x7fffffff
const int N = 200005;
int gcd(int x, int y) { return (y == 0) ? (x) : (gcd(y, x % y)); }
ll lcm(ll x, ll y) { return (x / gcd(x, y)) * y; }
char *p1, *p2, buf[100000];
#define nc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
int read() {
  int x = 0, f = 1;
  char ch = nc();
  while (ch < 48 || ch > 57) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }
  while (ch >= 48 && ch <= 57)
    x = x * 10 + ch - 48, ch = nc();
  return x * f;
}
void write(int x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
  return;
}
struct fio {
  inline char gc() {
    static const int IN_LEN = 1 << 18 | 1;
    static char buf[IN_LEN], *s, *t;
    static streambuf *sb = cin.rdbuf();
    return (s == t) && (t = (s = buf) + sb->sgetn(buf, IN_LEN)),
           s == t ? -1 : *s++;
  }
  inline fio &operator>>(string &s) {
    static char ch;
    ch = gc();
    s.clear();
    for (; isspace(ch); ch = gc())
      if (ch == -1)
        return *this;
    for (; !isspace(ch) && ch != -1; ch = gc())
      s += ch;
    return *this;
  }
  inline fio &operator>>(char *s) {
    static char ch;
    ch = gc();
    for (; isspace(ch); ch = gc())
      if (ch == -1)
        return *this;
    for (; !isspace(ch) && ch != -1; ch = gc())
      *(s++) = ch;
    return *this;
  }
  inline void gtline(string &s) {
    static char ch;
    ch = gc();
    s.clear();
    for (; ch != '\n' && ch != -1; ch = gc())
      s += ch;
  }
  template <typename T> inline fio &operator>>(T &n) {
    static char ch, sgn;
    ch = gc(), sgn = 0;
    for (; !isdigit(ch); ch = gc()) {
      if (ch == -1)
        return *this;
      sgn |= ch == '-';
    }
    for (n = 0; isdigit(ch); ch = gc())
      n = n * 10 + (ch ^ '0');
    if (ch == '.') {
      T tmp = 0;
      ch = gc();
      for (; isdigit(ch); ch = gc())
        tmp = tmp * 10 + (ch ^ '0');
      while (tmp > 1)
        tmp /= 10;
      n += tmp;
    }
    sgn && (n = -n);
    return *this;
  }
} io;
int c[N];
void solve() {
  int n;
  io >> n;
  for (int i = 1; i <= n; i++) {
    io >> c[i];
  }
  // Preprocessing: ensure c[i] is minimum of c[i] and all elements to its right
  for (int i = n - 1; i >= 1; i--) {
    c[i] = min(c[i], c[i + 1]);
  }
  int now; // Stores how many units can be purchased at current step
  int k;
  io >> k;
  for (int i = 1; i <= n; i++) {
    if (i == 1) {
      // First element: use all coins to buy as many units as possible
      now = k / c[1];
      cout << now << ' ';
      k %= c[1];
    } else {
      // For other elements, check if cost is same as previous
      if (c[i] - c[i - 1] == 0)
        cout << now << " ";
      else {
        // Calculate how many units can be purchased with remaining coins
        now = min(now, k / (c[i] - c[i - 1]));
        cout << now << " ";
        k -= now * (c[i] - c[i - 1]);
      }
    }
  }
  cout << endl;
}
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/