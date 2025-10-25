// Problem: CF 2137 F - Prefix Maximum Invariance
// https://codeforces.com/contest/2137/problem/F

/*
F. Prefix Maximum Invariance
Algorithm: Using monotonic stack and binary search to compute the contribution of each element in subarrays,
           leveraging the property that prefix maximums must be preserved.

Time Complexity: O(n) amortized per test case due to stack operations and binary search.
Space Complexity: O(n) for arrays and stack.

*/

#include <algorithm>
#include <iostream>

using namespace std;
int a[200000], b[200000], l[200000]; // a, b are input arrays; l stores left boundaries for each position
int stk[200000], p;                    // stk is monotonic stack; p is stack pointer
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T, n, i, L, R, mid;
  long long ans;
  for (cin >> T; T > 0; T--) {
    cin >> n;
    for (i = 0; i < n; i++)
      cin >> a[i];       // read array a
    for (i = 0; i < n; i++)
      cin >> b[i];       // read array b
    p = 0;               // reset stack pointer
    for (i = 0; i < n; i++) {
      // Maintain monotonic decreasing stack: remove elements smaller than current a[i]
      while (p > 0 && a[stk[p - 1]] < a[i])
        p--;
      if (a[i] == b[i])
        l[i] = i;         // if a[i] == b[i], left boundary is i
      else {
        L = -1;
        R = p;
        // Binary search to find the largest index in stack such that a[stk[mid]] >= max(a[i], b[i])
        while (R - L > 1) {
          mid = (L + R) / 2;
          if (a[stk[mid]] >= max(a[i], b[i]))
            L = mid;
          else
            R = mid;
        }
        if (L == -1)
          l[i] = -1;        // no valid previous element found
        else
          l[i] = stk[L];    // assign the left boundary
      }
      stk[p] = i;           // push current index onto stack
      p++;
    }
    ans = 0;
    for (i = 0; i < n; i++)
      ans += (long long)(l[i] + 1) * (long long)(n - i);  // accumulate total contribution
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/