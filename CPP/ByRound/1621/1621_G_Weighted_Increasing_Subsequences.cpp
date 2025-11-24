// Problem: CF 1621 G - Weighted Increasing Subsequences
// https://codeforces.com/contest/1621/problem/G

/*
 * Problem: Weighted Increasing Subsequences
 * 
 * Purpose: Calculate the sum of weights of all increasing subsequences in the given array.
 * 
 * Algorithm:
 * - Coordinate compression and sorting using order array.
 * - Using Binary Indexed Tree (Fenwick Tree) to efficiently calculate prefix sums and updates.
 * - Two passes (forward and backward) to calculate weights for each element:
 *   - Forward pass: w1[i] = number of increasing subsequences ending at position i.
 *   - Backward pass: w2[i] = number of increasing subsequences starting at position i.
 * - A third pass to compute final weights for each element.
 * - Final result is the sum over all elements of w1[i] * (w2[i] - w[i]) modulo 10^9+7.
 * 
 * Time Complexity: O(n log n) per test case due to sorting and Fenwick Tree operations.
 * Space Complexity: O(n) for storing arrays and auxiliary structures.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define N 200005
#define MOD 1000000007
#define pb push_back

int T, n, s, ans, a[N], ord[N], ps[N], vl[N], w1[N], w2[N], w[N];

// Add two numbers modulo MOD
int add(int x, int y) {
  x += y;
  return x < MOD ? x : x - MOD;
}

// Custom comparator for sorting indices by value, then by index in descending order for ties
bool cmp(int x, int y) { 
    return a[x] == a[y] ? x > y : a[x] < a[y]; 
}

// Clear the Fenwick Tree
void clear() {
  s = 0;
  for (int i = 1; i <= n; ++i)
    vl[i] = 0;
}

// Update the Fenwick Tree at position x with value w
void upd(int x, int w) {
  s = add(s, w);
  for (; x <= n; x += x & -x)
    vl[x] = add(vl[x], w);
}

// Query prefix sum up to position x in Fenwick Tree
int qSm(int x) {
  int res = 0;
  for (; x; x -= x & -x)
    res = add(res, vl[x]);
  return res;
}

// Solve for one test case
void slv() {
  scanf("%d", &n);
  ans = 0;
  for (int i = 1; i <= n; ++i)
    ord[i] = i, scanf("%d", &a[i]);
  sort(ord + 1, ord + n + 1, cmp);  // Sort indices by value
  for (int i = 1; i <= n; ++i)
    a[ord[i]] = i;  // Re-index values to compressed space
  clear();
  
  // Forward pass to calculate w1[i] - count of subsequences ending at i
  for (int i = 1; i <= n; ++i)
    w1[i] = qSm(a[i]) + 1, upd(a[i], w1[i]);  // Add to Fenwick Tree
  
  clear();
  
  // Backward pass to calculate w2[i] - count of subsequences starting at i
  for (int i = n; i; --i)
    w2[i] = add(s, MOD - qSm(a[i])) + 1, upd(a[i], w2[i]);  // Add to Fenwick Tree
  
  // Precompute ps[i] = largest index j where a[j] < i
  for (int i = 1, t = n; i <= n; ++i) {
    while (t && a[t] < i)
      --t;
    ps[i] = t;
  }
  
  clear();
  
  // Calculate final weights w[i] for each element
  for (int i = n; i; --i)
    if (ps[a[i]] <= i)
      w[i] = 1;
    else
      w[i] = add(qSm(a[ps[a[i]]]), MOD - qSm(a[i] - 1)) + 1, upd(a[i], w[i]);  // Add to Fenwick Tree
  
  // Compute total answer
  for (int i = 1; i <= n; ++i)
    ans = add(ans, 1ll * w1[i] * add(w2[i], MOD - w[i]) % MOD);
  printf("%d\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--)
    slv();
  return 0;
}


// https://github.com/VaHiX/CodeForces/