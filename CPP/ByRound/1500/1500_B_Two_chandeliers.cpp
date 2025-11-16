// Problem: CF 1500 B - Two chandeliers
// https://codeforces.com/contest/1500/problem/B

/*
 * Purpose: Find the day when Vasya becomes angry due to chandeliers showing different colors for the k-th time.
 * 
 * Algorithm:
 * - Use binary search on the day number to find when the k-th discrepancy occurs.
 * - For a given day x, calculate how many times colors differ using a helper function `Count`.
 * - The key idea is to compute how often a color from chandelier 1 matches the color from chandelier 2,
 *   over the full cycle of both chandeliers.
 * - Color cycles are grouped by equivalence class (same relative pattern).
 * 
 * Time Complexity: O(n + m + log(1e18))
 * Space Complexity: O(max(n, m))
 */

#include <stdio.h>
#include <utility>

#define ll long long
using namespace std;
int n, m, a[500010], b[500010], fr[1000010], id[1000010], cn, len;
ll K, l, r, mid;

// Function to count number of days where the two chandeliers differ within first x days
ll Count(ll x) {
  ll T, tot = 0;
  for (int i = 1; i <= n; ++i) {
    // Number of full cycles of chandelier 1 up to day x
    T = x / n + (x % n >= i);
    // If colors match in the same cycle, add the mismatch count
    if (fr[a[i]] == fr[b[i]])
      tot += T / len + (T % len > (id[a[i]] - id[b[i]] + len) % len);
  }
  return tot;
}

int main() {
  scanf("%d%d%lld", &n, &m, &K);
  // Ensure n <= m to simplify logic
  if (n > m) {
    for (int i = 1; i <= n; ++i)
      scanf("%d", &b[i]);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &a[i]);
    swap(n, m);
  } else {
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &b[i]);
  }
  // Identify the cycles in the second chandelier's color pattern
  for (int i = 1; i <= n; ++i)
    if (!fr[b[i]]) {
      fr[b[i]] = ++cn, id[b[i]] = 1;
      // Traverse through the cycle and mark colors accordingly
      for (int j = 2, p = (i + n - 1) % m + 1; !fr[b[p]];
           ++j, p = (p + n - 1) % m + 1)
        fr[b[p]] = cn, id[b[p]] = j;
    }
  // Calculate the length of cycle for second chandelier
  len = m / cn;
  // Binary search for the day when discrepancy count reaches K
  l = 1, r = 1e18;
  while (l < r)
    mid = l + r >> 1, mid - Count(mid) >= K ? r = mid : l = mid + 1;
  printf("%lld", l);
  return 0;
}


// https://github.com/VaHiX/CodeForces/