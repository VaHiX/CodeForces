// Problem: CF 1924 B - Space Harbour
// https://codeforces.com/contest/1924/problem/B

/*
B. Space Harbour
Algorithms/Techniques: Implicit Segment Tree with Binary Indexed Tree (Fenwick Tree), Union-Find, Lazy Propagation

Time Complexity: O((m + q) * log n)
Space Complexity: O(n)

The problem involves a line of points with harbours having values.
We need to efficiently process two operations:
1. Add a new harbour at point x with value v (type 1 query).
2. Calculate total cost of moving ships from l to r to next harbour (type 2 query).

Cost calculation for ship at position i is based on the nearest harbour to its left and distance to the next harbour.
A Union-Find structure helps track connected components of harbours,
and Binary Indexed Tree supports efficient range sum queries and updates.
*/

#include <cstdio>
const int N = 300002;
typedef long long ll;
int n, m, q, i, j, k, x[N], v, V[N];
int op[N], A[N], B[N], fa[N], l[N], L, R;
ll s[N], S[N], Ans[N];

// Find root with path compression
int p(int x) { return fa[x] == x ? x : fa[x] = p(fa[x]); }

// Add value to BIT at position x
void add(int x, ll y) {
  s[x] += y;
  while (x <= n)
    S[x] += y, x += x & -x;
}

// Prefix sum query from BIT up to x
ll sum(int x) {
  ll su = 0;
  while (x)
    su += S[x], x -= x & -x;
  return su;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  
  // Read harbour positions
  for (i = 1; i <= m; i++)
    scanf("%d", x + i);
    
  // Read harbour values and assign to the corresponding positions
  for (i = 1; i <= m; i++) {
    scanf("%d", &v);
    V[x[i]] = v;
  }
  
  // Read queries and process type-1 queries to modify values
  for (i = 1; i <= q; i++) {
    scanf("%d%d%d", op + i, A + i, B + i);
    if (op[i] == 1)
      V[A[i]] = B[i];
  }
  
  // Initialize Union-Find and prepare leftmost harbour indices
  for (i = 1; i <= n; i++)
    fa[i] = i;
    
  for (i = 1; i <= n; i++) {
    l[i] = V[i - 1] ? i - 1 : l[i - 1]; // leftmost harbour to the left of i
    if (V[i] == 0)
      fa[i] = i + 1;
    else
      add(i, 1ll * V[l[i]] * (i - l[i]) * (i - l[i] - 1) / 2);
  }
  
  // Process queries in reverse order (as per original logic)
  for (k = q; k; k--)
    if (op[k] == 1) { // type 1 query: remove harbour
      i = A[k];     // i is the point where we're removing harbour
      j = p(i + 1); // find next active position
      add(i, -1ll * V[l[i]] * (i - l[i]) * (i - l[i] - 1) / 2);
      add(j, -1ll * V[l[j]] * (j - l[j]) * (j - l[j] - 1) / 2);
      V[i] = 0;  // Mark as no harbour
      fa[i] = i + 1;
      l[j] = l[i]; // merge left indices
      add(j, 1ll * V[l[j]] * (j - l[j]) * (j - l[j] - 1) / 2);
    } else { // type 2 query: compute total cost
      L = A[k];
      R = B[k];
      i = p(L);                // rightmost active point starting from L
      j = l[p(R)];             // leftmost harbour before or at R
      if (i > j)
        Ans[k] =
            1ll * V[j] *
            (1ll * (i - L) * (i - L + 1) / 2 - 1ll * (i - R) * (i - R - 1) / 2);
      else {
        Ans[k] = sum(j) - sum(i);                 // range difference in BIT
        Ans[k] += 1ll * V[l[i]] * (i - L) * (i - L + 1) / 2; // prefix cost at i
        i = p(R);
        Ans[k] +=
            1ll * V[j] *
            (1ll * (i - j) * (i - j - 1) / 2 - 1ll * (i - R) * (i - R - 1) / 2); // suffix cost
      }
    }
    
  // Output answers for type-2 queries
  for (k = 1; k <= q; k++)
    if (op[k] == 2)
      printf("%lld\n", Ans[k]);
}


// https://github.com/VaHiX/codeForces/