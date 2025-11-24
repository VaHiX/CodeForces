// Problem: CF 1829 G - Hits Different
// https://codeforces.com/contest/1829/problem/G

/*
Algorithm/Techniques: Dynamic Programming with Preprocessing
Time Complexity: O(N) for precalculation + O(1) per query where N = 1e6
Space Complexity: O(N) for the DP array f

This solution uses dynamic programming to precompute the sum of all falling cans
for each starting position n^2. The pyramid structure is such that when a can at
position n^2 is hit, all cans above it in the pyramid fall, following a specific pattern.
The recurrence relation builds up the cumulative sum of squares of the numbers in
the falling cans, based on the row and position in the pyramid.
*/
#include <iostream>

using namespace std;
using LL = unsigned long long;
const int N = 1e6 + 10;
LL f[N];

void init() {
  f[1] = 1;  // Base case: if we hit 1^2, only 1^2 falls
  for (LL i = 2, j = 0, cnt = 2; i <= 1e6; i++) {
    j++;  // Position in current row
    int flg = 0;  // Flag to track how many previous sums were added
    f[i] = i * i;  // Every node contributes its own square value
    if (j != 1)  // If not the first element of the row
      f[i] += f[i - cnt], flg++;  // Add the sum from one row above
    if (j != cnt)  // If not the last element of the row
      f[i] += f[i - cnt + 1], flg++;  // Add the sum from one row above, shifted by 1
    if (flg == 2)  // If both previous contributions were used, subtract their overlap
      f[i] -= f[i - cnt - cnt + 2];  // Remove double counted value
    if (j == cnt)  // When we reach the end of the current row
      cnt++, j = 0;  // Move to next row, reset position counter
  }
}

void solve() {
  int n;
  cin >> n;
  LL ans = f[n];  // Retrieve precomputed result
  cout << ans << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();  // Precompute the dp array
  int tt = 1;
  cin >> tt;
  while (tt--)
    solve();  // Process all test cases
  return 0;
}


// https://github.com/VaHiX/CodeForces/