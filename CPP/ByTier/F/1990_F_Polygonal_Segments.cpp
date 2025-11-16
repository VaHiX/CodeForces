// Problem: CF 1990 F - Polygonal Segments
// https://codeforces.com/contest/1990/problem/F

/*
Algorithm: Segment Tree with Merge Operation
Purpose: Efficiently handle two types of queries on an array:
         1. Find the longest polygonal segment in a range [l, r]
         2. Update an element in the array
         A polygonal segment must have at least 3 sides and satisfy the polygon inequality:
         the longest side must be less than the sum of all other sides.
         Uses a segment tree where each node stores information about the maximum valid polygonal segment.

Time Complexity: 
  - Initialization: O(n log n)
  - Update: O(log n)
  - Query: O(log^2 n)
Space Complexity: O(n log n)

*/
#include <iostream>
#include <algorithm>

#define LL long long
using namespace std;
const int kMaxN = 2e5 + 1;
struct V {
  LL w, s;
  int c, ans;
  int l, r;
} v[kMaxN * 40];
int t, n, m, k, s[kMaxN * 4];
LL a[kMaxN];
void Pushup(int x) {
  // Update node properties based on children
  v[x].s = v[x].w, v[x].c = 1, v[x].ans = -1;
  if (v[x].l) {
    v[x].s += v[v[x].l].s, v[x].c += v[v[x].l].c;
    v[x].ans = max(v[x].ans, v[v[x].l].ans);
  }
  if (v[x].r) {
    v[x].s += v[v[x].r].s, v[x].c += v[v[x].r].c;
    v[x].ans = max(v[x].ans, v[v[x].r].ans);
  }
}
int Merge(int x, int y) {
  // Merge two nodes maintaining polygonal properties
  if (!x || !y) {
    return x | y;
  }
  int p = ++k;
  // Check if polygon condition is satisfied
  if (max(v[x].w, v[y].w) * 2 < v[x].s + v[y].s) {
    // Valid polygon with all sides
    v[p] = {max(v[x].w, v[y].w), v[x].s + v[y].s, v[x].c + v[y].c,
            v[x].c + v[y].c};
  } else if (v[x].w >= v[y].w) {
    // Propagate from x
    v[p] = v[x], v[p].r = Merge(v[p].r, y), Pushup(p);
  } else {
    // Propagate from y
    v[p] = v[y], v[p].l = Merge(x, v[p].l), Pushup(p);
  }
  return p;
}
void Init(int p, int l, int r) {
  // Initialize the segment tree recursively
  if (l == r) {
    s[p] = ++k, v[s[p]] = {a[l], a[l], 1, -1};
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  s[p] = Merge(s[p << 1], s[p << 1 | 1]);
}
void Update(int p, int l, int r, int x) {
  // Update element at position x
  if (l == r) {
    v[s[p]] = {a[l], a[l], 1, -1};
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Update(p << 1, l, mid, x);
  } else {
    Update(p << 1 | 1, mid + 1, r, x);
  }
  s[p] = Merge(s[p << 1], s[p << 1 | 1]);
}
int Ask(int p, int l, int r, int _l, int _r) {
  // Query for the longest polygonal segment in range [_l, _r]
  if (l >= _l && r <= _r) {
    return s[p];
  }
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    int x = Ask(p << 1, l, mid, _l, _r);
    int y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
    int ans = Merge(x, y);
    return ans;
  } else if (mid >= _l) {
    return Ask(p << 1, l, mid, _l, _r);
  } else {
    return Ask(p << 1 | 1, mid + 1, r, _l, _r);
  }
}
int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    k = 0, Init(1, 1, n);
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x;
      if (x == 1) {
        cin >> x >> y;
        cout << v[Ask(1, 1, n, x, y)].ans << '\n';
      } else {
        cin >> x >> a[x];
        Update(1, 1, n, x);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/