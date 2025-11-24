// Problem: CF 2140 C - Ultimate Value
// https://codeforces.com/contest/2140/problem/C

/*
C. Ultimate Value
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms/Techniques:
- Game theory with optimal play
- Greedy approach combined with prefix/suffix processing
- Dynamic programming concepts (minimizing/maximizing)
- Handling alternating turns between two players with different objectives

Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem involves a game where Alice and Bob take turns swapping elements to maximize/minimize f(a).
The value of f(a) is: cost + (a1 - a2 + a3 - a4 + ... ± an)
Both players play optimally, with Alice trying to maximize and Bob minimizing.
We compute the optimal result by analyzing the contributions of each element in alternating fashion.
*/

#include <algorithm>
#include <stdio.h>
using namespace std;
const int maxn = 2e5 + 7;
#define int long long
int t, n, a[maxn];
signed main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &a[i]);
    }
    int minn = 1e18, ans, sum = 0;
    if (n & 1)
      ans = n - 1; // Initialize answer based on parity
    else
      ans = n - 2;
    for (int i = 1; i <= n; i++) {
      if (i & 1) // odd index: add to sum and track minimum
        minn = min(minn, a[i] * 2 + i), sum += a[i];
      else // even index: update answer using current minn
        ans = max(ans, a[i] * 2 + i - minn), sum -= a[i];
    }
    minn = 1e18;
    for (int i = n; i; i--) {
      if (i & 1) // odd index from back: track minimum
        minn = min(minn, a[i] * 2 - i);
      else // even index from back: update answer
        ans = max(ans, a[i] * 2 - i - minn);
    }
    printf("%lld\n", ans + sum); // Final computed value of f(a)
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/