// Problem: CF 847 K - Travel Cards
// https://codeforces.com/contest/847/problem/K

/*
Algorithm: Dynamic Programming with Greedy Card Selection
Time Complexity: O(n log n) due to sorting of trip costs
Space Complexity: O(n) for storing trip information and map

This code solves the problem of minimizing travel expenses by optimally buying
at most k travel cards. Each card reduces the cost of a specific route to zero.
The solution uses a greedy approach: for each route, we calculate the total cost
of all trips on that route, sort the routes by total cost in descending order,
and then apply cards to the routes with the highest costs, provided that using
a card saves more than its cost (i.e., cost > f).

Key techniques:
1. Use a map to store and accumulate costs for each unique route (sorted stop names).
2. Determine whether a trip is a transshipment by comparing start of current
   trip with end of previous trip.
3. Sort routes by total trip cost in descending order.
4. Greedily apply cards to routes where savings (cost - f) is maximized.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define fi first
#define se second
string s[301], t[301];
int n;
int a, b;
int f, k;
map<string, int> mp;
vector<int> v;
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> a >> b >> k >> f;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s[i] >> t[i];
    // Calculate cost for current trip: b if transshipment, a otherwise
    // Store route in canonical form (smaller stop name first)
    mp[min(s[i], t[i]) + "#" + max(s[i], t[i])] += (s[i] == t[i - 1] ? b : a);
    ans += (s[i] == t[i - 1] ? b : a);
  }
  // Collect all route costs
  for (auto cur : mp)
    v.push_back(cur.se);
  // Sort routes by total cost in descending order to prioritize card usage
  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());
  // Apply cards greedily to routes with highest costs
  for (int i = 0; i < min(k, (int)v.size()); i++) {
    if (v[i] < f)
      break;
    // Subtract the savings from total cost (v[i] - f)
    ans -= v[i] - f;
  }
  cout << ans << endl;
}


// https://github.com/VaHiX/CodeForces/