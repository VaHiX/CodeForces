// Problem: CF 634 D - Package Delivery
// https://codeforces.com/contest/634/problem/D

/*
Algorithm: Greedy with Priority Queue
Approach:
- We use a greedy strategy where at each step, we try to fill up the tank to the
maximum possible distance.
- We maintain a priority queue of stations we can reach from our current
position.
- At each step, we select the cheapest station within our reach to refuel.
- The problem is solved by simulating the journey with refueling decisions based
on price.

Time Complexity: O(m * log m) - due to sorting and priority queue operations
Space Complexity: O(m) - for storing stations and priority queue
*/

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <functional>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
  ll n, d;
  int m;
  cin >> d >> n >> m;
  using P = pair<ll, ll>;
  V<P> v(m);
  for (int i = 0; i < m; i++) {
    cin >> v[i].first >> v[i].second;
  }
  sort(v.begin(), v.end());
  v.push_back(P(d, -1));
  ll nw = n, ans = 0;
  int le = 0;
  using Q = pair<ll, int>;
  priority_queue<Q, V<Q>, greater<Q>> que;
  while (nw < d) {
    // Add all reachable stations to the priority queue
    while (le < m && v[le].first <= nw) {
      que.push({v[le].second, le});
      le++;
    }
    // Remove stations that are too far to reach from current position
    while (que.size()) {
      Q q = que.top();
      if (nw - n < v[q.second].first)
        break;
      que.pop();
    }
    if (que.empty()) {
      cout << -1 << endl;
      return 0;
    }
    // Calculate how much fuel to buy to reach next station or destination
    ll fuel = min(v[le].first - nw, n - (nw - v[que.top().second].first));
    nw += fuel;
    ans += fuel * v[que.top().second].second;
  }
  cout << ans << endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/