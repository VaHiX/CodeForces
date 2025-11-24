// Problem: CF 1509 C - The Sports Festival
// https://codeforces.com/contest/1509/problem/C

/*
C. The Sports Festival
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This problem involves finding the optimal order of runners to minimize the sum of discrepancies.
A discrepancy d_i for the first i runners is defined as max(a_1...a_i) - min(a_1...a_i).
The approach uses dynamic programming where f[i][j] represents the minimum cost to process
runners from index i to j in optimal order.

We sort the array first to facilitate DP transitions. The recurrence relation considers:
- Taking the leftmost element (start), then solving for the rest.
- Taking the rightmost element (finish), then solving for the rest.
We choose the option that minimizes the cost plus the difference between max and min in current segment.

The recurrence is:
f[start][finish] = min(f[start+1][finish], f[start][finish-1]) + (a[finish] - a[start])

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort to make DP transitions simpler
  std::vector<std::vector<ll>> f(n, std::vector<ll>(n, 0)); // DP table
  for (ll d = 1; d < n; d++) {
    for (ll start = 0; start + d < n; start++) {
      ll finish = start + d;
      ll down = (start + 1 < n) ? (start + 1) : n; // Next state if we take left
      ll left = (finish > 0) ? (finish - 1) : 0;   // Next state if we take right
      ll x = f[down][finish];     // Cost of taking left element
      ll y = f[start][left];      // Cost of taking right element
      ll z = (x < y) ? x : y;     // Minimum of the two options
      f[start][finish] = z + (a[finish] - a[start]); // Add difference for current segment
    }
  }
  printf("%lld\n", f[0][n - 1]);
}


// https://github.com/VaHiX/codeForces/