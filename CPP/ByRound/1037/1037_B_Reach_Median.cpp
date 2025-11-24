// Problem: CF 1037 B - Reach Median
// https://codeforces.com/contest/1037/problem/B

/*
B. Reach Median
算法/技术: 排序 + 贪心
时间复杂度: O(n log n)
空间复杂度: O(n)

给定一个包含n个整数的数组和目标值s，n为奇数。
每次操作可以将任意元素+1或-1。求使数组中位数变为s的最少操作次数。

解法：
1. 先对数组排序，这样中位数位置就固定了（第(n/2)个元素）
2. 贪心策略：
   - 对于排好序后的数组中位于前n/2位置的元素，如果它们大于s，则需要减少到s
   - 对于排好序后的数组中位于后n/2位置的元素，如果它们小于s，则需要增加到s
   - 中位数本身不需要改变
3. 遍历排序后的数组，根据上述规则累计操作次数

注意：题目中的条件判断逻辑利用了数组长度是奇数这一性质。
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, s;
  scanf("%lld %lld", &n, &s);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end()); // 对数组进行排序，方便找到中位数
  ll cnt(0);
  for (ll p = 0; p < n; p++) {
    // 如果当前元素在前半部分（不包括中位数），且大于s，则减少到s
    if ((2 * p + 1 <= n) && (a[p] > s)) {
      cnt += (a[p] - s);
    } else if ((2 * p + 1 >= n) && (a[p] < s)) {
      // 如果当前元素在后半部分（不包括中位数），且小于s，则增加到s
      cnt += (s - a[p]);
    }
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/