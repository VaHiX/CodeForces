// Problem: CF 1809 D - Binary String Sorting
// https://codeforces.com/contest/1809/problem/D

/*
 * Problem: Binary String Sorting
 * Algorithm: Greedy with prefix/suffix counting
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(n) for storing the string
 *
 * The approach involves:
 * 1. Counting total number of '1's in the string.
 * 2. For each possible split point (0 to n), calculate cost:
 *    - Number of '1's before the split point (now).
 *    - Number of '0's after the split point (n - i - mid).
 *    - For each such split, we consider swapping adjacent elements to minimize cost.
 *    - We subtract 1000000000002 if a swap is needed at position i (to account for cost of swap).
 * 3. Return the minimum cost found.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long ll;
char num[300010];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%s", num + 1);
    int n = strlen(num + 1);
    ll ans = 1e18, mid = 0, now = 0;
    for (int i = 1; i <= n; i++)
      mid += (num[i] == '1');  // Count total number of '1's
    for (int i = 0; i <= n; i++) {
      if (num[i] == '1')       // Adjust count of '1's before split
        mid--, now++;
      ll res = now + (n - i - mid);  // Cost = left '1's + right '0's
      res = res * 1000000000000 + res;  // Base cost calculation
      if (num[i] == '1' && num[i + 1] == '0')  // If a swap is needed
        res -= 1000000000002;  // Adjust for swap cost
      ans = min(ans, res);  // Track minimum cost
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/