// Problem: CF 2082 B - Floor or Ceil
// https://codeforces.com/contest/2082/problem/B

/*
B. Floor or Ceil
Algorithm: Simulation with optimization
Time Complexity: O(1) per test case (since n and m are capped at 30)
Space Complexity: O(1)

The problem involves applying exactly n operations of type "floor division by 2" 
and m operations of type "ceil division by 2" to an integer x, in any order.
We need to compute the minimum and maximum possible values of x after all operations.

Key insights:
- Applying floor(x/2) reduces x faster than ceil(x/2), so to minimize x we prefer floor.
- To maximize x, we prefer ceil because it often rounds up, increasing value.
- Operations beyond 30 can be ignored due to integer underflow (x >> 30 becomes 0).
*/

#include <stddef.h>
#include <iostream>
#include <algorithm>

using namespace std;
int T, x, y, n, m;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> T;
  while (T--) {
    cin >> x >> n >> m;
    y = x;                    // Store original value for max calculation
    m = min(m, 30);           // Cap m to avoid unnecessary computations
    n = min(n, 30);           // Cap n to avoid unnecessary computations
    x >>= n;                  // Apply floor operations (equivalent to right shift by n)
    for (int i = 1; i <= m; i++) {
      x = (x + 1) / 2;        // Apply ceil operation: (x+1)/2 gives ceil(x/2)
      y = (y + 1) / 2;        // Similarly update y
    }
    y >>= n;                  // After all operations, apply remaining floor shift to x
    cout << y << ' ' << x << '\n';
  }
}


// https://github.com/VaHiX/codeForces/