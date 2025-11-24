// Problem: CF 1614 E - Divan and a Cottage
// https://codeforces.com/contest/1614/problem/E

/*
Code Purpose:
This code efficiently handles a series of temperature queries for a house that adjusts its temperature based on external conditions.
The house temperature changes daily according to a rule:
- If current temperature P < external temperature T, then P increases by 1
- If current temperature P > external temperature T, then P decreases by 1
- If current temperature P = external temperature T, then P stays unchanged

The algorithm uses a policy-based data structure (pb_ds) to maintain a multiset of temperatures
and supports efficient querying of order statistics to compute the temperature after each day's changes.

Algorithms/Techniques:
- Policy-Based Data Structures (pb_ds) for order statistics
- Binary search for finding approximate positions
- Modular arithmetic for query decoding

Time Complexity: O(n * k * log(n)) where n is number of days and k is average queries per day
Space Complexity: O(n)
*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/rb_tree_map_/node.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
#include <memory>

namespace __gnu_pbds {
struct null_type;
struct rb_tree_tag;
}  // namespace __gnu_pbds

using namespace std;
using namespace __gnu_pbds;
tree<int, null_type, less_equal<int>, rb_tree_tag,
     tree_order_statistics_node_update>
    s;
int n, t, k, o, pre, st;
inline int get(int o) { return st + o - s.order_of_key(o + 1); }
inline int query(int o) {
  int r = -1;
  for (int i = 1 << 30; i >>= 1;)
    r += i * (get(r + i) < o);
  return r + 1;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  while (n--) {
    cin >> t;
    int a = query(t), b = query(t + 1);
    st++, s.insert(a), s.insert(b);
    for (cin >> k; k--;)
      cin >> o, cout << (pre = get((o + pre) % 1000000001)) << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/