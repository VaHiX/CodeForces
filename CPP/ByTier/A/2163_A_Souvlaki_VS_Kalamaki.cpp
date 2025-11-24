// Problem: CF 2163 A - Souvlaki VS. Kalamaki
// https://codeforces.com/contest/2163/problem/A

/*
Code Purpose:
This code determines whether Souvlaki can reorder the array such that he has a guaranteed winning strategy in a game where he and Kalamaki take turns swapping adjacent elements in a specific pattern. The key insight is that if the array can be sorted such that all elements at odd positions (1-indexed) are equal, then Souvlaki can always win.

Algorithms/Techniques:
- Sort the array first.
- Check if elements at odd indices (0-indexed) are all equal.
- Use simple iteration and sorting to check the condition.

Time Complexity:
O(n log n) per test case due to sorting, where n is the size of the array.

Space Complexity:
O(n) for storing the array elements.
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace __gnu_pbds {
struct null_type;
struct rb_tree_tag;
}  // namespace __gnu_pbds

using namespace std;
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
    ost;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int j = 0; j < n; j++)
      cin >> a[j];
    sort(a.begin(), a.end()); // Sort the array to check arrangement
    bool holds = true;
    for (int j = 0; j < n - 1; j++) {
      // If current index is odd (1-indexed), check if elements are equal
      if ((j % 2 == 1) && (a[j] != a[j + 1])) {
        holds = false;
        break;
      }
    }
    if (holds)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/