// Problem: CF 1611 F - ATM and Students
// https://codeforces.com/contest/1611/problem/F

/*
Algorithm: Sliding Window Technique
Time Complexity: O(n) - Each element is visited at most twice (once by r, once by l)
Space Complexity: O(1) - Only a few variables used, no extra space proportional to input size

This code finds the maximum number of consecutive students that can be served
starting from some initial amount s in the ATM. It uses a sliding window approach
to explore all possible contiguous subsequences and tracks the best valid interval.

The key idea is to expand the window (using r) as long as the balance remains non-negative,
and shrink it (using l) when a negative balance occurs.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int n, a[200005];
long long s;
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    int L = 1, R = 0;  // To store the start and end of best interval
    int l = 1, r = 0;  // Sliding window pointers
    while (l <= n) {
      // Expand window while balance is non-negative and r hasn't reached end
      while (s >= 0 && r < n) {
        s += a[++r];  // Add next student's transaction
        // Update best interval if current is better
        if (s >= 0 && r - l > R - L)
          L = l, R = r;
      }
      s -= a[l++];  // Remove leftmost element from window and move l forward
    }
    if (L > R)
      puts("-1");  // No valid interval found
    else
      cout << L << ' ' << R << endl;  // Print starting and ending student indices
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/