// Problem: CF 2121 H - Ice Baby
// https://codeforces.com/contest/2121/problem/H

/*
H. Ice Baby
Algorithms/Techniques: 
  - Multiset-based approach to maintain active endpoints of intervals.
  - For each new element, we insert its left bound and remove the smallest right bound that is less than or equal to the current right bound.
  - The size of the multiset minus one gives the answer for the current step.

Time Complexity: O(n log n) per test case due to multiset operations (insertion and deletion).
Space Complexity: O(n) for storing elements in the multiset.

The problem involves finding the maximum length of a non-decreasing subsequence for arrays where each element lies within given bounds [l_i, r_i].
This is solved using an online algorithm with a multiset to simulate the process of building the longest non-decreasing subsequence.
*/

#include <iostream>
#include <set>

using namespace std;
int t, n;
multiset<int> f;

void solve() {
  cin >> n;
  f.insert(0); // Initialize with 0 to handle the first interval properly
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    auto pos = f.upper_bound(r); // Find the first element in f greater than r
    f.insert(l); // Insert left bound of the new interval
    if (pos != f.end())
      f.erase(pos); // Remove the found element if it exists
    cout << f.size() - 1 << ' '; // Size minus 1 gives number of non-overlapping intervals, which equals length of longest non-decreasing subsequence
  }
  cout << '\n';
  f.clear(); // Clear multiset for next test case
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/