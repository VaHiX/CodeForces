// Problem: CF 1869 B - 2D Traveling
// https://codeforces.com/contest/1869/problem/B

/*
B. 2D Traveling
Problem Description:
Piggy wants to travel from city 'a' to city 'b' on a 2D plane with n cities.
The first k cities are major cities, and flights between two major cities cost 0.
Other flights cost Manhattan distance.
Goal: Find minimum total cost of flights from city a to b.

Algorithms/Techniques:
- Precompute Manhattan distances
- Check if direct path is optimal or going through major cities gives cheaper route
- Use greedy logic for selecting cheapest intermediate major cities

Time Complexity: O(n) per test case, where n is number of cities.
Space Complexity: O(n) for storing city coordinates.

*/
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
ll dist(const std::pair<ll, ll> &r, const std::pair<ll, ll> &s) {
  ll dx = r.first - s.first;
  if (dx < 0) {
    dx = -dx;
  }
  ll dy = r.second - s.second;
  if (dy < 0) {
    dy = -dy;
  }
  return dx + dy;
}
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k, a, b;
    scanf("%lld %lld %lld %lld", &n, &k, &a, &b);
    std::vector<std::pair<ll, ll>> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &v[p].first, &v[p].second);
    }
    --a;
    --b;
    ll res = dist(v[a], v[b]); // Direct distance without using major cities
    ll minstart(2e15 + 7), mindest(2e15 + 7), minfly(2e15 + 7);
    for (ll p = 0; p < k; p++) {
      minstart = (minstart < dist(v[a], v[p])) ? minstart : dist(v[a], v[p]); // Minimum distance from start to any major city
      mindest = (mindest < dist(v[b], v[p])) ? mindest : dist(v[b], v[p]);   // Minimum distance from destination to any major city
      minfly = minstart + mindest;
    }
    res = (res < minfly) ? res : minfly; // Take minimum of direct path and path through major cities
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/