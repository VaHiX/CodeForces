// Problem: CF 1016 C - Vasya And The Mushrooms
// https://codeforces.com/contest/1016/problem/C

/*
C. Vasya And The Mushrooms
Algorithms/Techniques: Dynamic Programming, Prefix/Suffix Computation

Time Complexity: O(n)
Space Complexity: O(n)

Vasya's house is situated in a forest, and there is a mushroom glade near it. 
The glade consists of two rows, each of which can be divided into n consecutive cells. 
For each cell Vasya knows how fast the mushrooms grow in this cell (more formally,
how many grams of mushrooms grow in this cell each minute). Vasya spends exactly one 
minute to move to some adjacent cell. Vasya cannot leave the glade. Two cells are 
considered adjacent if they share a common side. When Vasya enters some cell, he 
instantly collects all the mushrooms growing there.

Vasya begins his journey in the left upper cell. Every minute Vasya must move to some 
adjacent cell, he cannot wait for the mushrooms to grow. He wants to visit all the cells 
exactly once and maximize the total weight of the collected mushrooms. Initially, all 
mushrooms have a weight of 0. Note that Vasya doesn't need to return to the starting cell.

Help Vasya! Calculate the maximum total weight of mushrooms he can collect.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
int n, a[2][maxn];
ll suf[maxn], sum[maxn], pre[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[0][i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[1][i]);

  // Compute suffix sums of total mushrooms in each position
  for (int i = n; i >= 1; i--)
    sum[i] = sum[i + 1] + a[0][i] + a[1][i];

  // Precompute suffix contribution: how much value can be gained starting from position i onward,
  // considering the optimal path ending at that point.
  for (int i = n; i >= 1; i--) {
    suf[i] =
        suf[i + 2] - 2LL * sum[i + 2] + (2LL * (i - 1) * a[(i % 2) ^ 1][i]) +
        ((2LL * i - 1) * a[(i % 2) ^ 1][i + 1]) +
        ((2LL * n - 2LL) * a[i % 2][i + 1]) + ((2LL * n - 1LL) * a[i % 2][i]);
  }

  ll ans = 0;
  // Compute prefix gains and check maximum combined with suffix values
  for (int i = 1; i <= n + 1; i++) {
    ans = max(ans, pre[i - 1] + suf[i]);
    pre[i] = pre[i - 1] + ((2LL * i - 2LL) * a[(i % 2) ^ 1][i] +
                           ((2LL * i - 1LL) * a[i % 2][i]));
  }
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/codeForces/