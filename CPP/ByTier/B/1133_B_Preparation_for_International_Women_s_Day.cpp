// Problem: CF 1133 B - Preparation for International Women's Day
// https://codeforces.com/contest/1133/problem/B

/*
B. Preparation for International Women's Day
Algorithm: Greedy + Modular Arithmetic
Time Complexity: O(n + k)
Space Complexity: O(k)

The problem asks to pair up boxes such that the sum of candies in each pair is divisible by k.
We use modular arithmetic to classify boxes by their remainder when divided by k.
For two numbers a and b, (a + b) % k == 0 if and only if (a % k) + (b % k) == k or (a % k) == 0 and (b % k) == 0.

We count how many boxes belong to each remainder class [0, k-1].
Then we pair:
- Boxes with remainder 0 can only be paired among themselves (each pair contributes 2 boxes).
- For remainders r and k-r, we pair them optimally (take min of counts).
- Special case for k even: remainder k/2 pairs with itself.

The algorithm computes the maximum number of gifts possible by greedily pairing valid combinations.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<ll> a(k, 0); // Count of boxes for each remainder mod k
  for (ll p = 0; p < n; p++) {
    ll d;
    scanf("%lld", &d);
    ++a[d % k]; // Increment count for this remainder class
  }
  ll total(a[0] - a[0] % 2); // Pair all boxes with remainder 0 among themselves
  for (ll p = 1; 2 * p <= k; p++) {
    total += 2 * ((a[p] < a[k - p]) ? a[p] : a[k - p]); // Pair min of remainder p and k-p
    if (2 * p == k) {
      total -= a[p] + a[p] % 2; // Adjust for special case when p = k/2 (odd k case)
    }
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/