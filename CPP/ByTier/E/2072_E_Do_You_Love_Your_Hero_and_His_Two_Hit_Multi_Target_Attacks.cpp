// Problem: CF 2072 E - Do You Love Your Hero and His Two-Hit Multi-Target Attacks?
// https://codeforces.com/contest/2072/problem/E

/*
E. Do You Love Your Hero and His Two-Hit Multi-Target Attacks?
Algorithm: Greedy placement of points to satisfy the constraint that exactly k pairs of points have Manhattan distance equal to Euclidean distance.

Time Complexity: O(k) per test case, as we generate points greedily until we reach the required number of valid pairs.
Space Complexity: O(k) for storing coordinates of points.

The key insight is that ρ(i,j)=d(i,j) holds when |x_i - x_j| = 0 or |y_i - y_j| = 0, i.e., when two points lie on the same vertical or horizontal line.

Approach:
- We greedily build the configuration by placing points row by row.
- Each new point is placed at increasing x-coordinates in a fixed y-coordinate to ensure many valid pairs.
- When we exceed n (number of pairs needed), adjust counters to maintain correctness.

This greedy solution works because it ensures that as we add more points:
1. For each new point added, it forms valid pairs with all previously placed points on the same x or y.
2. The number of such pairs grows in a predictable manner and we can precompute where to stop.
*/
#include <iostream>
using namespace std;
int t, n, cnt, _, x_, x[1000], y[1000];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cnt = _ = x_ = 0;
    while (n) {
      if (_ > n)           // If we've exceeded the required pairs, reset and increment x_
        _ = 0, x_++;
      cnt++;               // Increment count of placed points
      x[cnt] = x_, y[cnt] = cnt;  // Assign x-coordinate to current group, y to sequential index
      n -= _;              // Reduce n by number already used in this line
      _++;                // Increment the number of points on same row
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++)
      cout << x[i] << ' ' << y[i] << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/