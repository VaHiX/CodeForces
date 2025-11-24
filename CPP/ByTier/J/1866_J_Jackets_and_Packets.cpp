// Problem: CF 1866 J - Jackets and Packets
// https://codeforces.com/contest/1866/problem/J

/*
J. Jackets and Packets
Algorithms/Techniques: Dynamic Programming with State Compression
Time Complexity: O(N^3)
Space Complexity: O(N^2)

This problem involves determining the minimum time to pack all jackets into packets,
where each packet contains jackets of the same color. Two operations are available:
1. Move one jacket from one stack to another (costs Y per move).
2. Pack multiple jackets of the same color (costs X per packing operation).

The solution uses dynamic programming with a state dp[i][j] representing the minimum time
to process jackets from index i to j in the left stack, considering how they can be packed.

The array 'a' stores unique colors in order, and 'b' stores their counts.
*/

#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;
const int N = 410;
const ll INF = 1e16;
ll dp[N][N], g[N][2];
int n, x, y;
int a[N], b[N];

int main() {
  scanf("%d%d%d", &n, &x, &y);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  int m = 1;
  b[1] = 1;
  for (int i = 2; i <= n; i++)
    if (a[i] == a[m]) {
      b[m]++;
    } else {
      a[++m] = a[i];
      b[m] = 1;
    }
  n = m; // Update n to number of unique colors
  for (int i = n; i >= 1; i--) {
    dp[i][i] = x;
    for (int j = i; j <= n; j++)
      g[j][0] = g[j][1] = INF; // Initialize g array with infinity values
    g[i][0] = 1ll * b[i] * y;   // Cost of placing color i once at top (1 way)
    g[i][1] = 2ll * b[i] * y;   // Cost of placing color i twice at top (2 ways)
    for (int j = i + 1; j <= n; j++)
      dp[i][j] = dp[i + 1][j] + x; // Default case: move all from left to right then handle
    for (int j = i + 1; j <= n; j++)
      if (a[j] == a[i]) { // Only consider same color as a[i]
        ll s = INF;
        for (int k = i; k < j; k++)
          if (a[k] == a[i]) { // Only consider same color as a[i]
            // Update g[j][0] and g[j][1]:
            // 0th index = minimal cost of placing one or zero elements of type a[i] on top
            // 1st index = minimal cost of placing two elements of type a[i] on top
            g[j][0] = min(g[k][0] + 1ll * b[j] * y + dp[k + 1][j - 1], g[j][0]);
            g[j][1] = min(g[k][1] + 2ll * b[j] * y + dp[k + 1][j - 1], g[j][1]);
            // s is the minimal cost to pack a[i] from i to j
            s = min(s, g[j][0] + x);
            s = min(s, g[k][1] + dp[k + 1][j - 1] + x);
          }
        dp[i][j] = min(dp[i][j], s);
        // Propagate the best way to divide intervals
        for (int k = j + 1; k <= n; k++)
          dp[i][k] = min(dp[i][k], dp[i][j] + dp[j + 1][k]);
      }
  }
  printf("%lld\n", dp[1][n]);
}


// https://github.com/VaHiX/codeForces/