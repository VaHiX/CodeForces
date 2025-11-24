// Problem: CF 1725 K - Kingdom of Criticism
// https://codeforces.com/contest/1725/problem/K

/*
K. Kingdom of Criticism
Algorithms/Techniques: Union-Find (Disjoint Set Union), Map-based Coordinate Compression

Time Complexity: O((N + Q) * alpha(N)) where alpha is the inverse Ackermann function (nearly constant)
Space Complexity: O(N)

This code handles queries on building heights in a kingdom, supporting:
1. Updating a building's height
2. Querying the current height of a building
3. Criticizing buildings with heights in a range [l,r] where r-l is odd.
   The algorithm then minimizes time to adjust all affected buildings so 
   that no building has height in the interval [l,r]. This is done by placing
   all values either below l or above r, with preference to values on the side
   closer to the midpoint of l and r.

The data structure uses a map to manage which buildings are associated with specific heights,
and union-find to group buildings together that must have same height.
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;
const int MAXN = 400400;
int n, a[2 * MAXN], actual[2 * MAXN], q, cnt;
int uf[2 * MAXN];
int find(int x) { return uf[x] ? uf[x] = find(uf[x]) : x; }
void join(int x, int y) {
  if ((x = find(x)) == (y = find(y)))
    return;
  uf[y] = x;
}
void mapAll(vector<int> &v, int x, map<int, int> &m) {
  if (v.empty())
    return;
  auto it = m.lower_bound(x);
  if (it == m.end() || it->first != x) {
    int rep = v.back();
    it = m.insert(it, make_pair(x, rep));
    a[rep] = x;
  }
  for (const int &x : v)
    join(it->second, x);
}
void upd(int i, map<int, int> &m) {
  auto it = m.lower_bound(a[i]);
  if (it == m.end() || it->first != a[i])
    it = m.insert(it, make_pair(a[i], i));
  join(it->second, i);
}
int main() {
  scanf("%d", &n);
  map<int, int> m;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]), actual[i] = i;
    upd(i, m); // Initialize the mapping and union structure
  }
  cnt = n;
  for (scanf("%d", &q); q--;) {
    int op, l, r, k, w;
    scanf("%d", &op);
    if (op == 1) { // Update building k's height to w
      scanf("%d %d", &k, &w);
      actual[k] = ++cnt; // Increment counter and assign to new index
      a[actual[k]] = w; // Set the actual value
      upd(actual[k], m); // Update mapping structures for new entry
    } else if (op == 2) { // Query height of building k
      scanf("%d", &k);
      printf("%d\n", a[find(actual[k])]); // Find root and output value
    } else if (op == 3) { // Criticize range [l, r] where r - l is odd
      scanf("%d %d", &l, &r);
      vector<int> aa, bb;
      // Group elements based on whether their height is less than midpoint of l and r
      for (auto it = m.lower_bound(l); it != m.upper_bound(r); ++it)
        (it->first * 2 < (l + r) ? aa : bb).push_back(it->second);
      m.erase(m.lower_bound(l), m.upper_bound(r)); // Remove these entries from map
      mapAll(aa, l - 1, m); // Reinsert into map with adjusted value (to be less than l)
      mapAll(bb, r + 1, m); // Reinsert as greater than r
    }
  }
}


// https://github.com/VaHiX/codeForces/