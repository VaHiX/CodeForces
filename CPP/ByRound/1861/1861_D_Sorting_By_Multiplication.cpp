// Problem: CF 1861 D - Sorting By Multiplication
// https://codeforces.com/contest/1861/problem/D

/*
算法/技术: 贪心 + 前缀和 + 后缀和
时间复杂度: O(n)
空间复杂度: O(n)

问题描述:
给定一个正整数数组，可以通过对任意连续子数组乘以任意整数来改变数组元素。
求最少操作次数，使得数组变成严格递增序列。

解题思路:
1. 对于数组中每个位置，我们考虑是否需要将其乘以某个系数以满足递增条件。
2. 预处理前缀数组 pre[i] 表示前 i 个元素中违反递增条件的位置数（即需要操作的次数）。
3. 预处理后缀数组 suf[i] 表示从 i 到末尾违反递增条件的位置数。
4. 枚举分界点 i，将数组分为两部分：
   - [1, i] 部分需操作 pre[i] 次
   - [i+1, n] 部分需操作 suf[i+1] 次
5. 总操作次数即为 pre[i] + suf[i+1]，取最小值。
*/

#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <utility>

#define ll long long
#define enl putchar('\n')
#define all(x) (x).begin(), (x).end()
#define debug(x) printf(" " #x ":%d\n", x);
using namespace std;
const int MAXN = 1e6 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
typedef pair<int, int> pii;
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 21], *o = obuf, of[35];
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline ll qpow(ll a, ll n) {
  ll res = 1;
  while (n) {
    if (n & 1)
      res = res * a % mod;
    n >>= 1;
    a = a * a % mod;
  }
  return res;
}
inline int read() {
  int s = 0, f = 1;
  char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-')
      f = -1;
  for (; isdigit(c); c = gc())
    s = s * 10 + c - '0';
  return s * f;
}
inline void read(int *a, int n) {
  for (int i = 1; i <= n; ++i)
    a[i] = read();
}
inline int inal(char *s) {
  int n = 0;
  for (s[0] = gc(); !isalpha(s[0]); s[0] = gc())
    ;
  for (; isalpha(s[n]); s[++n] = gc())
    ;
  return s[n] = 0, n;
}
int n, m, q;
int a[MAXN], pre[MAXN], suf[MAXN];
signed main(signed argc, char const *argv[]) {
  clock_t c1 = clock();
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif
  a[0] = inf;
  int TxT = read();
  while (TxT--) {
    n = read();
    read(a, n);
    suf[n + 1] = 0;
    a[n + 1] = inf;
    for (int i = 1; i <= n; ++i)
      pre[i] = pre[i - 1] + (a[i] >= a[i - 1]); // 如果当前元素大于等于前一个元素，则无需操作（计数为0）
    for (int i = 1; i <= n; ++i)
      pre[i]++; // 加上当前位置的初始计数（前缀数组偏移）
    for (int i = n; i >= 1; --i)
      suf[i] = suf[i + 1] + (a[i] >= a[i + 1]); // 从后往前统计
    int ans = inf;
    for (int i = 0; i <= n; ++i)
      ans = min(ans, pre[i] + suf[i + 1]); // 枚举分界点，计算最少操作次数
    printf("%d\n", ans);
  }
#ifdef LOCAL
end:
  cout << "Time Used:" << clock() - c1 << "ms" << endl;
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/