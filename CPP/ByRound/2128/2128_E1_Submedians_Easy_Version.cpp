// Problem: CF 2128 E1 - Submedians (Easy Version)
// https://codeforces.com/contest/2128/problem/E1

/*
E1. Submedians (Easy Version)
Algorithm: Binary Search on Answer + Prefix Sum with Min Tracking
Time Complexity: O(n * log n) per test case
Space Complexity: O(n)

Binary search is applied on the possible values of submedian (from 1 to n).
For each candidate value 'mid', we transform the array into a binary prefix sum array:
- 1 if a[i] >= mid, else -1.
We then check if there exists a subarray of length at least k such that 
the sum of that subarray is non-negative. This indicates that the median 
of this subarray can be at least mid.

Key idea:
- Use prefix sums to efficiently compute subarray sums.
- For each window of size k, keep track of minimum prefix sum so far.
- If current sum - min prefix sum >= 0, it means we found a valid subarray.
*/

#include <iostream>
using namespace std;
int T, n, k, sum[500005], minn, flag, ans, lans, rans, a[500005], lnum;
signed main() {
  ios ::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    int l = 1, r = n;
    while (l <= r) {
      int mid = (l + r) >> 1; // Binary search on the answer
      sum[0] = 0;
      for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (a[i] >= mid ? 1 : -1); // Build prefix sum with 1/-1
      minn = 1e9, flag = 0;
      for (int i = k; i <= n; i++) {
        if (sum[i - k] < minn)
          minn = sum[i - k], lnum = i - k + 1; // Keep track of minimum prefix sum
        if (sum[i] - minn >= 0) { // If we found a valid subarray
          flag = 1;
          ans = mid, rans = i, lans = lnum;
          break;
        }
      }
      if (flag)
        l = mid + 1; // Try to find a larger valid submedian
      else
        r = mid - 1; // Try smaller value
    }
    cout << ans << ' ' << lans << ' ' << rans << '\n';
  }
}


// https://github.com/VaHiX/codeForces/