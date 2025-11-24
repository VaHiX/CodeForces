// Problem: CF 2140 D - A Cruel Segment's Thesis
// https://codeforces.com/contest/2140/problem/D

/*
D. A Cruel Segment's Thesis

Algorithm/Techniques:
- Greedy algorithm with sorting and prefix sum techniques.
- The key insight is to combine segments optimally in pairs to maximize the final segment length.
- We simulate a process where we greedily merge segments by choosing two segments such that their combined segment has maximum possible length.
- Sorting based on a custom value allows us to select optimal pairs.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the segments and auxiliary arrays.

*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

void solve() {
  int n;
  cin >> n;
  vector<array<int, 2>> a(n), b(n); // a stores original segments, b stores transformed segments
  ll h = 0, ans = -1e18; // h is the sum of all segment lengths, ans tracks maximum total length

  for (int i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1]; // Read segment [l, r]
    h += a[i][1]; // Accumulate segment lengths
    b[i][0] = -a[i][0] - a[i][1], b[i][1] = a[i][1]; // Transform segments for sorting
  }

  sort(b.begin(), b.end(), greater<array<int, 2>>()); // Sort based on transformed values in descending order

  for (int i = 0; i < n / 2; i++)
    h += b[i][0]; // Add the first half of transformed segments to h

  if (n % 2 == 0)
    ans = h; // If even number of segments, the result is already computed
  else {
    // For odd number of segments:
    for (int i = 0; i < n; i++) {
      if (i < n / 2)
        // Compute candidate answer by removing and adding segments
        ans = max(ans, h - b[i][1] - b[i][0] + b[n / 2][0]);
      else
        // For remaining segments, compute another candidate
        ans = max(ans, h - b[i][1]);
    }
  }

  for (int i = 0; i < n; i++)
    ans += a[i][1] - a[i][0]; // Add back the original segment lengths

  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int nc;
  cin >> nc;
  while (nc--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/