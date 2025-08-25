/*
 * Problem URL : https://codeforces.com/problemset/problem/2059/E2
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace qGet {
const int sz = 1 << 18;
char buf[sz], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, sz, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct Rd {
  Rd &operator>>(int &x) {
    x = 0;
    char c = gc();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = gc();
    return *this;
  }
} cin;
} // namespace qGet
namespace qPut {
const int sz = 1 << 18;
char buf[sz], *S = buf, *T = buf + sz;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct Exi {
  ~Exi() { flush(); }
} exi;
struct Wt {
  Wt &operator<<(int x) {
    if (!x) {
      pc('0');
      return *this;
    }
    static int sta[6];
    int top = 0;
    while (x) {
      sta[top++] = x % 10;
      x /= 10;
    }
    while (top)
      pc('0' + sta[--top]);
    return *this;
  }
  Wt &operator<<(char c) {
    pc(c);
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet::cin
#define cout qPut::cout
#define rsz resize
#define pb push_back
#define vi vector<int>
#define mmi make_move_iterator
int main() {
  int t;
  cin >> t;
  vi a, b;
  while (t--) {
    int n, m;
    cin >> n >> m;
    a.rsz(n * m);
    for (int &x : a)
      cin >> x;
    b.rsz(n * m);
    for (int &x : b)
      cin >> x;
    int res = 0;
    deque<array<int, 2>> ord;
    for (int r = 0; r < n; r++) {
      int rm = r * m, r1m = rm + m, j = rm, i = j - res, pos = 0;
      deque<array<int, 2>> tmp;
      while (i < rm && j < r1m) {
        if (a[i] != b[j]) {
          tmp.pb({r + 1, b[j++]});
          res++;
        } else {
          tmp.pb(ord.front());
          ord.pop_front();
          j++;
          i++;
        }
      }
      while (j < r1m && a[i] != b[j]) {
        tmp.pb({r + 1, b[j++]});
        res++;
      }
      int cnt = 0;
      while (j < r1m && a[i] == b[j]) {
        j++;
        i++;
        cnt++;
      }
      if (j < r1m) {
        j -= cnt;
        while (j < r1m) {
          tmp.pb({r + 1, b[j++]});
          res++;
        }
      }
      if (!tmp.empty())
        ord.insert(ord.begin(), mmi(tmp.begin()), mmi(tmp.end()));
    }
    cout << res << '\n';
    for (int i = --res; i >= 0; i--)
      cout << ord[i][0] << ' ' << ord[i][1] << '\n';
  }
}