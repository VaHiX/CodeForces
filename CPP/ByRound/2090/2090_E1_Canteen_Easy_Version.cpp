// Problem: CF 2090 E1 - Canteen (Easy Version)
// https://codeforces.com/contest/2090/problem/E1

/*
E1. Canteen (Easy Version)
Algorithms/Techniques: Sliding window, simulation optimization

Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This problem simulates a process where two arrays `a` and `b` are processed in rounds.
Each round:
1. For each index i, the minimum of a[i] and b[i] is subtracted from both.
2. A new array c is created such that c[i] = a[(i-1) % n].
3. Array a becomes equal to c.

We want to find the minimum number of rounds to make all elements of `a` zero,
given that we can make exactly k changes to `a` (but here k=0).

The key insight is to simulate the process, extending the arrays to 2*n to handle
circular shifts without explicitly computing them each time. We use a sliding window
approach to check maximum valid window size where prefix sum of (a[i] - b[i]) remains non-negative.
This represents the maximum number of consecutive rounds that can be performed without `a` going negative.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(2 * n), b(2 * n); // Extend arrays to handle circular shift
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    // Duplicate the arrays to simplify circular operations
    for (int i = 0; i < n; i++)
      a[i + n] = a[i], b[i + n] = b[i];
    long long gap = 0, res = 0;
    // Sliding window to find maximum contiguous subarray where prefix sum never goes negative
    for (int l = 0, r = 0; r < 2 * n; r++) {
      gap += a[r] - b[r]; // Accumulate difference between a[i] and b[i]
      if (gap <= 0)       // If we have a valid window
        res = max(res, r - l + 1LL), l = r + 1, gap = 0; // Update result and reset window
    }
    cout << res << "\n";
  }
}


// https://github.com/VaHiX/codeForces/