// Problem: CF 1799 F - Halve or Subtract
// https://codeforces.com/contest/1799/problem/F

/*
Algorithm: Greedy with priority sets
Approach:
1. For each element, precompute the benefit of applying operation 1 (halve) vs operation 2 (subtract b).
2. Sort elements in descending order based on their original values to prioritize larger elements for optimization.
3. Use a greedy strategy to try different combinations of operation 1 and 2 on the top elements.
4. Maintain two sets to track the difference in benefits and adjust accordingly to minimize final cost.

Time Complexity: O(n log n + k1 * k2), where n is the size of the array and k1, k2 are the limits on operations.
Space Complexity: O(n), due to storing arrays and sets of size up to n.

The key idea is to compute for each element:
- B[i]: benefit of subtracting b (max(a[i] - b, 0))
- C[i]: benefit of halving (a[i] / 2)
- BC[i]: combined benefit of applying both operations on the same element
*/

#include <stdio.h>
#include <algorithm>
#include <set>
#include <utility>

#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
#pragma GCC optimize("O2")
using namespace std;
int T, n, b, k1, k2, a[5005], B[5005], C[5005], BC[5005];
pair<int, int> p[5005];
ll ans;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &b, &k1, &k2);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      B[i] = min(b, a[i]);     // benefit from subtracting b
      C[i] = a[i] / 2;         // benefit from halving
      BC[i] = a[i] / 2 + min(b, (a[i] + 1) / 2);  // combined effect
      p[i] = mp(-a[i], i);     // sort by negative value (descending order)
    }
    sort(p + 1, p + n + 1);
    set<pair<int, int>> s1, s2;  // sets to store difference benefit and element id
    s1.insert(mp(orz, 0));
    s2.insert(mp(orz, 0));
    ll sum = 0;
    for (int i = 1; i <= min(k1, k2); ++i)
      sum += BC[p[i].se];      // apply both operations to minimize elements with highest combined benefit
    
    if (k1 > k2) {
      for (int i = min(k1, k2) + 1; i <= k1; ++i)  // allocate remainder of k1 operations
        sum += C[p[i].se], s1.insert(mp(C[p[i].se] - B[p[i].se], p[i].se));
    } else {
      for (int i = min(k1, k2) + 1; i <= k2; ++i)  // allocate remainder of k2 operations
        sum += B[p[i].se], s2.insert(mp(B[p[i].se] - C[p[i].se], p[i].se));
    }
    ans = sum;
    for (int i = min(k1, k2); i; --i) {
      if (k1 + k2 - i + 1 > n)
        break;
      sum -= BC[p[i].se];
      if (C[p[i].se] - B[p[i].se] >= s1.begin()->fi)
        sum += C[p[i].se], s1.insert(mp(C[p[i].se] - B[p[i].se], p[i].se));
      else
        sum += B[p[i].se], s2.insert(mp(B[p[i].se] - C[p[i].se], p[i].se));
      i = k1 + k2 - i + 1;      // adjust index
      if (C[p[i].se] - B[p[i].se] >= s1.begin()->fi)
        sum += C[p[i].se], s1.insert(mp(C[p[i].se] - B[p[i].se], p[i].se));
      else
        sum += B[p[i].se], s2.insert(mp(B[p[i].se] - C[p[i].se], p[i].se));
      i = k1 + k2 - i + 1;      // adjust index again
      if (s1.size() > k1 - i + 2) { // update sets to satisfy operation constraints
        sum -= s1.begin()->fi;
        s2.insert(mp(-s1.begin()->fi, s1.begin()->se));
        s1.erase(s1.begin());
      }
      if (s1.size() < k1 - i + 2) {
        sum -= s2.begin()->fi;
        s1.insert(mp(-s2.begin()->fi, s2.begin()->se));
        s2.erase(s2.begin());
      }
      ans = max(ans, sum);
    }
    ans = -ans;       // negate to correctly compute minimal cost
    for (int i = 1; i <= n; ++i)
      ans += a[i];    // compute final sum over original values
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/