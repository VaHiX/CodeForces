// Problem: CF 1691 E - Number of Groups
// https://codeforces.com/contest/1691/problem/E

/*
Algorithm: Union-Find / Segment Overlap Detection
Time Complexity: O(n log n) due to sorting and multiset operations
Space Complexity: O(n) for storing segments and multisets

This solution uses a sweep line approach combined with multisets to track
overlapping segments. For each segment, we check if it overlaps with any
segment of the opposite color. If so, we merge the groups. We use two multisets
to keep track of the right endpoints of red and blue segments respectively.
*/

#include <assert.h>
#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
#define ll long long
#define ar array

void solve() {
  int n;
  cin >> n;
  vector<ar<int, 3>> v;
  for (int i = 0; i < n; ++i) {
    int c, l, r;
    cin >> c >> l >> r;
    v.push_back({l, r, c}); // Store segments as [left, right, color]
  }
  sort(v.begin(), v.end()); // Sort segments by left endpoint
  int ans = n; // Initially assume each segment is its own group
  multiset<int> s[2]; // s[0] for red segments, s[1] for blue segments

  for (auto [l, r, c] : v) {
    // Remove segments from the multiset whose right endpoint is less than current left
    for (int i : {0, 1})
      while (s[i].size() && *s[i].begin() < l)
        s[i].erase(s[i].begin());

    s[c].insert(r); // Insert current segment's right endpoint into corresponding multiset

    // If there are segments of the opposite color that could connect
    if (s[c ^ 1].size()) {
      --ans; // Decrease group count because we found a connection

      // Remove all but the smallest (closest) segment from opposite color
      while (s[c ^ 1].size() > 1) {
        s[c ^ 1].erase(s[c ^ 1].begin());
        --ans;
      }

      assert(s[c].size() <= 2); // At most 2 segments of same color can be in the multiset
      if (s[c].size() == 2)
        s[c].erase(s[c].begin()); // Remove the smallest one to keep only relevant segments
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/