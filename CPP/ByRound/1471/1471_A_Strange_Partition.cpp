// Problem: CF 1471 A - Strange Partition
// https://codeforces.com/contest/1471/problem/A

/*
 * Problem: Strange Partition
 * Algorithms/Techniques: Greedy approach, Ceiling division
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * The problem involves finding the minimum and maximum "beauty" of an array
 * after performing operations that merge adjacent elements by summing them.
 * Beauty is defined as the sum of ceiling divisions of each element by x.
 *
 * For maximum beauty:
 *   - We want to minimize the number of merged elements, so we keep all elements
 *     as separate as possible. This gives us the sum of ceiling(a[i]/x) for all i.
 *
 * For minimum beauty:
 *   - We can merge elements optimally to reduce the total number of terms,
 *     which reduces the sum of ceiling values. The best case is when we
 *     have only one element (total sum), giving ceiling(total_sum/x).
 *
 * This approach works because:
 *   - Merging increases the value of an element, potentially increasing
 *     its ceiling division contribution.
 *   - To maximize beauty, don't merge at all.
 *   - To minimize beauty, merge everything into one element.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    ll s(0), mx(0); // s: total sum, mx: max beauty (no merging)
    while (n--) {
      ll a;
      scanf("%lld", &a);
      s += a;                    // accumulate sum of all elements
      mx += (a + x - 1) / x;     // compute ceiling of a/x and add to max beauty
    }
    ll mn = (s + x - 1) / x;     // minimum beauty: ceil(total_sum / x)
    printf("%lld %lld\n", mn, mx);
  }
}


// https://github.com/VaHiX/codeForces/