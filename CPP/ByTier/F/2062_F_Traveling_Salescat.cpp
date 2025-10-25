// Problem: CF 2062 F - Traveling Salescat
// https://codeforces.com/contest/2062/problem/F

/*
Algorithm: Dynamic Programming with Coordinate Transformation
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This solution uses a coordinate transformation technique to simplify the distance calculation.
The key insight is to transform each city (a[i], b[i]) into (a[i] + b[i], a[i] - b[i]).
Then, we apply dynamic programming to find the minimum cost path for each k from 2 to n.
The DP state tracks different configurations for the last two nodes in the path.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
#define int long long
const int N = 3005, inf = 2e16;
struct node {
  int x, y;
} a[N];
int tmp[N][3], f[N][3], ans[N], T, n;
bool cmp(node A, node B) { return A.y < B.y; }
signed main() {
  int i, x, y, j;
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld", &n);
    for (i = 1; i <= n; i++) {
      scanf("%lld%lld", &x, &y);
      a[i] = (node){x + y, x - y};  // Transform coordinates
    }
    sort(a + 1, a + 1 + n, cmp);  // Sort by transformed y-coordinate
    f[0][0] = 0, f[0][1] = f[0][2] = inf;
    for (i = 1; i <= n; i++) {
      ans[i] = inf;
      f[i][0] = f[i][1] = f[i][2] = inf;
    }
    for (i = 1; i <= n; i++) {
      for (j = 0; j <= i; j++) {
        tmp[j][0] = f[j][0];
        tmp[j][1] = f[j][1];
        tmp[j][2] = f[j][2];
      }
      tmp[1][0] = min(tmp[1][0], 2 * a[i].x - 2 * a[i].y);  // Update first state
      tmp[1][1] = min(tmp[1][1], a[i].x - 2 * a[i].y + a[i].y);  // Update second state
      for (j = 2; j <= i; j++) {
        tmp[j][0] = min(tmp[j][0], f[j - 1][0] + 2 * a[i].x);  // DP transition
        tmp[j][1] = min(tmp[j][1], min(f[j - 1][1] + 2 * a[i].x,
                                       f[j - 1][0] + a[i].x + a[i].y));
        tmp[j][2] = min(tmp[j][2], min(f[j - 1][2] + 2 * a[i].x,
                                       f[j - 1][1] + a[i].x - a[i].y));
        ans[j] = min(ans[j], tmp[j][2] + 2 * a[i].y);  // Calculate final answer
      }
      for (j = 0; j <= i; j++) {
        f[j][0] = tmp[j][0];
        f[j][1] = tmp[j][1];
        f[j][2] = tmp[j][2];
      }
    }
    for (i = 2; i <= n; i++)
      printf("%lld ", ans[i] / 2);  // Output result, divide by 2 due to transformation
    putchar('\n');
  }
}


// https://github.com/VaHiX/CodeForces/