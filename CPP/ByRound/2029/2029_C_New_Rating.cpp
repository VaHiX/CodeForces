// Problem: CF 2029 C - New Rating
// https://codeforces.com/contest/2029/problem/C

/*
C. New Rating
Algorithms/Techniques: Greedy approach with prefix and suffix tracking.
Time Complexity: O(n) per test case.
Space Complexity: O(1).

The problem involves selecting an interval [l,r] to skip contests such that the final rating x is maximized.
Rating x changes based on comparison with contest ratings:
- If a[i] > x, x increases by 1
- If a[i] < x, x decreases by 1
- If a[i] == x, x remains unchanged

The approach tracks the maximum possible value of x while simulating rating updates,
and considers skipping each possible interval [l,r] to find the optimal result.
*/

#include <algorithm>
#include <iostream>

using namespace std;

inline void solve() {
  int n;
  cin >> n;
  int x = 0, y = 0, z = -1; // x: current rating, y: max rating so far, z: max rating after skipping interval
  for (int i = 1; i <= n; ++i) {
    int a;
    cin >> a;
    if (x < a)
      ++x;   // Increase rating if current contest rating is greater than x
    if (x > a)
      --x;   // Decrease rating if current contest rating is less than x
    if (z < a)
      ++z;   // Update z to track maximum value of a seen so far, but not directly related to x
    if (z > a)
      --z;   // Decrement z if it exceeds a
    z = max(z, y), y = max(y, x);  // Keep updating max rating seen so far
  }
  cout << z << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/