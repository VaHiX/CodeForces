// Problem: CF 2056 D - Unique Median
// https://codeforces.com/contest/2056/problem/D

/*
 * Problem: D. Unique Median
 * Algorithm: Sliding window + prefix sum technique with map for counting subarrays
 *
 * Time Complexity: O(10 * n) per test case
 * Space Complexity: O(n)
 *
 * Approach:
 * - For each number k from 1 to 10, we process the array to count subarrays where median equals k.
 * - We transform elements into +1 (if > k), -1 (if < k), and 0 (if == k).
 * - Using prefix sums and a map to store how many times each prefix sum has occurred.
 * - The number of valid subarrays ending at index i corresponds to how many previous positions have
 *   the same prefix sum value, because that implies the subarray between those indices has median = k.
 */

#include <iostream>
#include <map>

using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
int T, n, a[maxn], s, t;
int c[maxn * 2];
ll ans;
map<int, int> mp;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    ans = 1ll * n * (n + 1) / 2; // Total number of subarrays
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int k = 1; k <= 10; k++) { // For each possible median value from 1 to 10
      mp[0] = 1; // Initialize map with prefix sum 0 occurring once
      s = t = n;
      for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] == k)
          while (j <= i) { // Expand window when current element is equal to median
            c[t]++;
            t += a[j++] > k ? 1 : -1;
          }
        s += a[i] > k ? 1 : -1; // Update prefix sum based on comparison with median
        ans -= c[s]; // Subtract invalid subarrays where median not equal to k
      }
      for (int i = 0; i <= 2 * n; i++)
        c[i] = 0; // Reset array for next iteration
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/