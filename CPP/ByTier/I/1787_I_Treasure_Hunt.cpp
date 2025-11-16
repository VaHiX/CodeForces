// Problem: CF 1787 I - Treasure Hunt
// https://codeforces.com/contest/1787/problem/I

/*
Code Purpose:
This code solves the "Treasure Hunt" problem where we need to calculate the sum of beauty values for all non-empty subsegments of a given sequence. 

The beauty value of a sequence b is defined as the maximum value of:
∑_{i=1}^{q} b_i + ∑_{i=s}^{t} b_i, where s > q or t ≤ q.

This solution uses a divide and conquer approach with preprocessing to efficiently compute the sum of beauty values over all subsegments.

Algorithms/Techniques:
- Divide and Conquer: Recursively splits the array into halves.
- Preprocessing: For each segment, calculates prefix and suffix maximums to optimize range queries.
- Stack-based approach: Used to compute initial answer using monotonic stack.

Time Complexity: O(n log n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <algorithm>

using namespace std;
const int o = 1e6 + 10, MOD = 998244353;
int T, n, a[o], ans, st[o], tp, sd[o], se[o];
long long s[o], sm, b[o], c[o], d[o], e[o];

// Recursive function to compute beauty values using divide and conquer
void slv(int l, int r) {
  if (l == r) {
    // Base case: only one element; beauty is max of that element and 0
    ans = (ans + max(a[l], 0)) % MOD;
    return;
  }
  int md = l + r >> 1, p1 = md + 1, p2 = md + 1;
  long long mn, tot;
  // Process left side prefix
  mn = tot = b[md + 1] = c[md + 1] = 0;
  for (int i = md; i >= l; --i)
    mn = min(mn, tot += a[i]), b[i] = max(b[i + 1], tot - mn),  // Calculate best prefix ending at i
    c[i] = max(c[i + 1], tot);  // Maximum prefix sum up to i
  // Process right side suffix
  mn = tot = d[md] = e[md] = 0;
  for (int i = md + 1; i <= r; ++i)
    mn = min(mn, tot += a[i]), d[i] = max(d[i - 1], tot - mn),  // Best suffix starting at i
    e[i] = max(e[i - 1], tot);  // Maximum suffix sum starting at i
  // Precompute prefix sums of d and e
  sd[md] = se[md] = 0;
  for (int i = md + 1; i <= r; ++i)
    sd[i] = (sd[i - 1] + d[i]) % MOD, se[i] = (se[i - 1] + e[i]) % MOD;
  // For each left element, determine optimal right position for maximizing expression
  for (int i = md; i >= l; --i) {
    for (; p1 <= r && max(d[p1], c[i] + e[p1]) < b[i]; ++p1)
      ;  // Move p1 to a point where we can get a larger value
    for (p2 = max(p2, p1); p2 <= r && d[p2] - e[p2] < c[i]; ++p2)
      ;  // Adjust p2 based on balance of d and e
    ans = (ans + b[i] * (p1 - md - 1) + c[i] * (p2 - p1) + se[p2 - 1] + MOD -
           se[p1 - 1] + sd[r] - sd[p2 - 1]) %
          MOD;
  }
  // Recursive calls to left and right halves
  slv(l, md);
  slv(md + 1, r);
}

int main() {
  for (scanf("%d", &T); T--; printf("%d\n", ans), ans = sm = 0) {
    scanf("%d", &n);
    st[tp = 0] = n + 1;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];  // Compute prefix sums
    // Monotonic stack based computation for initial answer
    for (int i = n; i + 1; st[++tp] = i--) {
      for (; tp && s[st[tp]] < s[i]; --tp)
        sm -= s[st[tp]] * (st[tp - 1] - st[tp]);  // Adjust sum by removing elements from stack
      sm += (st[tp] - i) * s[i];
      ans = (ans + sm - s[i] * (n - i + 1ll)) % MOD;
    }
    slv(1, n);  // Begin recursive divide and conquer
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/