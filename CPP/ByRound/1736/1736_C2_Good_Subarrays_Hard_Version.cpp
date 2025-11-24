// Problem: CF 1736 C2 - Good Subarrays (Hard Version)
// https://codeforces.com/contest/1736/problem/C2

/*
Code Purpose:
This code solves the "C2. Good Subarrays (Hard Version)" problem efficiently using precomputed data structures.
The key idea is to precompute for each starting index i, the farthest ending index j such that subarray [i, j] is "good"
and the earliest index k such that subarray [i, k] is not good.

Time Complexity: O(n) for preprocessing and O(q) for each query, leading to overall O(n + q)
Space Complexity: O(n) for storing auxiliary arrays

Algorithms/Techniques:
- Two-pointer technique to find range of good subarrays starting at each index
- Preprocessing with prefix sums to quickly calculate number of good subarrays
- Query processing based on whether the updated value increases or decreases
*/

#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
const int N = 2e5 + 10;
int a[N], sum[N], sm[N], f[N], s[N];

signed main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int j = 1, k = 1;
  for (int i = 1; i <= n; i++) {
    // Move j forward while subarray [i, j] remains good
    while (j <= n && a[j] >= j - i + 1) {
      f[j++] = i;
    }
    // Adjust k to find earliest bad ending index for current i
    k = min(max(k, j + 1), n + 1);
    while (k <= n && a[k] >= k - i + 1) {
      k++;
    }
    // If s[j] is not yet set, assign it to i
    if (s[j] == 0)
      s[j] = i;
    // Calculate cumulative count of good subarrays ending at or before i
    sum[i] = sum[i - 1] + (j - i);
    // Calculate cumulative count of valid ranges for query processing
    sm[i] = sm[i - 1] + (k - i);
  }
  int p, q, x;
  cin >> q;
  while (q--) {
    cin >> p >> x;
    int ans = sum[n]; // Start with total count of good subarrays
    if (x < a[p] && f[p] <= p - x) {
      // When value decreases and can affect good subarrays
      ans -= sum[p - x] - sum[f[p] - 1];
      ans += (p - x - f[p] + 1) * (x + p - f[p]) / 2;
    } else if (x > a[p] && s[p]) {
      // When value increases and can affect good subarrays
      ans -= sum[f[p] - 1] - sum[max(p - x, s[p] - 1)];
      ans += sm[f[p] - 1] - sm[max(p - x, s[p] - 1)];
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/