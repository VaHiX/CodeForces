// Problem: CF 1896 D - Ones and Twos
// https://codeforces.com/contest/1896/problem/D

/*
Algorithm: 
This solution uses a set to track positions of 1s in the array for efficient querying.
For each query of type 1 (sum check):
- If s is too large, it's impossible.
- If s has the same parity as the number of 1s, it's possible (because we can replace 2s with 1s and vice versa).
- Otherwise, we check if s can be formed by considering max possible sums from either end of the array.

Time Complexity: O(q * log(n)) where q is the number of queries and n is the array size.
Space Complexity: O(n) for storing the array and the set of 1s positions.
*/
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
#if defined(LOCAL) or not defined(LUOGU)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,unroll-loops")
#endif
using namespace std;
#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...) (__VA_ARGS__)
#endif
namespace Fread {
const int SIZE = 1 << 16;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 16;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#define Setprecision 10
#define between '\n'
#define __int128 long long
template <typename T> struct is_char {
  static constexpr bool value =
      (std::is_same<T, char>::value || std::is_same<T, signed char>::value ||
       std::is_same<T, unsigned char>::value);
};
template <typename T> struct is_integral_ex {
  static constexpr bool value =
      (std::is_integral<T>::value || std::is_same<T, __int128>::value) &&
      !is_char<T>::value;
};
template <typename T> struct is_floating_point_ex {
  static constexpr bool value =
      std::is_floating_point<T>::value || std::is_same<T, __float128>::value;
};
namespace Fastio {
struct Reader {
  template <typename T>
  typename std::enable_if_t<std::is_class<T>::value, Reader &>
  operator>>(T &x) {
    for (auto &y : x)
      *this >> y;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_integral_ex<T>::value, Reader &>
  operator>>(T &x) {
    char c = getchar();
    short f = 1;
    while (c < '0' || c > '9') {
      if (c == '-')
        f *= -1;
      c = getchar();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
      x = (x << 1) + (x << 3) + (c ^ 48);
      c = getchar();
    }
    x *= f;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_floating_point_ex<T>::value, Reader &>
  operator>>(T &x) {
    char c = getchar();
    short f = 1, s = 0;
    x = 0;
    T t = 0;
    while ((c < '0' || c > '9') && c != '.') {
      if (c == '-')
        f *= -1;
      c = getchar();
    }
    while (c >= '0' && c <= '9' && c != '.')
      x = x * 10 + (c ^ 48), c = getchar();
    if (c == '.')
      c = getchar();
    else
      return x *= f, *this;
    while (c >= '0' && c <= '9')
      t = t * 10 + (c ^ 48), s++, c = getchar();
    while (s--)
      t /= 10.0;
    x = (x + t) * f;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_char<T>::value, Reader &> operator<<(T c) {
    putchar(c);
    return *this;
  }
  Reader() {}
} cin;
const char endl = '\n';
struct Writer {
  typedef __int128 mxdouble;
  template <typename T>
  typename std::enable_if_t<std::is_class<T>::value, Writer &> operator<<(T x) {
    for (auto &y : x)
      *this << y << between;
    *this << '\n';
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_integral_ex<T>::value, Writer &>
  operator<<(T x) {
    if (x == 0)
      return putchar('0'), *this;
    if (x < 0)
      putchar('-'), x = -x;
    static int sta[45];
    int top = 0;
    while (x)
      sta[++top] = x % 10, x /= 10;
    while (top)
      putchar(sta[top] + '0'), --top;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_floating_point_ex<T>::value, Writer &>
  operator<<(T x) {
    if (x < 0)
      putchar('-'), x = -x;
    mxdouble _ = x;
    x -= (T)_;
    static int sta[45];
    int top = 0;
    while (_)
      sta[++top] = _ % 10, _ /= 10;
    if (!top)
      putchar('0');
    while (top)
      putchar(sta[top] + '0'), --top;
    putchar('.');
    for (int i = 0; i < Setprecision; i++)
      x *= 10;
    _ = x;
    while (_)
      sta[++top] = _ % 10, _ /= 10;
    for (int i = 0; i < Setprecision - top; i++)
      putchar('0');
    while (top)
      putchar(sta[top] + '0'), --top;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_char<T>::value, Writer &> operator<<(T c) {
    putchar(c);
    return *this;
  }
  Writer &operator<<(char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer &operator<<(const char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer &operator<<(std::string str) {
    int st = 0, ed = str.size();
    while (st < ed)
      putchar(str[st++]);
    return *this;
  }
  Writer() {}
} cout;
} // namespace Fastio
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1);
  set<int> st;
  for (int x = 1; x <= n; x++) {
    cin >> a[x];
    if (a[x] == 1)
      st.insert(x);
  }
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int s;
      cin >> s;
      if (s > 2 * n - st.size()) {
        cout << "NO" << endl;
        continue;
      }
      if ((s ^ st.size()) & 1 ^ 1) {
        cout << "YES" << endl;
        continue;
      }
      if (st.empty()) {
        cout << "No" << endl;
        continue;
      }
      if (s <=
          max(2 * (*st.rbegin() - 1), 2 * (n - *st.begin())) - st.size() + 1) {
        cout << "YEs" << endl;
        continue;
      }
      cout << "nO" << endl;
    } else {
      int i, v;
      cin >> i >> v;
      st.erase(i);
      a[i] = v;
      if (v == 1)
        st.insert(i);
    }
  }
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/