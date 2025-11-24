// Problem: CF 2053 I1 - Affectionate Arrays (Easy Version)
// https://codeforces.com/contest/2053/problem/I1

/*
I1. Affectionate Arrays (Easy Version)
time limit per test3 seconds
memory limit per test512 megabytes

Algorithms/Techniques: Kadane's algorithm variant, sliding window with prefix sums

Time Complexity: O(n) amortized over all test cases
Space Complexity: O(1)

This problem asks to find the minimum length of an array `b` that:
1. Contains `a` as a subsequence
2. Has the same sum as `a`
3. Has minimal possible "boredom" (maximum subarray sum)
4. Among all such arrays with minimal boredom, has minimal length

The approach uses two variables `L` and `R` which track the minimum and maximum possible values of a prefix sum during traversal.
When we update these prefixes, we count when `L > R`, meaning a valid split occurred between elements.
This helps in determining how many extra elements are required to maintain the constraint on subarray sums.
Finally, we check if `R` equals `sum`, if not, we increment answer once more (meaning last segment needs adjustment).
*/

#include <algorithm>
#include <iostream>
using namespace std;
#define endl '\n'
typedef long long LL;
const int MAXN = 3e6 + 5;
int T, n, a[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    LL sum = 0, L = 0, R = 0;
    int ans = n; // Initially assume we just need the same length as input
    for (int i = 1; i <= n; ++i)
      cin >> a[i], sum += a[i]; // Read and compute total sum

    for (int i = 1; i <= n; ++i) {
      L = max(0ll, L + a[i]), R = min(R + a[i], sum); // Update prefix bounds
      if (L > R)
        ++ans, L = max(0, a[i]), R = sum + min(0, a[i]); // Found a gap in valid range; increment count and reset
    }

    if (R != sum) // If final accumulated sum is not equal to target, adjust again
      ++ans;

    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/