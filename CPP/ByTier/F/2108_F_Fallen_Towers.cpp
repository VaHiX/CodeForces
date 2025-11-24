// Problem: CF 2108 F - Fallen Towers
// https://codeforces.com/contest/2108/problem/F

/*
F. Fallen Towers
Algorithms/Techniques: Binary search on answer + difference array technique

Time Complexity: O(n * log(n)) per test case
Space Complexity: O(n)

The problem asks to find the maximum MEX (minimum excludant) of an array after performing a series of operations.
Each operation allows knocking down a tower and increasing the heights of subsequent towers.
The final array must remain non-decreasing.

We use binary search on the answer to determine the maximum possible MEX.
For each candidate MEX value, we check if it's feasible using a difference array technique
to simulate the sequence of operations efficiently.
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const ll N = 1e5 + 2;
ll a[N], b[N], od[N], n;

// Function to check if MEX value x is achievable
bool chk(ll x) {
  b[n] = x - 1, od[n] = 0; // Initialize last element of b and difference array
  for (int i = n - 1; i >= 1; --i)
    b[i] = max(0ll, b[i + 1] - 1), od[i] = 0; // Propagate decreasing constraint from right to left
  ll cur = 0;
  for (int i = 1; i <= n; ++i) {
    cur -= od[i] - (i > 1); // Adjust current value considering previous operations
    if (cur < b[i])
      return 0; // Not enough blocks to maintain non-decreasing order
    ll x = cur + a[i] - b[i]; // Compute how much we can knock down tower i
    ++od[1 + min(n, i + x)]; // Update difference array for range update
  }
  return 1;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  ll l = 1, r = n, ans = l;
  while (l <= r) {
    ll m = (l + r) / 2;
    if (chk(m)) {
      l = m + 1;
      ans = m;
    } else
      r = m - 1;
  }
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/