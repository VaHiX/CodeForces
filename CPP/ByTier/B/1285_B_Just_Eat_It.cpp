// Problem: CF 1285 B - Just Eat It!
// https://codeforces.com/contest/1285/problem/B

/*
Code Purpose:
This code determines whether Yasser will always be happy after buying cupcakes,
i.e., whether the total tastiness of all cupcakes is strictly greater than
the maximum possible sum of any contiguous subsegment (excluding the entire array) that Adel might choose.

Algorithms/Techniques:
- Prefix sum and suffix sum techniques are used to check if all prefixes and suffixes are positive.
- The key insight is that for Yasser to always win, the total sum must be greater than
  the maximum subarray sum of any contiguous segment that excludes the full array.
- This is equivalent to ensuring that no prefix or suffix (excluding the full array) has a sum <= 0.

Time Complexity: O(n) per test case, where n is the number of cupcakes.
Space Complexity: O(n) for storing the array of cupcake tastiness values.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll s(0);
    bool ans(true);
    // Check if all prefix sums are positive (i.e., no prefix including first element has sum <= 0)
    for (ll p = 0; p < n; p++) {
      s += a[p];
      if (s <= 0) {
        ans = false;
        break;
      }
    }
    s = 0;
    // Check if all suffix sums are positive (i.e., no suffix including last element has sum <= 0)
    for (ll p = n - 1; p > 0; p--) {
      s += a[p];
      if (s <= 0) {
        ans = false;
        break;
      }
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/