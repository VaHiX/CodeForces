// Problem: CF 1830 E - Bully Sort
// https://codeforces.com/contest/1830/problem/E

/*
 * Overview
 * --------
 * This program solves the "Bully Sort" problem: given a permutation a[1..n],
 * answer m queries where each query is an update (swap two elements) and we
 * must compute the sum of absolute differences |a[i] - i| after each update.
 *
 * However, the key insight is that bully sort moves each element to its "ideal"
 * position by counting how many elements above its target are to the right of
 * it. The final cost is the sum of these counts per element, which equals the
 * total number of inversions between the array and the identity permutation.
 *
 * Problem decomposes into:
 * 1. Track the sum of |a[i] - i| for all i (easily maintained with swaps)
 * 2. Count inversions (pairs (i,j) where i < j but a[i] > a[j]) in the
 *    modified array after each update
 *
 * Algorithm:
 * - Use offline processing with merge sort tree (CDQ divide-and-conquer)
 * - Precompute all swaps and position changes upfront
 * - During merge sort tree solve, accumulate inversion contributions
 * - Combine position sum with inversion count to get final answer
 *
 * Key techniques:
 * - Binary Indexed Tree (Fenwick tree) for efficient range queries
 * - Merge sort tree (CDQ divide-and-conquer) for offline 2D range queries
 * - Coordinate compression implicit in BIT operations
 *
 * Time Complexity: O((n + m*2) * log^2(n + m*2))
 * - We process O(m) updates, each creating 2 removals and 2 insertions = O(m)
 * ops
 * - Merge sort tree: log(n+m) levels, each level does O(n+m) BIT ops, each
 * O(log n)
 *
 * Space Complexity: O(n + m)
 * - Arrays for permutation, updates, and operation stream
 * - BIT and temporary arrays
 */

#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & (-x)) // Extract lowest set bit (used in BIT indexing)
using namespace std;
const int N = 5e5 + 10, M = 5e4 + 10;

// Fast custom template-based input for competitive programming
// Supports reading single or multiple values with one call
template <class T> inline void read(T &x) {
  x = 0;
  int f = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  if (f)
    x = ~x + 1;
}
template <class T, class... T1> inline void read(T &x, T1 &...x1) {
  read(x), read(x1...);
}
int n, m;
int tot;
int a[N], t[N]; // a: permutation, t: BIT array for inversion counting

// Operation struct: represents add/remove events for merge sort tree
// t: timestamp (query index); p: position in array; x: value; y: +1 (add) or -1
// (remove)
struct Op {
  int t, p, x, y;
} q[N + (M << 2)], w[N + (M << 2)];

ll res[M], ans[M]; // res: position cost (|a[i]-i|), ans: inversion contribution

// Binary Indexed Tree (Fenwick tree) for efficient range queries and point
// updates Used to count inversions: how many elements > current value appear to
// the right
inline void add(int x, int k) {
  for (; x <= n; x += lowbit(x))
    t[x] += k;
}
inline int ask(int x) {
  int res = 0;
  for (; x; x -= lowbit(x))
    res += t[x];
  return res;
}
// Merge sort tree (CDQ divide-and-conquer) for offline 2D range queries
// Processes events q[l..r] by:
// 1. Recursively solving left half [l..mid]
// 2. Recursively solving right half [mid+1..r]
// 3. Merging: for each query in right half, count contributions from left half
//    that affect it, using BIT to track inversions
// 4. Merging: repeat in reverse for symmetric inversion counting
//
// Key insight: divide by position (p), conquer by timestamp (t)
// For each query at timestamp t and position p, we count how many updates
// to positions > p with value < x happened before time t (and vice versa)
void solve(int l, int r) {
  if (l >= r)
    return;
  int mid = l + r >> 1;
  solve(l, mid), solve(mid + 1, r);

  // First merge pass: process left half updates then right half queries
  // Count inversions where left element goes right of right element
  int i = l, j = mid + 1, k = l;
  auto lm = [&]() { add(q[i].x, q[i].y), w[k++] = q[i++]; };
  auto mr = [&]() {
    // For each query (right half), count how many left-half updates > q[j].x
    // contribute to inversions (ask for elements > q[j].x)
    ans[q[j].t] += (ask(n) - ask(q[j].x)) * q[j].y, w[k++] = q[j++];
  };
  while (i <= mid && j <= r) {
    if (q[i].p <= q[j].p)
      lm();
    else
      mr();
  }
  while (i <= mid)
    lm();
  while (j <= r)
    mr();
  // Clean up BIT for second pass
  for (int i = l; i <= mid; i++)
    add(q[i].x, -q[i].y);

  // Second merge pass: process right half updates then left half queries
  // (reversed) Count inversions where right element goes left of left element
  i = mid, j = r;
  auto ml = [&]() { add(q[i].x, q[i].y), i--; };
  auto rm = [&]() {
    // For each query (left half), count how many right-half updates < q[j].x
    // contribute to inversions (ask for elements < q[j].x)
    ans[q[j].t] += ask(q[j].x - 1) * q[j].y, j--;
  };
  while (i >= l && j >= mid + 1) {
    if (q[i].p >= q[j].p)
      ml();
    else
      rm();
  }
  while (i >= l)
    ml();
  while (j >= mid + 1)
    rm();
  // Clean up BIT again
  for (int i = l; i <= mid; i++)
    add(q[i].x, -q[i].y);

  // Merge the two sorted subarrays back into q
  for (int i = l; i <= r; i++)
    q[i] = w[i];
}
int main() {
  read(n, m);

  // Initialize: read permutation and build initial query operations
  // Each element contributes |a[i] - i| to the position cost
  for (int i = 1; i <= n; i++)
    read(a[i]),
        q[++tot] = {0, i, a[i],
                    1}, // timestamp 0: add element a[i] at position i
        res[0] += abs(a[i] - i);

  // Process m update queries
  for (int i = 1; i <= m; i++) {
    int x, y;
    read(x, y); // Swap positions x and y

    // Inherit position cost from previous query and adjust for swap
    res[i] = res[i - 1];
    res[i] -= abs(a[x] - x) + abs(a[y] - y); // Remove old contributions

    // Record removal of old values before swap
    q[++tot] = {i, x, a[x], -1};
    q[++tot] = {i, y, a[y], -1};

    // Perform swap
    swap(a[x], a[y]);

    // Record addition of new values after swap
    q[++tot] = {i, x, a[x], 1};
    q[++tot] = {i, y, a[y], 1};

    res[i] += abs(a[x] - x) + abs(a[y] - y); // Add new contributions
  }

  // Run merge sort tree to compute inversion contributions
  solve(1, tot);

  // Compute and output final answers
  // Answer for query i = (position cost) - (inversion count)
  for (int i = 1; i <= m; i++) {
    ans[i] += ans[i - 1]; // Accumulate inversion count
    printf("%lld\n", res[i] - ans[i]);
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/