// Problem: CF 1710 B - Rain
// https://codeforces.com/contest/1710/problem/B

/*
Code Purpose:
This program determines whether erasing a specific day's rain can prevent a flood in a field modeled as an infinite line.
The approach uses a sweep line technique with a map to track changes in rainfall intensity over positions.
For each day, we simulate the effect of removing that day's rain and check if a flood occurs.

Algorithms/Techniques:
- Sweep Line with Map: to efficiently compute the maximum rainfall at any point
- Difference Array Concept: to mark range updates in the map
- Binary Search on Answer Concept (implicit): to determine flood conditions

Time Complexity: O(n log n) per test case due to map operations
Space Complexity: O(n) for storing the map and input data

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

using namespace std;
#define ll long long
const int N = 2e5 + 3;
int T, n, m, x[N], p[N], lst, k;
ll l, a, b;
map<int, int> mp;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    mp.clear();
    cin >> n >> m;
    // Processing each day's rain and marking the range in map
    for (int i = 1; i <= n; i++) {
      cin >> x[i] >> p[i];
      mp[x[i] - p[i] + 1]++, mp[x[i] + 1] -= 2, mp[x[i] + p[i] + 1]++;
    }
    l = k = 0, a = b = -1e16;
    // Sweep line to compute maximum rainfall and identify flood points
    for (auto it : mp) {
      l += 1ll * k * (1ll * it.first - lst), k += it.second;
      if (l > m) {
        a = max(a, l - it.first + 1);
        b = max(b, l + it.first - 1);
      }
      lst = it.first;
    }
    // Check for each day if deleting it avoids flood
    for (int i = 1; i <= n; i++)
      cout << (p[i] + m - x[i] >= a && 1ll * p[i] + m + x[i] >= b);
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/