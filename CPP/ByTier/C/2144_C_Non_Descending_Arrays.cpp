// Problem: CF 2144 C - Non-Descending Arrays
// https://codeforces.com/contest/2144/problem/C

#include <stdio.h>
#include <algorithm>
#include <iostream>

#define mod 998244353
using namespace std;
int a[1005], b[1005];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    long long ans = 2; // Start with 2 because each position has at least one valid choice (swap or not swap)
    cin >> n;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
      scanf("%d", &b[i]);
    for (int i = 1; i < n; i++) {
      // For each adjacent pair of positions, determine valid swaps
      int x = max(a[i], b[i]), y = a[i] + b[i] - x, z = max(a[i + 1], b[i + 1]),
          w = a[i + 1] + b[i + 1] - z, opt = 0;
      // Check if swapping or not swapping keeps both arrays sorted in non-descending order
      if (z >= x && w >= y)
        opt++;
      if (z >= y && w >= x)
        opt++;
      ans = ans * opt % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/