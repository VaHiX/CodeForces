// Problem: CF 1913 D - Array Collapse
// https://codeforces.com/contest/1913/problem/D

// Problem: Array Collapse
// Algorithm: Dynamic Programming with Stack
// Time Complexity: O(n) amortized per test case
// Space Complexity: O(n)

#include <stdio.h>
#include <algorithm>
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
  typename std::enable_if_t<is_char<T>::value, Reader &> operator>>(T &c) {
    c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    return *this;
  }
  Reader &operator>>(char *str) {
    int len = 0;
    char c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    while (c != '\n' && c != ' ' && c != '\r')
      str[len++] = c, c = getchar();
    str[len] = '\0';
    return *this;
  }
  Reader &operator>>(std::string &str) {
    str.clear();
    char c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    while (c != '\n' && c != ' ' && c != '\r')
      str.push_back(c), c = getchar();
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
      putchar('-');
    short f = 1;
    if (x < 0) {
      x = -x;
      f = 0;
    }
    int int_part = x;
    double dec_part = x - int_part;
    if (f == 0) {
      putchar('-');
    }
    putchar(int_part + '0');
    putchar('.');
    for (int i = 0; i < 10; i++) {
      dec_part *= 10;
      int digit = dec_part;
      putchar(digit + '0');
      dec_part -= digit;
    }
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
void solve();
int main() {
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
constexpr int p = 998244353;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1), dp(n + 1), s(n + 1);
  for (int x = 1; x <= n; x++)
    cin >> a[x];
  vector<int> st;
  int sum = 0;
  for (int x = 1; x <= n; x++) {
    // Maintaining stack properties; popping elements smaller than current
    while (!st.empty() && a[x] < a[st.back()])
      (sum -= dp[st.back()]) %= p, st.pop_back();
    
    // Compute the number of valid sequences ending at position x
    if (st.empty())
      dp[x] = (1 + s[x - 1]) % p;
    else
      dp[x] = ((sum + s[x - 1]) % p - s[st.back()]) % p;
    
    // Update prefix sum array for future calculations
    s[x] = (s[x - 1] + dp[x]) % p;
    (sum += dp[x]) %= p;
    st.push_back(x);
  }
  int now = 1e9;
  int ans = 0;
  for (int x = n; x >= 1; x--)
    if (a[x] <= now)
      now = a[x], (ans += dp[x]) %= p;
  cout << (ans + p) % p << endl;
}


// https://github.com/VaHiX/CodeForces/