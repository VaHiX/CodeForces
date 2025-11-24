// Problem: CF 2096 B - Wonderful Gloves
// https://codeforces.com/contest/2096/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> vl(n), vr(n), v(n);
    ll total(0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &vl[p]); // Read left gloves count for each color
    }
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &vr[p]); // Read right gloves count for each color
    }
    for (ll p = 0; p < n; p++) {
      v[p] = (vl[p] < vr[p] ? vl[p] : vr[p]); // Minimum of left and right gloves for each color (possible pairs)
      total += vl[p] + vr[p]; // Total number of gloves
    }
    sort(v.begin(), v.end()); // Sort the possible pairs in ascending order
    for (ll p = 0; p < n - k; p++) {
      total -= v[p]; // Subtract smallest (n-k) pair counts from total to get worst-case scenario
    }
    total -= (v[n - k] - 1); // Subtract one more to ensure at least k pairs
    printf("%lld\n", total);
  }
}
/*
Problem: B. Wonderful Gloves

Purpose:
This code computes the minimum number of gloves to be taken out from a drawer to ensure that there are at least k matching pairs of gloves with different colors, regardless of how the gloves are drawn.

Algorithm/Techniques:
- Greedy approach combined with sorting
- Worst-case analysis is used to determine minimum gloves needed

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing glove counts and possible pairs

Input Format:
- Each test case starts with two integers n (number of colors) and k (required pairs)
- Then n integers representing left gloves for each color
- Then n integers representing right gloves for each color

Output Format:
- For each test case, the minimum number of gloves to guarantee k matching pairs with different colors
*/

// https://github.com/VaHiX/codeForces/