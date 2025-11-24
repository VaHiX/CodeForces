// Problem: CF 2006 C - Eri and Expanded Sets
// https://codeforces.com/contest/2006/problem/C

/*
  Problem: C. Eri and Expanded Sets
  Algorithms/Techniques: Sliding window with GCD, bit manipulation for powers of two

  Time Complexity: O(N * log(max(a[i])) + N) per test case
  Space Complexity: O(N) for arrays and structures

  The task is to count the number of subarrays such that after expanding the set using the given operation,
  the final set can become consecutive. The key insight is that the expansion is possible if and only if
  the GCD of differences between adjacent elements in the sorted subarray is 1 or a power of 2.
  We use a sliding window technique to maintain counts of distinct GCDs and check conditions.
*/

#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef int64_t i64;
const int N = 4e5 + 5, B = 45;
int t, n, a[N], b[N], cn;
i64 ans;
struct node {
  int v, c;
} c[B];
void solve() {
  cin >> n;
  ans = n;  // Every single element subarray is brilliant
  cn = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], b[i] = abs(a[i] - a[i - 1]);  // Compute differences between adjacent elements
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= cn; j++)
      c[j].v = __gcd(c[j].v, b[i]);  // Update GCDs with current difference
    c[++cn] = {b[i], 1};  // Add the new difference to our structure
    int m = cn;
    cn = 1;
    for (int j = 2; j <= m; j++) {
      if (c[j].v == c[cn].v)
        c[cn].c += c[j].c;  // Merge same GCDs
      else
        c[++cn] = c[j];
    }
    for (int j = 1; j <= cn; j++)
      if (c[j].v == 0 || (c[j].v & (c[j].v - 1)) == 0)  // Check for zero or power of two
        ans += c[j].c;  // Increment answer if condition satisfied
  }
  cout << ans << '\n';
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/