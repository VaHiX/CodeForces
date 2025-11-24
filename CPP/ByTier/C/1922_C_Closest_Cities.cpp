// Problem: CF 1922 C - Closest Cities
// https://codeforces.com/contest/1922/problem/C

/*
C. Closest Cities
 Algorithms/Techniques: Prefix sums, closest city precomputation, greedy optimization

 Time complexity: O(n + m) per test case, where n is number of cities and m is number of queries
 Space complexity: O(n) per test case for prefix arrays qz and hz

 This solution precomputes the cost of traveling to the closest city from each position using prefix sums,
 allowing efficient query processing.
*/
#include <cstdio>
int T, n, a[100005], m, qz[100005], hz[100005];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), qz[1] = hz[n] = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    // Precompute prefix sums for forward direction
    for (int i = 1; i < n; ++i)
      qz[i + 1] =
          (i == 1 || a[i] - a[i - 1] > a[i + 1] - a[i] ? 1 : a[i + 1] - a[i]) +
          qz[i];
    // Precompute prefix sums for backward direction
    for (int i = n; i > 1; --i)
      hz[i - 1] =
          (i == n || a[i] - a[i - 1] < a[i + 1] - a[i] ? 1 : a[i] - a[i - 1]) +
          hz[i];
    scanf("%d", &m);
    int x, y;
    // Process queries
    while (m--) {
      scanf("%d%d", &x, &y);
      if (y > x)
        printf("%d\n", qz[y] - qz[x]);  // Forward path: use qz
      else
        printf("%d\n", hz[y] - hz[x]);  // Backward path: use hz
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/