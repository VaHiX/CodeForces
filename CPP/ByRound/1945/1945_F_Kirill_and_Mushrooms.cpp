// Problem: CF 1945 F - Kirill and Mushrooms
// https://codeforces.com/contest/1945/problem/F

/* 
算法/技术: 贪心 + 优先队列 + 排序
时间复杂度: O(n log n)
空间复杂度: O(n)

思路:
1. 按魔法值从大到小对蘑菇索引排序
2. 对于每个可能的蘑菇数量k，我们尝试找到最优的k个蘑菇
3. 使用优先队列维护当前已选蘑菇中，哪些蘑菇的魔法值会被变为0
4. 对于每个k，从排序后的数组中选取前k个蘑菇，使用优先队列判断它们是否会影响后续蘑菇
5. 记录最大强度和对应的最小蘑菇数
*/

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
#include <string>
#include <type_traits>
#include <vector>
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
      t = t * 10 + (c ^ 48), c = getchar();
    for (int i = 0; i < Setprecision; i++)
      t *= 10;
    x += t / pow(10, Setprecision);
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
    x += pow(10, -Setprecision) / 2;
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
void solve();
int main() {
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
void solve() {
  int n;
  cin >> n;
  vector<int> v(n + 1), p(n + 1), id(n + 1);
  for (int x = 1; x <= n; x++)
    cin >> v[x], id[x] = x;
  for (int x = 1, u; x <= n; x++)
    cin >> u, p[u] = x;
  sort(id.begin() + 1, id.end(), [&](auto a, auto b) { return v[a] > v[b]; });
  priority_queue<int, vector<int>, greater<int>> pq;
  long long ans = 0, ans2 = 0;
  int sb = 1;
  for (int x = 1; x <= n; x++) {
    while (!pq.empty() && pq.top() < x)
      pq.pop();
    while (sb <= n && pq.size() < x) {
      if (p[id[sb]] >= x)
        pq.push(p[id[sb]]);
      sb++;
    }
    if (pq.size() == x) {
      if (1ll * x * v[id[sb - 1]] > ans)
        ans = 1ll * x * v[id[sb - 1]], ans2 = x;
    } else
      break;
  }
  cout << ans << ' ' << ans2 << endl;
}


// https://github.com/VaHiX/CodeForces/