// Problem: CF 2169 C - Range Operation
// https://codeforces.com/contest/2169/problem/C

/*
Purpose: This code solves the problem of maximizing the sum of an array after performing at most one operation,
         where the operation replaces a subarray [l, r] with the value (l + r). The algorithm efficiently computes
         the maximum possible array sum using prefix sums and dynamic programming concepts.

Algorithms/Techniques: Prefix sums, optimized dynamic programming, sliding window idea.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for the prefix sum array.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
#define int long long
const int N = 200005;
int n, a[N], s[N];
signed main() {
  int T, i;
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld", &n);
    s[0] = 0;
    for (i = 1; i <= n; i++)
      scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];
    int mxd = 0, Ans = s[n], mxl = 0;
    for (i = 1; i <= n; i++) {
      // Update mxd: maximum gain we can achieve by choosing a subarray ending at i
      mxd = max(mxd, i * i + i - s[i] + mxl);
      // Update mxl: maximum value of (prefix_sum - i - i*i) seen so far
      mxl = max(mxl, s[i] - i - i * i);
    }
    printf("%lld\n", Ans + mxd);
  }
}


// https://github.com/VaHiX/CodeForces/