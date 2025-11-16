// Problem: CF 920 F - SUM and REPLACE
// https://codeforces.com/contest/920/problem/F

/*
 * Problem: F. SUM and REPLACE
 * 
 * Algorithm/Techniques:
 *   - Number theory: Preprocessing divisor count using sieve
 *   - Segment tree with lazy propagation optimization:
 *     - Build segment tree to support range sum queries
 *     - Use max value in segment tree node to optimize update operations
 *     - Only perform updates when max value > 2 (since D(x) <= x, and D(x) = 1 only for x = 1)
 * 
 * Time Complexity:
 *   - Preprocessing divisor count: O(10^6)
 *   - Building segment tree: O(n)
 *   - Each query (REPLACE/SUM): O(log n)
 *   - Total: O(10^6 + n log n + m log n)
 * 
 * Space Complexity:
 *   - D array: O(10^6)
 *   - Segment tree: O(4 * n)
 *   - Total: O(10^6 + n)
 */

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define dn 1000100
#define N 100100
#define inf 100000000
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pff(n, m) printf("%d %d\n", n, m)
#define pffl(n, m) printf("%I64d %I64d\n", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int D[dn], arr[3 * N];
ll tree[12 * N], mx[12 * N];

// Precompute the number of divisors for each number up to 10^6
void div() {
  memset(D, 0, sizeof(D));
  for (int i = 1; i < dn; i++) {
    for (int j = i; j < dn; j += i)
      D[j]++;
  }
}

// Build segment tree with initial values from array
void build(int at, int L, int R) {
  if (L == R) {
    tree[at] = (ll)arr[L];
    mx[at] = (ll)arr[L];
    return;
  }
  int mid = (L + R) / 2;
  build(at * 2, L, mid);
  build(at * 2 + 1, mid + 1, R);
  tree[at] = tree[at * 2] + tree[at * 2 + 1];
  mx[at] = max(tree[at * 2], tree[at * 2 + 1]);
}

// Query sum in range [l,r]
ll query(int at, int L, int R, int l, int r) {
  if (r < L || R < l)
    return 0;
  if (l <= L && R <= r)
    return tree[at];
  int mid = (L + R) / 2;
  return query(at * 2, L, mid, l, r) + query(at * 2 + 1, mid + 1, R, l, r);
}

// Update function to replace values with their divisor count in range [l,r]
void update(int at, int L, int R, int l, int r) {
  if (r < L || R < l)
    return;
  // Early termination if the maximum value in range is <= 2
  if (mx[at] <= 2)
    return;
  if (l <= L && R <= r && L == R) {
    // Replace value with number of divisors
    tree[at] = mx[at] = D[mx[at]];
    return;
  }
  int mid = (L + R) / 2;
  update(at * 2, L, mid, l, r);
  update(at * 2 + 1, mid + 1, R, l, r);
  tree[at] = tree[at * 2] + tree[at * 2 + 1];
  mx[at] = max(mx[at * 2], mx[at * 2 + 1]);
}

int main() {
  int i, j, k;
  int n, m;
  int t, l, r;
  div();
  sff(n, m);
  for (i = 1; i <= n; i++)
    sf(arr[i]);
  build(1, 1, n);
  while (m--) {
    sf(t);
    sff(l, r);
    if (t == 1)
      update(1, 1, n, l, r);
    else
      pfl(query(1, 1, n, l, r)), pfs("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/