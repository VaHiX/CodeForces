// Problem: CF 1949 B - Charming Meals
// https://codeforces.com/contest/1949/problem/B

/*
 * Problem: B. Charming Meals
 * 
 * Purpose: Given n appetizers and n main dishes with spiciness values,
 * we want to pair each appetizer with exactly one main dish such that
 * the minimum charm (absolute difference) of all meals is maximized.
 * 
 * Approach:
 * - Sort both arrays of appetizers and main dishes.
 * - For each possible way of assigning the sorted elements, compute
 *   the minimum charm and keep track of the maximum among these minima.
 * 
 * Key Insight:
 * - To maximize the minimum charm, we try different assignments
 *   and find the best possible minimum charm.
 * 
 * Time Complexity: O(n^2), due to nested loops checking all possible pairings
 * Space Complexity: O(1), since we're using only a few variables and input arrays are already allocated
 * 
 * Algorithms/Techniques:
 * - Sorting
 * - Brute-force pairing with optimization using pre-sorted arrays
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int N = 50005, M = 998244353;
const int p = 998244353, _g = 3;
int t, n, a[N], b[N], mn, mx;

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);  // Read appetizer spiciness
    for (int i = 1; i <= n; ++i)
      scanf("%d", &b[i]);  // Read main dish spiciness
    sort(a + 1, a + 1 + n);  // Sort appetizers
    sort(b + 1, b + 1 + n);  // Sort main dishes
    mx = 0;  // Initialize maximum charm
    for (int i = 1; i <= n; ++i) {  // Try different pairings
      mn = 1 << 30;  // Initialize minimum charm for this pairing
      for (int j = 1; j <= i; ++j)
        mn = min(mn, abs(b[j + n - i] - a[j]));  // Pair first j with last (n-i+j) dishes
      for (int j = i + 1; j <= n; ++j)
        mn = min(mn, abs(b[j - i] - a[j]));  // Pair remaining with first (j-i) dishes
      mx = max(mx, mn);  // Update maximum charm
    }
    printf("%d\n", mx);
  }
}


// https://github.com/VaHiX/CodeForces/