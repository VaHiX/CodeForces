// Problem: CF 1801 B - Buying gifts
// https://codeforces.com/contest/1801/problem/B

/*
 * Problem: Buying gifts
 * Algorithm: Sorting + Binary search + Sliding window technique
 * Time Complexity: O(n * log(n)) per test case
 * Space Complexity: O(n)
 *
 * The idea is to try all possible gifts for the first friend,
 * and for each such choice, find the best possible gift for the second friend
 * such that the difference of max prices is minimized.
 * 
 * We sort the departments by price of first gift (a_i) and for each department
 * we precompute the maximum price of second gift from all departments after it.
 * Then for each department, we use binary search to find candidates
 * and check few nearby elements to minimize the difference.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <utility>

#define pii pair<int, int>
using namespace std;
typedef long long ll;
const int N = 500005;
int T, n, m, b[N], mx[N];
pii a[N];

void solve() {
  scanf("%d", &n);
  mx[n + 1] = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &a[i].first, &b[i]), a[i].second = i; // Store department index with price
  sort(a + 1, a + n + 1); // Sort by first gift price
  int ans = 0x3f3f3f3f; // Initialize with large value
  for (int i = n; i; --i)
    mx[i] = max(mx[i + 1], b[a[i].second]); // Precompute max b_i from i to n
  for (int i = 1; i <= n; ++i) {
    int p = lower_bound(a + 1, a + n + 1, pii{b[i], 0}) - a; // Find where b[i] would fit in sorted array
    for (int j = max(1, p - 3); j <= min(n, p + 3); ++j) // Check nearby elements
      if (a[j].second != i && b[i] >= mx[j + 1]) // Avoid using same department and ensure valid max
        ans = min(ans, abs(a[j].first - b[i])); // Update minimum difference
  }
  printf("%d\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/