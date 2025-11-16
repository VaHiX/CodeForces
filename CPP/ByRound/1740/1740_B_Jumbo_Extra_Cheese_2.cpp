// Problem: CF 1740 B - Jumbo Extra Cheese 2
// https://codeforces.com/contest/1740/problem/B

/*
B. Jumbo Extra Cheese 2
Algorithm: Greedy approach to minimize the perimeter of stacked rectangles.
Time Complexity: O(n log n) due to sorting (implicit in the loop logic, but not explicitly present, so effectively O(n))
Space Complexity: O(1) - only using a few variables

The problem asks to arrange rectangular cheese slices such that:
- Each slice is aligned with axes
- Bottom edge touches x-axis
- No overlaps
- Shape is connected
- Minimize total perimeter

Key insight:
To minimize the perimeter, we want to stack all rectangles such that they form one connected figure:
1. We can rotate each rectangle, so we always put the larger dimension as width.
2. We accumulate the smaller dimensions into 's' to get the height of stacked area.
3. The maximum width becomes mx, which contributes to left and right edges.

The final perimeter is computed as:
Perimeter = 2 * (max_width + total_height)
Because we have two sides of max_width and two sides of sum of heights.
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll mx(0), s(0); // mx stores maximum width; s stores sum of heights
    for (ll p = 0; p < n; p++) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      if (x < y) { // Ensure x >= y by swapping
        ll w = x;
        x = y;
        y = w;
      }
      mx = (mx > x) ? mx : x; // Update maximum width
      s += y; // Accumulate the height
    }
    printf("%lld\n", 2 * (mx + s)); // Final perimeter calculation
  }
}


// https://github.com/VaHiX/codeForces/