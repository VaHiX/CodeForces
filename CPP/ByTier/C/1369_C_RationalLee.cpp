// Problem: CF 1369 C - RationalLee
// https://codeforces.com/contest/1369/problem/C

/*
C. RationalLee
Algorithms/Techniques: Greedy algorithm, sorting, two pointers approach

Time Complexity: O(n log n + k log k) per test case due to sorting operations
Space Complexity: O(n + k) for storing arrays a and w

Problem:
Lee wants to distribute n integers among k friends such that friend i gets exactly w[i] integers.
The happiness of a friend is the sum of the maximum and minimum integers they receive.
Goal: Maximize total happiness.
Approach:
- Sort integers a in ascending order.
- Sort weights w in descending order (to assign largest groups first).
- For each friend, give them the w[i] integers starting from current index.
- First and last elements of group contribute to happiness (max + min).
- Use greedy to maximize sum of (max + min) by assigning largest values wisely.
*/

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
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> w(k);
    for (ll p = 0; p < k; p++) {
      scanf("%lld", &w[p]);
    }
    sort(a.begin(), a.end()); // Sort integers in ascending order
    sort(w.rbegin(), w.rend()); // Sort weights in descending order to assign larger groups first
    
    ll s(0), idx(0);
    for (ll p = 0; p < k; p++) {
      s += a[n - k + p]; // Add the largest element in current group (max)
      s += (w[p] > 1) ? a[idx] : a[n - k + p]; // If group size > 1, add smallest; else reuse max
      idx += w[p] - 1; // Move index to start of next group
    }
    printf("%lld\n", s);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/