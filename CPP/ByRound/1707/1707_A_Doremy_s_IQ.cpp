// Problem: CF 1707 A - Doremy's IQ
// https://codeforces.com/contest/1707/problem/A

/*
算法/技术: 贪心算法
时间复杂度: O(n)，其中 n 是比赛数量。我们只需遍历一次数组。
空间复杂度: O(n)，用于存储比赛难度和结果字符串。

本代码使用贪心策略从后往前处理每个比赛，以使 Doremy 的 IQ 最大化地被利用，
从而能够参加尽可能多的比赛。
*/
#include <iostream>

using namespace std;
const int N = 2e5 + 3;
int a[N], ans[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, i, j, k, T;
  for (cin >> T; T--;) {
    cin >> n >> k, j = 0; // j 表示当前 IQ，k 表示初始 IQ
    for (i = 1; i <= n; ++i)
      cin >> a[i]; // 读入每个比赛的难度
    for (i = n; i; --i) { // 从后往前处理比赛
      if (j < a[i]) { // 如果当前 IQ 小于比赛难度
        if (j == k) // 如果当前 IQ 等于初始 IQ
          ans[i] = 0; // 不能参加这场比赛
        else
          ans[i] = 1, ++j; // 可以参加，IQ 增加
      } else
        ans[i] = 1; // 当前 IQ 足够，可以参加
    }
    for (i = 1; i <= n; ++i)
      cout << ans[i]; // 输出结果
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/