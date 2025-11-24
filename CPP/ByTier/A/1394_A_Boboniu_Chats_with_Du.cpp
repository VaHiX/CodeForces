// Problem: CF 1394 A - Boboniu Chats with Du
// https://codeforces.com/contest/1394/problem/A

/*
Problem: Boboniu Chats with Du
Purpose: Given n days of fun factors, a muzzle duration d, and mood threshold m,
         find the maximum total fun factor by optimally permuting the array such that
         when a[i] > m, the next d days are muted.
Algorithm:
  - Sort the array.
  - For each possible number of "big" elements (a[i] > m), simulate the optimal selection
    using prefix sums to compute total fun factor efficiently.
Time Complexity: O(n log n) due to sorting and linear traversal.
Space Complexity: O(n) for storing array and prefix sum array.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
long long a[100009];
long long dp[100009]; // Prefix sum array
int main() {
  long long n, d, m;
  scanf("%lld %lld %lld", &n, &d, &m);
  int cnt = 0; // Count of elements <= m
  for (long long i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    if (a[i] <= m) {
      cnt++;
    }
  }
  sort(a + 1, a + n + 1); // Sort the array
  for (long long i = 1; i <= n; i++) {
    dp[i] = dp[i - 1] + a[i]; // Build prefix sum
  }
  if (cnt == n) { // All elements are <= m
    printf("%lld", dp[n]);
  } else {
    long long ans = 0;
    for (long long i = n; i > cnt; i--) {
      if ((n - i) * d <= i - 1) {
        // Calculate number of elements to skip from the start
        long long num =
            max((long long)0, (n - i) * d - (n - cnt - (n - i + 1)));
        ans = max(ans, dp[cnt] - dp[num] + dp[n] - dp[i - 1]);
      } else {
        break; // No valid configuration
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/