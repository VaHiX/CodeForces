// Problem: CF 2073 I - Squares on Grid Lines
// https://codeforces.com/contest/2073/problem/I

/*
 * Problem: Count number of ways to place four points on grid boundaries forming a square of given area.
 * Algorithm:
 *   - Preprocessing:
 *     - Mark banned positions based on sum of squares (x^2 + y^2) that cannot form valid squares.
 *     - Use prefix sums and difference arrays for efficient range updates and queries.
 *   - For each query:
 *     - Check if area is valid (banned), else compute result using precomputed values.
 *
 * Time Complexity: O(N^2 + Q) where N = 2000, Q = 100000
 * Space Complexity: O(N) where N = 9000013
 */

#include <math.h>
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
const int N = 9000013;
ll pf[N], del[N], ban[N];

void solve() {
  int n, q;
  cin >> n >> q;
  
  // Mark all possible (i^2 + j^2) sums as banned
  for (int i = 0; i < n; i++)
    for (int j = 0; j + i < n; j++)
      ban[2 * (i * i + j * j)] = 1;

  // Update prefix sums for even squares using difference array technique
  for (int cnt, j = 2; j <= n; j += 2)
    cnt = (n - j + 1) * (n - j + 1), pf[(j - 2) * (j - 2)] += cnt,
    pf[j * j] -= cnt;

  // Process odd squares using difference array technique
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += 2) {
      int cnt = (n - j + 1) * (n - j + 1);
      if (j == i)
        pf[j * j] += cnt * 2, del[j * j] += cnt, pf[j * j * 2] -= cnt * 2,
            del[j * j * 2] -= cnt;
      else
        pf[(j - 2) * (j - 2) + i * i] += cnt * 2, pf[j * j + i * i] -= cnt * 2,
            del[(j - 2) * (j - 2) + i * i] += cnt * 2;
    }

  // Compute prefix sum for final values
  for (int i = 1; i < N; i++)
    pf[i] += pf[i - 1];

  while (q--) {
    string s;
    cin >> s;
    int p = floor((stod(s) + 0.001) * 2); // Convert to integer index for lookup
    if (s[s.size() - 1] == '0' &&
        (s[s.size() - 2] == '5' || (s[s.size() - 2]) == '0')) {
      // Check if area is valid and not banned
      if (ban[p])
        cout << -1 << '\n';
      else
        cout << pf[p] - del[p] << '\n';
    } else
      // For non-special cases, simply output pf value
      cout << pf[p] << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}


// https://github.com/VaHiX/codeForces/