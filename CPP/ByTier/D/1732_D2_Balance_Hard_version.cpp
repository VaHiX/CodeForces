// Problem: CF 1732 D2 - Balance (Hard version)
// https://codeforces.com/contest/1732/problem/D2

/*
Code Purpose:
This code solves the "Balance (Hard version)" problem where we maintain a dynamic set of integers
and efficiently compute k-mex for each query. The k-mex is the smallest non-negative integer divisible by k that is not in the set.

Algorithms/Techniques:
- Use of maps and sets to track presence and deletion states
- Optimization to avoid recomputing the same k-mex values multiple times
- Efficiently track and update potential k-mex candidates using a greedy approach

Time Complexity: O(q * sqrt(max_value)) where q is the number of queries
Space Complexity: O(q) for storing the data structures
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
typedef long long ll;
ll i, j, k, n, m, t;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // f[k] keeps track of the current candidate for k-mex
  map<ll, ll> f, mp;
  // vis[k] stores which values have been visited for k-mex computation
  map<ll, set<ll>> vis, del;
  // Initially, 0 is in the set
  mp[0] = 1;
  cin >> t;
  while (t--) {
    string s;
    cin >> s >> k;
    if (s == "+") {
      // When adding an element, remove its influence from k-mex tracking
      for (auto i : vis[k])
        del[i].erase(k);
      // Mark k as present in the set
      mp[k] = 1;
    } else if (s == "?") {
      // Compute and output k-mex
      // Keep incrementing f[k] while the value exists in the set
      while (mp[f[k]]) {
        vis[f[k]].insert(k); // Mark this value as visited for this k
        f[k] += k; // Move to next multiple
      }
      ll res = f[k];
      // If there are deletions for this k, check if a smaller valid value exists
      if (!del[k].empty())
        res = min(res, (ll)*del[k].begin());
      cout << res << '\n';
    } else {
      // When removing an element, mark it for deletion in k-mex tracking
      for (auto i : vis[k])
        del[i].insert(k);
      // Mark k as not present in the set
      mp[k] = 0;
    }
  }
}


// https://github.com/VaHiX/CodeForces/