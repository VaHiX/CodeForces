// Problem: CF 2019 D - Speedbreaker
// https://codeforces.com/contest/2019/problem/D

/*
D. Speedbreaker
Algorithm: Two-pointers + Sliding window approach
Time Complexity: O(n) amortized per test case
Space Complexity: O(n) for input vector

The problem asks to find how many cities can be chosen as the starting city such that
all cities are conquered on or before their respective deadlines. The conquest must
follow adjacency rules. 

This solution uses reverse iteration from n down to 1, maintaining a window [l, r]
of valid positions that could have been conquered at time t. For each step, we update
the left and right boundaries of this valid window based on the current deadline,
and check if it's possible to build a valid strategy.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define per(i, r, l) for (int i = r; i >= l; i--)
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  int l = 0, r = n - 1;
  int L = 0, R = n - 1;
  per(t, n, 1) {
    // Move l forward while a[l] > t to find the first valid left point
    while (l < n && a[l] > t)
      l++;
    // Move r backward while a[r] > t to find the first valid right point
    while (r >= 0 && a[r] > t)
      r--;
    // Update the maximum required right boundary for time t
    L = max(L, r - t + 1);
    // Update the minimum required left boundary for time t
    R = min(R, l + t - 1);
    // If current valid region is larger than t, impossible to win
    if (r - l + 1 > t) {
      cout << "0\n";
      return;
    }
  }
  // The number of valid starting cities is the size of the final interval [L, R]
  cout << max(R - L + 1, 0) << "\n";
}
int main(int _) {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> _; _--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/