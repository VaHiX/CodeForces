// Problem: CF 2139 B - Cake Collection
// https://codeforces.com/contest/2139/problem/B

/*
B. Cake Collection

Algorithms/Techniques: Greedy algorithm
Time Complexity: O(n log n + t * n), where n is the number of ovens and t is the number of test cases.
Space Complexity: O(n), for storing the array of oven capacities.

The problem involves maximizing the number of cakes collected in m seconds by choosing which oven to collect from each second.
Since the cakes accumulate over time, we want to prioritize collecting from the oven with the highest rate of cake production at each step,
as that will yield maximum cakes for the remaining time.
We sort ovens in descending order based on their rates and greedily select the best oven each time,
adding contribution of that oven for remaining seconds (m - i) to total sum.

Key logic:
1. Sort the oven rates in descending order.
2. For each second i (0 to m-1), collect from the best available oven.
3. Contribution = rate * (number of remaining seconds) = v[i] * (m - i).
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
#define basbosa ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

signed main() {
  basbosa int t;
  cin >> t;
  while (t--) {
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> v(n);
    for (auto &i : v)
      cin >> i;
    sort(v.rbegin(), v.rend()); // Sort in descending order to get highest rates first
    for (int i = 0; i < n && m; i++, m--) {
      ans += (v[i] * m); // Add contribution of current oven for remaining time
    }
    cout << ans;
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/