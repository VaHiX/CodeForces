// Problem: CF 1158 A - The Party and Sweets
// https://codeforces.com/contest/1158/problem/A

/*
A. The Party and Sweets

Algorithm: Greedy + Conditional Logic
Time Complexity: O(n + m)
Space Complexity: O(1)

The problem asks us to minimize the total number of sweets distributed such that:
- Each boy gives at least b_i sweets to some girl
- Each girl receives at most g_j sweets from some boy

We calculate:
- sb = sum of all b_i (minimum sweets per boy)
- mxbA = maximum value in b array (largest minSweet for a boy)
- mxbB = second largest value in b array (second largest minSweet for a boy)
- sg = sum of all g_j (maximum sweets per girl)
- mng = minimum value in g array (smallest maxSweet for a girl)

Based on the relationship between mxbA and mng:
1. If mxbA > mng, impossible situation -> return -1
2. If mxbA == mng, we can distribute all boys' sweets as m * (sb - mxbA) + sg
3. If mxbA < mng, minimal total = sb * m + sg - (m - 1) * mxbA - mxbB

*/
#include <cstdio>
typedef long long ll;
int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  ll sb(0), mxbA(0), mxbB(0), sg(0), mng(1e9); // Initialize variables
  for (ll p = 0; p < n; p++) {
    ll b;
    scanf("%lld", &b);
    sb += b; // Sum of minimums per boy
    if (b >= mxbA) { // If current b is greater or equal to max
      mxbB = mxbA; // Move previous max to second max
      mxbA = b;    // Update max
    } else if (b >= mxbB) { // If current b is greater or equal to second max
      mxbB = b;  // Update second max
    }
  }
  for (ll p = 0; p < m; p++) {
    ll g;
    scanf("%lld", &g);
    sg += g;   // Sum of maximums per girl
    if (g <= mng) { // If current g is smaller or equal to minimum
      mng = g;   // Update minimum
    }
  }
  if (mxbA > mng) {
    puts("-1"); // Impossible case: maximum boy min > minimum girl max
  } else if (mxbA == mng) {
    ll ans = m * (sb - mxbA) + sg; // Case where all boys' minimum equals girls' maximum
    printf("%lld\n", ans);
  } else if (mxbA < mng) {
    ll ans = sb * m + sg - (m - 1) * mxbA - mxbB; // Optimize for case where boy max < girl min
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/