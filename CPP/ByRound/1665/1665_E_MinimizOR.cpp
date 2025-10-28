// Problem: CF 1665 E - MinimizOR
// https://codeforces.com/contest/1665/problem/E

// Problem: E. MinimizOR
// Task: For each query (l, r), find the minimum value of a_i | a_j for all i != j in subarray [l, r]
// Algorithm: Trie-based approach with persistent segment trees to efficiently compute minimum OR values
// Time Complexity: O(n * log(max_val) + q * log(max_val)) where max_val < 2^30
// Space Complexity: O(n * log(max_val))

#include <stdio.h>
#include <string.h>
#include <iostream>

#define use 1, n, rt
#define left l, mid, ls[p]
#define righ mid + 1, r, rs[p]
#define N 400000 * 35
#define mod 998244353
#define fer(x, y, z) for (register int x = y; x <= z; x++)
using namespace std;
int lct, tr[N][2], sum[N], rt[110000];
int sta[110000], ss, n;

// Build persistent trie
void sak_tr(int &p, int pr, int wei, int num) {
  p = ++lct; // Allocate new node
  sum[p] = sum[pr] + 1; // Increment count of elements up to this node
  if (wei == 1)
    return;
  int to = ((num & (1 << wei - 2)) != 0); // Determine which bit is set at current position
  tr[p][to ^ 1] = tr[pr][to ^ 1]; // Copy other branch from parent
  sak_tr(tr[p][to], tr[pr][to], wei - 1, num); // Recursively build the current branch
}

// Find a number that minimizes OR with given prefix
int sak_fi(int p, int pr, int wei, int num) {
  if (wei == 1)
    return num; // Base case: return constructed number
  int to = 1;
  if (sum[tr[p][0]] - sum[tr[pr][0]]) // Check if there's a 0-bit in current level that leads to minimal OR
    to = 0;
  return sak_fi(tr[p][to], tr[pr][to], wei - 1, (num << 1) | to); // Recurse and build result
}

// Query the minimum OR value in range [l, r]
int sak_qu(int p, int pr, int wei, int num) {
  if (wei == 1)
    return num; // Return constructed number at leaf
  int to, c1 = 0, c0 = 0;
  fer(i, 1, ss) if ((sta[i] & (1 << wei - 2)) != 0) c1++; // Count elements with 1s in current bit
  else c0++;
  to = (sum[tr[p][0]] - sum[tr[pr][0]] + c0 <= 1); // Determine next bit selection
  int res = 0;
  if (to == 0) { // Copy all elements where current bit is 0 into stack
    fer(i, 1, ss) if ((sta[i] & (1 << wei - 2)) == to) sta[++res] = sta[i];
    ss = res;
  }
  if (sum[tr[p][0]] - sum[tr[pr][0]] == 1 && c0 == 0) // If there's exactly one element with 0-bit, add it to stack
    sta[++ss] = sak_fi(tr[p][0], tr[pr][0], wei - 1, num << 1);
  return sak_qu(tr[p][to], tr[pr][to], wei - 1, (num << 1) | to); // Recurse on selected branch
}

signed main() {
  int t;
  cin >> t;
  while (t--) {
    fer(i, 1, lct) sum[i] = tr[i][0] = tr[i][1] = 0; // Reset trie
    memset(rt, 0, n * 4 + 4), lct = 0; // Reset roots and node counter
    scanf("%d", &n);
    int x, l, r;
    fer(i, 1, n) scanf("%d", &x), sak_tr(rt[i], rt[i - 1], 33, x); // Build segment tree with trie roots
    int q;
    scanf("%d", &q);
    while (q--)
      scanf("%d%d", &l, &r), ss = 0,
                             printf("%d\n", sak_qu(rt[r], rt[l - 1], 33, 0)); // Process query
  }
}


// https://github.com/VaHiX/codeForces/