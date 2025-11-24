// Problem: CF 1453 B - Suffix Operations
// https://codeforces.com/contest/1453/problem/B

/*
B. Suffix Operations
Algorithms/Techniques: Greedy algorithm, prefix analysis, array manipulation

Time Complexity: O(n) for each test case, where n is the size of the array
Space Complexity: O(n) for storing the array

The problem asks to minimize the number of operations needed to make all elements equal,
where operations can only be applied to suffixes (subarrays ending at the last element).
We are allowed to change one element in the array before Gildong starts, and this
change does not count as an operation.

Approach:
1. For each possible index that we might want to change (including no change),
   we simulate what happens with that modification.
2. We compute the cost for all elements to be equal after applying operations.
3. A greedy strategy is employed to determine where the optimal change should be made,
   and then a minimal number of operations is calculated based on differences between adjacent elements.

Key idea:
We look at transitions between consecutive elements (differences). If there's a local peak or valley
that could be "smoothed" by changing one element, we test that scenario.
We compare current result with the best result obtained by modifying any single element.
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
    // Compute initial differences between first two and last two elements
    ll diffA = (a[0] < a[1]) ? (a[1] - a[0]) : (a[0] - a[1]);
    ll diffB =
        (a[n - 2] < a[n - 1]) ? (a[n - 1] - a[n - 2]) : (a[n - 2] - a[n - 1]);
    ll mx = diffA > diffB ? diffA : diffB;
    ll pos = (diffA > diffB) ? 0 : (n - 1);
    // Iterate from index 1 to n-2 to check potential local optimums
    for (ll p = 1; p + 1 < n; p++) {
      // Skip if the element forms a monotonic sequence with its neighbors
      if (a[p - 1] <= a[p] && a[p] <= a[p + 1]) {
        continue;
      }
      if (a[p - 1] >= a[p] && a[p] >= a[p + 1]) {
        continue;
      }
      // Calculate the sum of absolute differences
      ll u = a[p - 1] - a[p];
      if (u < 0) {
        u = -u;
      }
      ll v = a[p + 1] - a[p];
      if (v < 0) {
        v = -v;
      }
      ll prev = u + v;
      // Difference between previous and new difference via changing a[p]
      ll w = a[p + 1] - a[p - 1];
      if (w < 0) {
        w = -w;
      }
      ll tst = prev - w;
      if (tst > mx) {
        pos = p;
        mx = tst;
      }
    }
    // Apply the optimal modification to the array
    if (pos == 0) {
      a[0] = a[1];
    } else if (pos == n - 1) {
      a[n - 1] = a[n - 2];
    } else {
      a[pos] = a[pos - 1];
    }
    // Count total operations required to equalize the array
    ll cnt(0);
    for (long p = 1; p < n; p++) {
      ll cur = a[p] - a[p - 1];
      if (cur < 0) {
        cur = -cur;
      }
      cnt += cur;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/