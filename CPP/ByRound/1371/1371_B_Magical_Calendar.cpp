// Problem: CF 1371 B - Magical Calendar
// https://codeforces.com/contest/1371/problem/B

#include <cstdio>
typedef long long ll;

/*
B. Magical Calendar

Purpose:
This program calculates the number of distinct shapes that can be formed by painting n consecutive days on a magical calendar,
where the number of days in a week (k) can be any value from 1 to r.
The key insight is based on how many distinct rectangles can be formed with n cells,
subjected to a constraint of at most r columns per row.

Algorithms/Techniques:
- Mathematical analysis of tiling patterns
- Combinatorial counting with constraints

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input:
Multiple test cases, each with two integers n and r (1 <= n, r <= 10^9)

Output:
Number of distinct shapes for each test case
*/

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, r;
    scanf("%lld %lld", &n, &r);
    // ans is initialized to 1 if r >= n, else 0.
    // This accounts for the case when the number of days in a week is greater than or equal to n
    ll ans(r >= n);
    // r is capped at n - 1 because after that, the patterns will repeat cyclically
    r = (r >= n) ? (n - 1) : r;
    // Add arithmetic series sum for possible shapes with less than n days in a week
    ans += r * (r + 1) / 2;
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/