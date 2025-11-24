// Problem: CF 2080 B - Best Runner
// https://codeforces.com/contest/2080/problem/B

/*
 * Problem: Best Runner
 * Task: Determine the maximum number of full tracks a single runner can complete within T seconds.
 *
 * Algorithms/Techniques:
 *   - Two-pointer technique with prefix/suffix processing for each runner's starting track
 *   - Greedy approach to maximize track completions by prioritizing shorter tracks
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 */
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 300010;
int a[N], b[N]; // a[] stores track lengths, b[] stores runner start positions
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, m, p, ans = 0; // n: tracks, m: runners, p: training time, ans: result
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  b[m + 1] = n + 1; // sentinel value to simplify boundary checks
  for (int i = 1; i <= m; i++) {
    // Process backwards from current runner's start position
    for (int j = b[i], tot = p, cnt = 0; j > b[i - 1] && tot >= 0; j--) {
      ans = max(ans, cnt + tot / a[j]); // update maximum tracks possible
      cnt++, tot -= a[j];               // increment count and subtract time
    }
    // Process forwards from current runner's start position
    for (int j = b[i], tot = p, cnt = 0; j < b[i + 1] && tot >= 0; j++) {
      ans = max(ans, cnt + tot / a[j]); // update maximum tracks possible
      cnt++, tot -= a[j];               // increment count and subtract time
    }
  }
  cout << ans;
}


// https://github.com/VaHiX/codeForces/