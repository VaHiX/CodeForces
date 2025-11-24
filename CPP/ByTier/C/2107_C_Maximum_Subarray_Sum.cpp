// Problem: CF 2107 C - Maximum Subarray Sum
// https://codeforces.com/contest/2107/problem/C

/*
C. Maximum Subarray Sum
Algorithms/Techniques: Kadane's algorithm for maximum subarray sum, greedy assignment of values

Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem involves filling in missing values (marked by '0' in string s) in an array such that the maximum subarray sum equals exactly k.
We use Kadane's algorithm to find the current maximum subarray sum. If the maximum exceeds k or is less than k and no unfilled positions exist, the answer is "No".
Otherwise, we try to assign the required value to one of the unfilled positions by adjusting values greedily so that k remains achievable.
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, m, k, sum, cnt, pre, a[N], b[N], d[N];
string c;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int i, j, x, y, z, t;
  cin >> t;
  while (t--) {
    cin >> n >> k >> c;
    for (i = 0; i < n; i++)
      cin >> a[i];
    pre = -1, sum = cnt = 0;
    for (i = 0; i < n; i++) {
      if (c[i] == '0')
        pre = i, a[i] = INT_MIN; // Mark unfilled positions
      cnt = max(cnt + a[i], a[i]), sum = max(sum, cnt); // Kadane's algorithm
    }
    if (sum > k || (sum != k && pre == -1)) // If max subarray exceeds k or no unfilled pos
      cout << "No\n";
    else {
      if (pre != -1) {
        sum = cnt = 0;
        for (i = pre + 1; i < n; i++) // Compute suffix sum after unfilled position
          cnt += a[i], sum = max(sum, cnt);
        k -= sum, sum = cnt = 0;
        for (i = pre - 1; i >= 0; i--) // Compute prefix sum before unfilled position
          cnt += a[i], sum = max(sum, cnt);
        a[pre] = k - sum; // Assign value to unfilled slot
      }
      cout << "Yes\n";
      for (i = 0; i < n; i++)
        cout << a[i] << " ";
      cout << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/