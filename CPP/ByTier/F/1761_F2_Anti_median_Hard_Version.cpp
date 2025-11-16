// Problem: CF 1761 F2 - Anti-median (Hard Version)
// https://codeforces.com/contest/1761/problem/F2

/*
Algorithm/Techniques: 
This solution utilizes dynamic programming and combinatorics to count valid permutations that are "anti-median".
The key insight is that an array is "bad" if its median equals the middle element after sorting.
We process elements in order, tracking valid ranges and combinations for each element, and use modular arithmetic 
to handle large numbers. The main complexity comes from checking valid ranges and updating DP states based on previous values.

Time Complexity: O(N^2) in worst case due to nested loops checking ranges and combinations.
Space Complexity: O(N) for storing arrays and intermediate values.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1000005, mod = 1000000007;
int t, n, m, ans, a[N], fac[N], inv[N], pos[N];
int l1[N], r1[N], l2[N], r2[N], f1[N], f2[N], sum[N];

// Adds two numbers and returns result modulo mod
int add(int x, int y) {
  x += y;
  return (x < mod ? x : x - mod);
}

// Computes combination C(n, m) using precomputed factorials
int C(int n, int m) {
  if ((m < 0) || (m > n))
    return 0;
  return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}

// Computes prefix sum of combinations from l to r
int get_sum(int l, int r) {
  l = max(l, 0), r = min(r, n - 2);
  if (l > r)
    return 0;
  return add(sum[r], (l ? mod - sum[l - 1] : 0));
}

// Checks if a range is valid for a given position
bool check(int l, int r) {
  if (l <= r)
    return l + r <= n + 1;
  return l + r > n + 1;
}

// Calculates combination values for range computation
int calc(int l, int r, int x, int y) {
  return add(add(C(l + r, l), mod - C(l + r, x - 1 + r)),
             mod - C(l + r, y + 1 + r));
}

// Calculates transition between ranges, used in DP
int move(int l1, int r1, int l2, int r2) {
  int l = (l1 - l2 + n) % n, r = (r2 - r1 + n) % n;
  if ((l + r >= n) || (!check(l2, r2)))
    return 0;
  if (l1 <= r1)
    return calc(l, r, l1 + r1 - n - 1, l1 + r1 - 2);
  return calc(l, r, -n, l1 + r1 - n - 2);
}

// Main logic for computing number of valid permutations
int work() {
  m = 0;
  for (int i = 1; i <= n; i++)
    pos[i] = 0;
  for (int i = 1; i <= n; i++)
    if (a[i] > 0)
      pos[a[i]] = ((i & 1) ? (i + 1 >> 1) : n - (i >> 1) + 1);
  for (int i = 1; i <= n; i++)
    if (pos[i]) {
      if (i == 1)
        m++, l1[m] = r1[m] = l2[m] = r2[m] = pos[i], f1[m] = 1, f2[m] = 0;
      else {
        l1[++m] = pos[i] % n + 1, r1[m] = (pos[i] + i - 2) % n + 1;
        l2[m] = (pos[i] + n - i) % n + 1, r2[m] = (pos[i] + n - 2) % n + 1;
        f1[m] = f2[m] = 0;
        if (m == 1) {
          for (int j = 1; j <= (n + 1 >> 1); j++) {
            f1[m] = add(f1[m], move(j, j, l1[m], r1[m]));
            f2[m] = add(f2[m], move(j, j, l2[m], r2[m]));
          }
        } else {
          f1[m] =
              (ll)f1[m - 1] * move(l1[m - 1], r1[m - 1], l1[m], r1[m]) % mod;
          f1[m] = (f1[m] +
                   (ll)f2[m - 1] * move(l2[m - 1], r2[m - 1], l1[m], r1[m])) %
                  mod;
          f2[m] =
              (ll)f1[m - 1] * move(l1[m - 1], r1[m - 1], l2[m], r2[m]) % mod;
          f2[m] = (f2[m] +
                   (ll)f2[m - 1] * move(l2[m - 1], r2[m - 1], l2[m], r2[m])) %
                  mod;
        }
        l1[m] = r2[m] = pos[i];
      }
      if (i < n) {
        if (!check(l1[m], r1[m]))
          f1[m] = 0;
        if (!check(l2[m], r2[m]))
          f2[m] = 0;
      }
    }
  if (pos[n])
    return f1[m];
  if (m) {
    int ans = 0;
    for (int i = (n + 1 >> 1) + 1; i <= n; i++) {
      ans = (ans +
             (ll)f1[m] * move(l1[m], r1[m], i % n + 1, (i + n - 2) % n + 1)) %
            mod;
      ans = (ans +
             (ll)f2[m] * move(l2[m], r2[m], i % n + 1, (i + n - 2) % n + 1)) %
            mod;
    }
    return ans;
  }
  int ans = 0;
  sum[0] = 1;
  for (int i = 1; i <= n - 2; i++)
    sum[i] = add(sum[i - 1], C(n - 2, i));
  for (int i = 1; i <= (n + 1 >> 1); i++) {
    ans = add(ans, get_sum((n + 1 >> 1) - i, n - i - 1));
    ans = add(ans, mod - get_sum(i - (n >> 1) - 2, i - 3));
    ans = add(ans, mod - get_sum(i + (n + 1 >> 1) - 1, i + n - 2));
  }
  return ans;
}

int main() {
  fac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i < N; i++)
    fac[i] = (ll)fac[i - 1] * i % mod;
  for (int i = 2; i < N; i++)
    inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
  for (int i = 1; i < N; i++)
    inv[i] = (ll)inv[i - 1] * inv[i] % mod;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    ans = work();
    for (int i = 1; i <= n; i++)
      if (a[i] > 0)
        a[i] = n - a[i] + 1;
    printf("%d\n", add(ans, work()));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/