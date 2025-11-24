// Problem: CF 1515 H - Phoenix and Bits
// https://codeforces.com/contest/1515/problem/H

/*
H. Phoenix and Bits
Algorithm: Trie with lazy propagation for range operations on bits
Time Complexity: 
    - Add/Query/Update: O(LG) per operation where LG = 20
    - Overall: O((N + Q) * LG)
Space Complexity: O((N + Q) * LG)
*/
#include <stdio.h>

#define N 200000
#define Q 100000
#define N_ ((N + Q * 2) * (LG + 1))
#define LG 20
#define B (1 << LG)
int ll[1 + N_], rr[1 + N_], sz[1 + N_], msk0[1 + N_], msk1[1 + N_], lz[1 + N_],
    _ = 1;

// Propagate lazy updates to children
void put(int u, int lg, int x) {
  int tmp, x0, x1;
  if (u == 0)
    return;
  // Rotate left and right children based on current bit value
  if ((x & 1 << lg - 1) != 0)
    tmp = ll[u], ll[u] = rr[u], rr[u] = tmp;
  // Update masks for bits that are flipped or not
  x0 = msk0[u] & ~x | msk1[u] & x, x1 = msk1[u] & ~x | msk0[u] & x;
  msk0[u] = x0, msk1[u] = x1;
  lz[u] ^= x; // Toggle the lazy value
}

// Push lazy values to children
void pus(int u, int lg) {
  if (lz[u])
    put(ll[u], lg - 1, lz[u]), put(rr[u], lg - 1, lz[u]), lz[u] = 0;
}

// Update node size and masks after merge
void pul(int u) {
  int l = ll[u], r = rr[u];
  sz[u] = sz[l] + sz[r], msk0[u] = msk0[l] | msk0[r],
  msk1[u] = msk1[l] | msk1[r];
}

// Insert a value into the trie
int add(int u, int lg, int a) {
  if (u == 0)
    u = _++;
  if (lg == 0)
    sz[u] = 1, msk0[u] = a ^ B - 1, msk1[u] = a;
  else {
    // Traverse left or right based on current bit
    if ((a & 1 << lg - 1) == 0)
      ll[u] = add(ll[u], lg - 1, a);
    else
      rr[u] = add(rr[u], lg - 1, a);
    pul(u);
  }
  return u;
}

// Split subtrie into two parts based on range [ql, qr)
void split(int *u, int *v, int lg, int l, int r, int ql, int qr) {
  int m;
  if (qr <= l || r <= ql || *u == 0) {
    *v = 0;
    return;
  }
  if (ql <= l && r <= qr) {
    *v = *u, *u = 0;
    return;
  }
  pus(*u, lg), *v = _++;
  m = (l + r) / 2;
  split(&ll[*u], &ll[*v], lg - 1, l, m, ql, qr),
      split(&rr[*u], &rr[*v], lg - 1, m, r, ql, qr);
  pul(*u), pul(*v);
}

// Merge two tries recursively
void merge(int *u, int *v, int lg) {
  if (*u == 0) {
    *u = *v;
    return;
  }
  if (*v == 0 || lg == 0)
    return;
  pus(*u, lg), pus(*v, lg);
  merge(&ll[*u], &ll[*v], lg - 1), merge(&rr[*u], &rr[*v], lg - 1);
  pul(*u);
}

// Update or operation on specified range
void update_or(int u, int lg, int x) {
  if (u == 0)
    return;
  // If no bits are common between x and current node's mask, update entire subtree
  if ((x & msk0[u] & msk1[u]) == 0) {
    put(u, lg, x & msk0[u]);
    return;
  }
  pus(u, lg);
  // Handle the case when current bit is set in x and move to right child
  if ((x & 1 << lg - 1) != 0)
    put(ll[u], lg - 1, 1 << lg - 1), merge(&rr[u], &ll[u], lg - 1), ll[u] = 0;
  update_or(ll[u], lg - 1, x), update_or(rr[u], lg - 1, x);
  pul(u);
}

// Query number of distinct values in range [ql, qr)
int query(int u, int lg, int l, int r, int ql, int qr) {
  int m;
  if (qr <= l || r <= ql || u == 0)
    return 0;
  if (ql <= l && r <= qr)
    return sz[u];
  pus(u, lg);
  m = (l + r) / 2;
  return query(ll[u], lg - 1, l, m, ql, qr) +
         query(rr[u], lg - 1, m, r, ql, qr);
}

int main() {
  int n, q, i, u;
  scanf("%d%d", &n, &q);
  u = 0;
  for (i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    u = add(u, LG, a);
  }
  while (q--) {
    int type, l, r;
    scanf("%d%d%d", &type, &l, &r), r++;
    if (type != 4) {
      int x, v;
      scanf("%d", &x);
      split(&u, &v, LG, 0, B, l, r); // Split into [l,r) and rest
      if (type == 1)
        put(v, LG, B - 1), update_or(v, LG, x ^ B - 1), put(v, LG, B - 1);
      else if (type == 2)
        update_or(v, LG, x);
      else
        put(v, LG, x);
      merge(&u, &v, LG); // Merge back into original trie
    } else
      printf("%d\n", query(u, LG, 0, B, l, r));
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/