// Problem: CF 1951 C - Ticket Hoarding
// https://codeforces.com/contest/1951/problem/C

/*
算法/技术: 贪心 + 优先队列（或排序 + 预处理）
时间复杂度: O(n log n)，其中 n 是天数。主要由排序决定。
空间复杂度: O(n)，用于存储价格数组。

题目描述:
给定 n 天的票价，每天最多可以购买 m 张票，且购买 x 张票后，之后每一天的价格都增加 x。
目标是购买总共 k 张票，使得总花费最少。

解法思路:
1. 首先对价格进行排序，这样可以贪心地从便宜的日期开始买票。
2. 从第一天开始遍历：
   - 如果剩余需要买的票数 k 小于等于当天能买的最大票数 m，则直接买下剩余的票。
   - 否则先买满 m 张票，并更新累积的价格增量 pr。
3. 每次购买票时，实际支付的价格是当前价格加上前面已购买的票数导致的价格增量。

关键点:
- 我们在每一天买票前，用 pr 记录前面所有天数买票所增加的价格。
- 每次购买完后，更新 pr = pr + m（因为增加了 m 每天价格）。
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
constexpr int Spp{1 << 20};
char buf[Spp], *p1, *p2;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, Spp, stdin), p1 == p2)         \
       ? EOF                                                                   \
       : *p1++)
template <typename T> void read(T &x) {
  char c;
  int f{1};
  do
    x = (c = getchar()) ^ 48;
  while (!isdigit(c) && c != '-');
  if (x == 29)
    f = -1, x = 0;
  while (isdigit(c = getchar()))
    x = (x << 3) + (x << 1) + (c ^ 48);
  x *= f;
}
template <typename T, typename... Args> void read(T &x, Args &...args) {
  read(x);
  read(args...);
}
constexpr int N(3e5);
int a[N + 5];
int main() {
  int T;
  read(T);
  while (T--) {
    int n, m, k;
    read(n, m, k);
    for (int i{1}; i <= n; ++i)
      read(a[i]);
    sort(a + 1, a + 1 + n); // 对价格排序以贪心选取最低价
    long long pr{0}, ans{0}; // pr: 到目前为止的累计价格增量; ans: 总花费
    for (int i{1}; i <= n; ++i) {
      if (k <= m) {
        // 如果剩下的票不足或等于最大购票数，一次性全部买下
        ans += (pr + a[i]) * k;
        break;
      }
      k -= m; // 减去本次买满 m 张票的票数
      ans += m * (pr + a[i]); // 买 m 张票的花费
      pr += m; // 累计价格增量
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/