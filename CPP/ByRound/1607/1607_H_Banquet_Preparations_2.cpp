// Problem: CF 1607 H - Banquet Preparations 2
// https://codeforces.com/contest/1607/problem/H

/*
Purpose: This code solves the problem of minimizing the variety of dishes after a taster consumes a specific amount of food from each dish.
         The variety is defined as the number of distinct (fish, meat) pairs of dishes remaining after the taster eats some amount.
         The strategy is to assign how much fish and meat the taster eats to minimize duplicates.

Algorithm:
- For each dish, compute:
  - s[i] = a[i] + b[i] - m[i]: the remaining mass (total - eaten)
  - l[i] = max(0, a[i] - m[i]): minimum fish that can be left after eating
  - r[i] = a[i] + min(0, b[i] - m[i]): maximum possible fish that could be eaten
- Group dishes by s[i] to identify which dishes can potentially overlap.
- Within each group, sort based on r[i] to apply a greedy strategy.
- For each group, greedily assign a "range" such that overlapping ranges are merged, minimizing total sets.
- Output the minimum number of unique (fish, meat) pairs and the assignment for each dish.

Time Complexity: O(n log n) due to sorting operations across all dishes.
Space Complexity: O(n) for storing data and auxiliary arrays.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n), m(n), s(n), l(n), r(n);
    map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) {
      cin >> a[i] >> b[i] >> m[i];
      s[i] = a[i] + b[i] - m[i]; // remaining mass after eating
      l[i] = max(0, a[i] - m[i]); // min fish that can remain
      r[i] = a[i] + min(0, b[i] - m[i]); // max fish that could be eaten
      mp[s[i]].push_back(i); // group dishes by remaining mass
    }
    int ans = 0;
    vector<int> rs(n);
    for (auto &&[si, idx] : mp) {
      sort(begin(idx), end(idx), [&](int i, int j) { return r[i] < r[j]; }); // sort by max fish eaten
      int nr = -1;
      for (auto &i : idx) {
        if (nr < l[i]) { // if this range doesn't overlap with previous
          ++ans;
          nr = r[i];
        }
        rs[i] = nr; // assign the range end position to the dish
      }
    }
    cout << ans << "\n";
    for (int i = 0; i < n; ++i) {
      cout << a[i] - rs[i] << " " << m[i] - a[i] + rs[i] << "\n"; // output fish and meat eaten
    }
  }
}


// https://github.com/VaHiX/CodeForces/