// Problem: CF 2080 D - Order Statistics
// https://codeforces.com/contest/2080/problem/D

/*
 * Purpose:
 * This code solves a dynamic order statistics problem where we need to maintain
 * array values and answer queries after applying operations that modify the
 * array or request statistics about certain ranges.
 *
 * Problem Description:
 * - Given an array A of length n and initial parameters m0, k0
 * - Support three types of operations:
 *   1. Query order statistics in range [l,r] with parameters m,k
 *   2. Update single element value
 *   3. Query full array statistics with parameters m,k
 * - For each query, compute values after applying transformation:
 *   if value > threshold: value = threshold
 *   where threshold is computed to ensure k elements are modified
 *
 * Key Components:
 * 1. Fenwick Trees (BIT)
 *    - Two BITs: one for counts, one for value sums
 *    - Support point updates and range queries in O(log n)
 *    - Used for efficient prefix computations
 *
 * 2. Coordinate Compression
 *    - Maps large input values to smaller indices
 *    - Maintains order relationships while reducing space
 *    - Essential for handling large value ranges
 *
 * 3. Binary Search
 *    - Find optimal threshold values
 *    - Compute number of elements to modify
 *    - Determine range boundaries
 *
 * Complexity Analysis:
 * Time: O((n + q) * log^2(n))
 * - Each query requires binary search: O(log n)
 * - Each binary search step needs BIT operations: O(log n)
 * - Total q queries and n initial elements
 *
 * Space: O(n * log n)
 * - Fenwick trees: O(n)
 * - Coordinate compression array: O(n)
 * - Additional arrays for query processing: O(n)
 *
 * Implementation Notes:
 * - Uses long long for all integers to handle large values
 * - Preprocesses input through coordinate compression
 * - Maintains four segments for efficient statistics computation
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 10;
int n, a[N], t[N], ct, op[N], m[N], k[N], l[N], r[N], w[N];
// Fenwick Tree (Binary Indexed Tree) implementation
struct bit {
  int c[N], sum; // c: tree array, sum: total sum for optimization

  // Add value x at position a
  // Updates both total sum and tree nodes
  // Time: O(log n)
  void add(int a, int x) {
    for (sum += x; a <= ct; a += (a & -a)) // Add to nodes up the tree
      c[a] += x;
  }

  // Query prefix sum up to position a
  // Returns sum of elements in range [1..a]
  // Time: O(log n)
  int ask(int a) {
    if (a == ct) // Optimization for full range query
      return sum;
    int b = 0;
    for (; a; a -= (a & -a)) // Sum nodes down the tree
      b += c[a];
    return b;
  }

  // Find largest position b where prefix sum <= x
  // Uses binary lifting technique
  // Time: O(log n)
  int find(int x) {
    int b = 0, i;
    for (i = 20; i >= 0; i--) // Binary search on prefix
      if (b + (1 << i) <= ct && c[b + (1 << i)] <= x)
        b += (1 << i), x -= c[b];
    return b;
  }
} c1, c2; // c1: count BIT, c2: value sum BIT
// Helper function to update both BITs simultaneously
void add(int a, int x) {
  c1.add(a, x),            // Update count BIT
      c2.add(a, t[a] * x); // Update value sum BIT
}

// Global variables for segment boundaries and parameters
int s1, t1, // First segment: original values below threshold
    s2, t2, // Second segment: partially modified values
    s3, t3, // Third segment: fully modified values at threshold
    s4, t4, // Fourth segment: values above threshold
    o,      // Current threshold value
    M;      // Current m parameter

// Get weighted sum of first x elements using BITs
// Returns sum considering element values and counts
int get(int x) {
  int p = c1.find(x); // Find position with prefix count <= x
  // Sum up to position p + remaining elements at t[p+1]
  return c2.ask(p) + t[p + 1] * (x - c1.ask(p));
}

// Binary search in compressed coordinate array
// Returns 1-based index where x would be inserted
int lb(int x) { return lower_bound(&t[1], &t[ct] + 1, x) - t; }

// Calculate prefix sum up to position x
// Handles four different segments with different computations
int presum(int x) {
  if (x <= s1) // First segment: original values
    return get(x);
  if (x <= s1 + s2) // Second segment: partial modifications
    return t1 + (o - 1) * (x - s1);
  if (x <= s1 + s2 + s3) // Third segment: at threshold
    return t1 + t2 + o * (x - s1 - s2);
  // Fourth segment: above threshold
  return t1 + t2 + t3 + get(x) - get(s1 + s2 + s3) - (x - s1 - s2 - s3) * M;
}

// Core solving function for queries
// Parameters:
// m: maximum difference allowed
// k: number of elements to modify
// l,r: range for query (-1 for full array query)
void slv(int m, int k, int l, int r) {
  int L = 0, R = n, mid, i;

  // First binary search: find number of elements above threshold
  while (L < R) {
    mid = (L + R + 1) >> 1;
    int a = c1.find(n - mid);         // Find position for n-mid elements
    int b = get(n - mid);             // Get their sum
    int p = lb(t[a + 1] - m) - 1;     // Find threshold boundary
    int s = c2.ask(p), u = c1.ask(p); // Get sums up to boundary

    // Check if current mid satisfies the k-modification constraint
    if (mid * m + b - s - (t[a + 1] - m) * (n - mid - u) <= m * k)
      L = mid;
    else
      R = mid - 1;
  }
  s4 = L, t4 = c2.sum - get(n - L); // Store fourth segment info

  // Second binary search: find optimal threshold value
  L = -2e9, R = 1e9;
  if (s4)                           // If we have elements above threshold
    R = t[c1.find(n - s4) + 1] - m; // Update upper bound

  while (L < R) {
    mid = (L + R) >> 1;
    int x = lb(mid) - 1; // Find position of current threshold
    // Check if current threshold satisfies remaining modifications
    if ((c2.sum - t4 - c2.ask(x)) - mid * (n - s4 - c1.ask(x)) <= m * (k - s4))
      R = mid;
    else
      L = mid + 1;
  }
  int x = lb(L) - 1;
  int a = m * (k - s4) - ((c2.sum - t4 - c2.ask(x)) - L * (n - s4 - c1.ask(x)));
  s1 = c1.ask(x), t1 = c2.ask(x);
  s2 = a, t2 = (L - 1) * s2;
  s3 = n - s1 - s2 - s4, t3 = L * s3;
  o = L, M = m;
  if (l == -1) {
    for (i = 1; i <= n; i++)
      w[i] = presum(i);
    for (i = 1; i <= n; i++)
      printf("%lld%c", w[i] - w[i - 1], " \n"[i == n]);
  } else
    printf("%lld\n", presum(r) - presum(l - 1));
}

signed main() {
  int m0, k0, q, i;

  // Read initial parameters
  scanf("%lld%lld%lld%lld", &n, &m0, &k0, &q);

  // Read array elements and store them for coordinate compression
  for (i = 1; i <= n; i++)
    scanf("%lld", &a[i]), t[i] = a[i];
  ct = n;

  // Read q queries
  for (i = 1; i <= q; i++) {
    scanf("%lld%lld%lld", &op[i], &m[i], &k[i]);
    if (op[i] == 1) // Type 1: Single element query
      scanf("%lld", &l[i]), r[i] = l[i];
    if (op[i] == 2)   // Type 2: Update value
      t[++ct] = k[i]; // Add new value to compression array
    if (op[i] == 3)   // Type 3: Range query
      scanf("%lld%lld", &l[i], &r[i]);
  }

  // Perform coordinate compression
  sort(&t[1], &t[ct] + 1);                // Sort all values
  ct = unique(&t[1], &t[ct] + 1) - t - 1; // Remove duplicates

  // Initialize BITs with compressed coordinates
  for (i = 1; i <= n; i++)
    a[i] = lb(a[i]), add(a[i], 1);

  // Process initial query for full array
  slv(m0, k0, -1, -1);

  // Process all queries
  for (i = 1; i <= q; i++) {
    if (op[i] == 2) { // Update operation
      // Remove old value, add new value in compressed coordinates
      add(a[m[i]], -1), a[m[i]] = lb(k[i]), add(a[m[i]], 1);
    } else { // Query operation
      slv(m[i], k[i], l[i], r[i]);
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/