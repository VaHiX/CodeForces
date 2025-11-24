// Problem: CF 1539 C - Stable Groups
// https://codeforces.com/contest/1539/problem/C

/*
C. Stable Groups
Algorithms/Techniques: Greedy, Sorting, Binary Search

Time Complexity: O(n log n)
Space Complexity: O(n)

The problem asks to split students into minimum number of stable groups,
where a group is stable if no two adjacent elements (in sorted order) differ by more than x.
We can invite up to k additional students with arbitrary levels.

Approach:
1. Sort the initial student levels.
2. Compute gaps between consecutive students and determine how many
   students we need to insert to bridge each gap.
3. Sort these required insertions in ascending order.
4. Greedily use k insertions to eliminate the smallest gaps,
   minimizing the final number of groups.

Key insight:
- Each gap of size (diff - 1) / x additional students are needed to make
  consecutive elements in a group stable.
- To minimize groups, we should fill the smallest gaps first with our k insertions.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, k, x;
  scanf("%lld %lld %lld", &n, &k, &x);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end());
  std::vector<ll> d;
  for (ll p = 1; p < n; p++) {
    ll diff = a[p] - a[p - 1];
    if (diff > x) {
      // Calculate number of students needed to bridge this gap
      d.push_back((diff - 1) / x);
    }
  }
  sort(d.begin(), d.end());
  ll res(d.size() + 1); // Initial number of groups = number of gaps + 1
  for (ll p = 0; p < d.size(); p++) {
    if (k >= d[p]) {
      k -= d[p];
      --res; // Reduce group count by merging two groups through filling this gap
    } else {
      break; // Cannot fill this gap, so no more gaps can be filled
    }
  }
  printf("%lld\n", res);
}


// https://github.com/VaHiX/codeForces/