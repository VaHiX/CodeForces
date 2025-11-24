// Problem: CF 1685 E - The Ultimate LIS Problem
// https://codeforces.com/contest/1685/problem/E

/*
 * Problem: E. The Ultimate LIS Problem
 * 
 * Purpose: 
 * This code handles a problem related to finding a cyclic shift of a permutation 
 * such that the length of the longest increasing subsequence (LIS) is at most n.
 * The permutation is subject to multiple swaps, and after each swap, we determine 
 * a valid cyclic shift or indicate impossibility.
 * 
 * Approach:
 * - The solution uses a segment tree to maintain information about the elements 
 *   in the permutation and how they contribute to LIS properties.
 * - Elements are categorized based on their value relative to (n+1) to build 
 *   the segment tree.
 * - For each update, the segment tree is updated, and then queries are made to 
 *   find a valid starting position for a cyclic shift that satisfies the LIS constraint.
 * - The key insight is that we can compute the LIS value of a cyclic shift by 
 *   processing a prefix sum in the segment tree and checking certain conditions.
 * 
 * Time Complexity: O(q * log(2n+1)) where q is the number of queries
 * Space Complexity: O(4 * (2n+1)) for the segment tree, which is O(n)
 * 
 * Algorithms/Techniques: Segment Tree, Prefix Sum, Cyclic Shift, LIS Analysis
 */

#include <stdio.h>
#include <utility>

using namespace std;
int n, q, N, a[200005], pos[200005];
int sum[524300], pre[524300], id[524300];
struct info {
  int c, l, r;
} d0[524300], d1[524300];

// Custom operator to merge segment tree information
info operator+(info a, info b) {
  if (a.l < 0)
    return b;
  if (b.l < 0)
    return a;
  int t1 = a.r % (n + 1), t2 = b.l % (n + 1);
  return (info){a.c + b.c + ((t2 - t1 + n + 1) % (n + 1) == 1), a.l, b.r};
}

// Pushes up the computed values from children to parent node
void pushup(int i) {
  int ls = i << 1, rs = i << 1 | 1;
  sum[i] = sum[ls] + sum[rs];
  if (pre[ls] <= pre[rs] + sum[ls])
    pre[i] = pre[ls], id[i] = id[ls];
  else
    pre[i] = pre[rs] + sum[ls], id[i] = id[rs];
  d0[i] = d0[ls] + d0[rs];
  d1[i] = d1[ls] + d1[rs];
}

// Initializes a node in the segment tree based on element value
void init(int i, int p) {
  if (a[p] < n + 1) {
    sum[i] = -1, pre[i] = -1, id[i] = p;
    d0[i] = (info){0, a[p], a[p]};
    d1[i] = (info){0, -1, -1};
  }
  if (a[p] == n + 1) {
    sum[i] = 0, pre[i] = 0, id[i] = p;
    d0[i] = (info){0, a[p], a[p]};
    d1[i] = (info){0, a[p], a[p]};
  }
  if (a[p] > n + 1) {
    sum[i] = 1, pre[i] = 0, id[i] = p - 1;
    d0[i] = (info){0, -1, -1};
    d1[i] = (info){0, a[p], a[p]};
  }
}

// Builds the segment tree recursively
void built(int i, int l, int r) {
  if (l == r) {
    init(i, l);
    return;
  }
  int md = (l + r) >> 1;
  built(i << 1, l, md), built(i << 1 | 1, md + 1, r);
  pushup(i);
}

// Updates the segment tree at a specific position
void upd(int i, int l, int r, int p) {
  if (l == r) {
    init(i, l);
    return;
  }
  int md = (l + r) >> 1;
  if (p <= md)
    upd(i << 1, l, md, p);
  else
    upd(i << 1 | 1, md + 1, r, p);
  pushup(i);
}

// Calculates prefix sum up to position p
int calcs(int i, int l, int r, int p) {
  if (l == r)
    return sum[i];
  int md = (l + r) >> 1;
  if (md >= p)
    return calcs(i << 1, l, md, p);
  return sum[i << 1] + calcs(i << 1 | 1, md + 1, r, p);
}

int main() {
  scanf("%d%d", &n, &q), N = n + n + 1;
  for (int i = 1; i <= N; i++)
    scanf("%d", &a[i]), pos[a[i]] = i;
  built(1, 1, N);
  while (q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    swap(a[u], a[v]), swap(pos[a[u]], pos[a[v]]);
    upd(1, 1, N, u), upd(1, 1, N, v);
    int p = pos[n + 1];
    int s = p < 2 ? 0 : calcs(1, 1, N, p - 1);
    int t0 = d0[1].c + ((d0[1].l - d0[1].r + n + 1) % (n + 1) == 1);
    int t1 = d1[1].c + ((d1[1].l - d1[1].r + n + 1) % (n + 1) == 1);
    if (s != pre[1]) {
      printf("%d\n", id[1]);
      continue;
    }
    if (t0 != n + 1) {
      printf("%d\n", p % N);
      continue;
    }
    if (t1 != n + 1) {
      printf("%d\n", p - 1);
      continue;
    }
    puts("-1");
  }
}


// https://github.com/VaHiX/CodeForces/