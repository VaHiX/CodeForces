// Problem: CF 2056 A - Shape Perimeter
// https://codeforces.com/contest/2056/problem/A

/*
 * Problem: Shape Perimeter
 * Algorithm: Geometric calculation using difference in coordinates
 * Time Complexity: O(n) per test case, where n is the number of operations
 * Space Complexity: O(1), only using a few variables for computation
 *
 * The approach calculates the total perimeter by tracking how the stamp
 * moves across the paper and accumulating the contribution of each step.
 * For the first stamp, we add 4*m (full square perimeter).
 * For subsequent stamps, we add 2*(x + y) which represents
 * the additional exposed edges due to movement in x and y directions.
 */

#include <stdio.h>
#include <iostream>

#define ll long long
using namespace std;
const ll N = 1e4 + 10, INF = 1e9 + 10, M = 1e9 + 7;
int n, m;
inline ll read() {
  ll f = 1, x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int main() {
  int T = read();
  while (T--) {
    n = read(), m = read();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      int x = read(), y = read();
      if (i == 1)
        ans += 4 * m; // First stamp contributes full perimeter
      else {
        ans = ans + 2 * (x + y); // Additional edges from movement
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/