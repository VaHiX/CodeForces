/*
Problem 1810F: M-tree (Codeforces) - C++ Solution
--------------------------------------------------
Given n positions with initial values (treated as digits in base m),
handle q updates changing position i to value y.
For each update, find the first position where we can increment without
exceeding m.

Key Insight: Treat array as base-m digits with carries/borrows.
- When incrementing position at index i: check if all carry positions can be
satisfied
- When decrementing (borrow): backtrack through chain of (m-1) values
- Answer: rightmost non-zero digit, adjusted based on structure

Algorithm:
- Use lazy segment tree to track sum of digit values at each position
- upd1(i): increment digit at position i, handling carries upward
- upd2(i): decrement digit at position i, setting to (m-1) (borrow)
- qry(): find rightmost position with non-zero digit
- Additional check: if sum >= 2, answer is rightmost+1

Segment Tree with Lazy Propagation:
- st[u] = sum of digit values in range
- lz[u] = lazy value to propagate (-1 = no pending update)
- Range updates and queries in O(log^2 n)

Time Complexity: O(q * log^2(n)) per test case
Space Complexity: O(n * log(n))
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN = 2e5;
int n, m, q, a[mxN], st[1 << 19], lz[1 << 19];

// Push lazy value from node u down to its children
// Applies pending updates: set st[u] to lazy value * range size, propagate to
// children
void psh(int u, int l, int r) {
  if (~lz[u]) {                  // If lazy update pending (lz[u] != -1)
    st[u] = lz[u] * (r - l + 1); // Set all values in range to lz[u]
    if (l != r)                  // If not a leaf, propagate to children
      lz[2 * u] = lz[2 * u + 1] = lz[u];
    lz[u] = -1; // Clear lazy flag
  }
}

// Increment digit at position i, propagating carries if needed
// Returns true if successfully incremented without hitting (m-1) saturation
// Recursively tries left child first, then right child
bool upd1(int i, int u = 1, int l = 1, int r = mxN + 20) {
  psh(u, l, r); // Apply any pending lazy updates

  if (r < i)
    return 0; // Position i is beyond this range

  // If all elements in range are at maximum (m-1), set to 0 (carry occurred)
  if (l >= i && st[u] == (m - 1) * (r - l + 1)) {
    lz[u] = 0;
    psh(u, l, r);
    return 0; // Carry signal: couldn't increment further
  }

  if (l == r) { // Leaf node: increment this digit
    ++st[u];
    return 1; // Successfully incremented
  }

  // Recursively try to increment: left child first, then right child
  int mid = (l + r) / 2;
  bool ret = upd1(i, 2 * u, l, mid) ? 1 : upd1(i, 2 * u + 1, mid + 1, r);
  psh(2 * u + 1, mid + 1, r);        // Ensure right child is up-to-date
  st[u] = st[2 * u] + st[2 * u + 1]; // Merge results
  return ret;
}

// Decrement digit at position i (borrow operation)
// Returns true if successfully decremented without hitting 0 (zero stay)
// Sets range to (m-1) when borrowing, tries left child first then right
bool upd2(int i, int u = 1, int l = 1, int r = mxN + 20) {
  psh(u, l, r); // Apply any pending lazy updates

  if (r < i)
    return 0; // Position i is beyond this range

  // If entire range is 0, set to (m-1) (borrow occurred)
  if (l >= i && !st[u]) {
    lz[u] = m - 1;
    psh(u, l, r);
    return 0; // Borrow signal: couldn't decrement further
  }

  if (l == r) { // Leaf node: decrement this digit
    --st[u];
    return 1; // Successfully decremented
  }

  // Recursively try to decrement: left child first, then right child
  int mid = (l + r) / 2;
  bool ret = upd2(i, 2 * u, l, mid) ? 1 : upd2(i, 2 * u + 1, mid + 1, r);
  psh(2 * u + 1, mid + 1, r);        // Ensure right child is up-to-date
  st[u] = st[2 * u] + st[2 * u + 1]; // Merge results
  return ret;
}

// Query: find rightmost (largest index) position with non-zero digit sum
// Returns -1 if no non-zero digits exist
// Queries right subtree first (seeking larger indices) then left if needed
int qry(int u = 1, int l = 1, int r = mxN + 20) {
  psh(u, l, r); // Apply any pending lazy updates

  if (!st[u])
    return -1; // No non-zero values in this range

  if (l == r)
    return l; // Found the position

  int mid = (l + r) / 2;
  // Query right subtree first (seeking rightmost position)
  int x = qry(2 * u + 1, mid + 1, r);
  // If right subtree has no result, try left subtree
  return x != -1 ? x : qry(2 * u, l, mid);
}

// Solve one test case
void solve() {
  cin >> n >> m >> q;

  // Read initial array and build initial state in segment tree
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    upd1(a[i]); // Increment count at position a[i]
  }

  // Process q updates
  while (q--) {
    int i, x;
    cin >> i >> x, --i; // Convert to 0-indexed

    // Update: remove old value, add new value
    upd2(a[i]);     // Decrement count at position a[i]
    upd1(a[i] = x); // Increment count at position x

    // Query answer: rightmost non-zero digit, plus 1 if total sum >= 2
    // st[1] >= 2 means we can increment at rightmost+1 position
    cout << qry() + (st[1] > 1) << " ";
  }

  cout << "\n";

  // Cleanup: remove all values from segment tree for next test case
  for (int i = 0; i < n; ++i)
    upd2(a[i]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  memset(lz, -1,
         sizeof(lz)); // Initialize lazy array to -1 (no pending updates)

  int t;
  cin >> t; // Read number of test cases
  while (t--)
    solve(); // Process each test case

  return 0;
}

// https://github.com/VaHiX/CodeForces/