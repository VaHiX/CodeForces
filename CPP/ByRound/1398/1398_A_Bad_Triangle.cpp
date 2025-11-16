// Problem: CF 1398 A - Bad Triangle
// https://codeforces.com/contest/1398/problem/A

/*
算法/技术: 
    1. 由于数组已按非递减顺序排序，我们可以通过比较最大边与另外两边之和的关系来判断是否能构成非退化三角形。
    2. 如果对于某个三元组 (a[i], a[j], a[k])，其中 a[k] 是最大边（即 a[k] >= a[j] 且 a[k] >= a[i]），若 a[k] >= a[i] + a[j]，则无法构成三角形。
    3. 由于数组已排序，我们可以从索引 1 开始遍历到 n-2，检查 a[n-1] 是否大于等于 a[0] + a[p]，这样就能找到一个不构成三角形的三元组。
    4. 时间复杂度 O(n)，空间复杂度 O(1)（不考虑输入数组存储空间）。

时间复杂度: O(n)
空间复杂度: O(1)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long idx(-1);
    // 遍历中间元素，寻找不满足三角不等式的三元组
    for (long p = 1; p < n - 1; p++) {
      if (a[n - 1] >= a[0] + a[p]) {
        idx = p + 1;
        break;
      }
    }
    if (idx > 0) {
      // 如果找到了这样的组合，输出索引（注意题目索引从1开始）
      printf("1 %ld %ld\n", idx, n);
    } else {
      // 否则没有这样的三元组
      puts("-1");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/