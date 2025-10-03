// Problem: CF 2102 F - Mani and Segments
// https://codeforces.com/contest/2102/problem/F

/*
F. Mani and Segments

Algorithm: This code uses a combination of monotonic stacks and dynamic programming to compute for each subarray the longest increasing and decreasing subsequences (LIS/LDS) and checks if the condition LIS + LDS = length + 1 holds.
- Uses two passes over the array: forward and reverse, computing for each position how far back a certain element can extend an increasing/decreasing sequence.
- For each subarray, it uses precomputed values to determine valid ranges.
Time Complexity: O(n) per test case
Space Complexity: O(n)

*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
#define ll long long
#define pb push_back
#define pii pair<int, int>
#define f first
#define s second
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define all(x) x.begin(), x.end()
#define vec vector
void solve() {
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vec<vec<int>> bound(2, vec<int>(n)); // Store bounds for increasing and decreasing sequences
  auto fillin = [&](int m) {
    vec<int> hi(n), lo(n); // hi[i] stores last index of element > a[i], lo[i] for < a[i]
    stack<int> sh, sl; // stacks to maintain monotonicity for max and min
    for (int i = 0; i < n; i++) {
      while (sh.size() && a[i] > a[sh.top()]) {
        sh.pop(); // Remove elements from stack if current is larger
      }
      while (sl.size() && a[i] < a[sl.top()]) {
        sl.pop(); // Remove elements from stack if current is smaller
      }
      hi[i] = (sh.empty() ? -1 : sh.top()); // Last index where element is greater
      lo[i] = (sl.empty() ? -1 : sl.top()); // Last index where element is smaller
      sh.push(i);
      sl.push(i);
    }
    bound[m][0] = 0;
    for (int i = 1; i < n; i++) {
      bound[m][i] = bound[m][i - 1];
      if (a[i] > a[i - 1] && hi[i] < hi[i - 1]) { // If increasing and previous has a larger bound
        chmax(bound[m][i], hi[i - 1] + 1); // Update max bound
      }
      if (a[i] < a[i - 1] && lo[i] < lo[i - 1]) { // If decreasing and previous has a larger bound
        chmax(bound[m][i], lo[i - 1] + 1); // Update max bound
      }
    }
    if (m == 1) {
      vec<int> b2 = bound[1]; // Copy of reverse result for mirroring
      for (int i = 0; i < n; i++) {
        bound[m][i] = n - b2[n - i - 1] - 1; // Mirror indices to simulate reverse scan in forward pass
      }
    }
    reverse(all(a)); // Reverse to compute reverse pass
  };
  fillin(0); // Forward pass
  fillin(1); // Backward pass
  int last_r = bound[1][0]; // Start of the rightmost range
  ll ans = last_r + 1; // Initialize result with first subarray count
  for (int i = 1; i < n; i++) {
    ans += (bound[1][i] - i + 1); // Add valid subarrays from current position to i
    ans += (ll)(bound[1][i] - last_r) * (i - bound[0][i]); // Count contribution from ranges
    last_r = bound[1][i]; // Update the rightmost boundary for next iteration
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/