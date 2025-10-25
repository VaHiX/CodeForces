// Problem: CF 2084 F - Skyscape
// https://codeforces.com/contest/2084/problem/F

/*
F. Skyscape
Algorithms/Techniques: BIT (Binary Indexed Tree), Greedy, Simulation

Time Complexity: O(n log n)
Space Complexity: O(n)

Problem Description:
Given a permutation 'a' and partial permutation 'c', find a complete permutation 'b'
such that b is good (can be transformed to a through right cyclic shifts of subarrays
where the last element is the minimum in the subarray). The elements of b must match
those of c where c[i] != 0.

The solution uses two BITs to track the maximum and minimum positions of elements,
and greedy assignment along with priority queues to construct valid permutations.
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int N = 5e5 + 10;
const int inf = 2e9;
int n, m;
int a[N], b[N], c[N];
int p[N], q[N];
#define lowbit(x) (x & -x)
struct BIT {
  int t[N];
  void init() {
    for (int i = 0; i <= n; i++)
      t[i] = 0;
  }
  void add(int x, int y) {
    for (; x <= n; x += lowbit(x))
      t[x] = max(t[x], y);
  }
  int qry(int x) {
    int mx = 0;
    for (; x; x -= lowbit(x))
      mx = max(mx, t[x]);
    return mx;
  }
} t;
struct BIT2 {
  int t[N];
  void init() {
    for (int i = 0; i <= n; i++)
      t[i] = inf;
  }
  void add(int x, int y) {
    for (; x; x -= lowbit(x))
      t[x] = min(t[x], y);
  }
  int qry(int x) {
    int mx = inf;
    for (; x <= n; x += lowbit(x))
      mx = min(mx, t[x]);
    return mx;
  }
} t2;
struct node {
  int r, x;
  friend bool operator<(const node &x, const node &y) {
    return x.r > y.r || (x.r == y.r && x.x > y.x);
  }
};
vector<node> g[N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    p[i] = q[i] = c[i] = 0, g[i].clear();
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[a[i]] = i; // Store position of each element in 'a'
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    if (b[i])
      q[b[i]] = i; // Store positions of elements in 'c' that are not 0
  }
  t.init();
  for (int i = 1; i <= n; i++) {
    if (q[i]) { // If element i is fixed in the input permutation
      if (t.qry(p[i]) > q[i])
        return cout << "-1\n", void(); // Check constraint on existing values
      t.add(p[i], q[i]); // Add to BIT for tracking upper limit
    }
  }
  t.init();
  t2.init();
  for (int i = 1; i <= n; i++) {
    if (q[a[i]]) { // If a[i] is in the fixed positions set, add it to BIT
      t.add(a[i], q[a[i]]);
    } else
      c[i] = t.qry(a[i]) + 1; // Use BIT to assign the minimum possible number
  }
  for (int i = n; i >= 1; i--) {
    if (q[a[i]]) { // If a[i] is fixed, update opposite BIT
      t2.add(a[i], q[a[i]]);
    } else {
      int r = t2.qry(a[i]) - 1; // Get the maximum possible value from opposite BIT
      if (r < c[i])
        return cout << "-1\n", void(); // If r is smaller than minimal requirement, impossible
      g[c[i]].push_back({r, a[i]}); // Push valid elements into group of current level
    }
  }
  priority_queue<node> q;
  for (int i = 1; i <= n; i++) {
    for (node p : g[i])
      q.push(p); // Push all elements to queue sorted by 'r' value
    if (!b[i]) { // If not assigned yet in c, assign from queue
      if (q.empty() || q.top().r < i)
        return cout << "-1\n", void(); // Impossible case
      b[i] = q.top().x;
      q.pop();
    }
  }
  for (int i = 1; i <= n; i++)
    cout << b[i] << " \n"[i == n]; // Output final permutation
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/