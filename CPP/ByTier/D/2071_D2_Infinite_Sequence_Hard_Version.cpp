// Problem: CF 2071 D2 - Infinite Sequence (Hard Version)
// https://codeforces.com/contest/2071/problem/D2

/*
D2. Infinite Sequence (Hard Version)
Algorithms/Techniques: Pattern recognition, prefix sums, XOR properties, mathematical optimization for large ranges

Time Complexity: O(n) per test case, where n is the number of initial elements.
Space Complexity: O(n) for storing the sequence and prefix sums.

This code computes the sum of a specific range [l, r] in an infinite binary sequence defined by:
For m > n, a[m] = a[1] ^ a[2] ^ ... ^ a[⌊m/2⌋].
The approach uses a precomputed table with periodic behavior and optimized querying using prefix sums.
*/

#include <algorithm>
#include <iostream>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, l, r, a[N << 1], b[N << 1], s[N << 1], ans;

// Recursive function to calculate sum up to index r using memoization and pattern recognition
int solve(int r) {
  if (r <= n * 2 + 1)
    return s[r]; // If within precomputed range, return directly from prefix sum array
  int t = r - n * 2 - 1; // Offset from the last computed range
  int rr = n + t / 4 * 2 + min(t % 4, 2ll); // Find corresponding index in periodic pattern using math
  int ss = solve(rr) - s[n]; // Subtracts prefix sum to compute difference using recurrence relation
  if (!b[n]) // If the last bit is 0, return total length plus difference
    return s[n * 2 + 1] + ss;
  return s[n * 2 + 1] + t - ss; // Otherwise, use complemented logic
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> l >> r;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      b[i] = b[i - 1] ^ a[i]; // Compute XOR prefix
      s[i] = s[i - 1] + a[i]; // Compute sum prefix
    }
    if (n % 2 == 0) { // Ensure array length is odd to simplify further logic (padding)
      ++n;
      a[n] = b[n / 2];
      b[n] = b[n - 1] ^ a[n];
      s[n] = s[n - 1] + a[n];
    }
    for (int i = n + 1; i <= n * 2 + 1; ++i) {
      a[i] = b[i / 2]; // Fill remaining positions using XOR prefix
      b[i] = b[i - 1] ^ a[i];
      s[i] = s[i - 1] + a[i];
    }
    cout << solve(r) - solve(l - 1) << '\n'; // Query the required range sum using the precomputed values
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/