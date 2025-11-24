// Problem: CF 1797 E - Li Hua and Array
// https://codeforces.com/contest/1797/problem/E

/*
 * Problem: Li Hua and Array
 * Algorithm: Segment Tree with Euler's Totient Function
 * 
 * Time Complexity: O(n * log(n) + m * log(n) * log(max_a))
 * Space Complexity: O(n + max_a)
 *
 * The solution uses a segment tree to efficiently handle two types of operations:
 * 1. Update a range: transform each element in the range using φ(x)
 * 2. Query a range: find minimum number of operations to make all elements equal in the range
 * 
 * Euler's Totient Function φ(x) is precomputed using sieve of Eratosthenes.
 * For each query, we calculate how many steps it takes for values in the segment to reduce to 1.
 * The segment tree maintains for each node:
 * - val: total operations needed to make all elements 1
 * - e: current value of the segment (used for comparison during merge)
 * - flag: whether all elements are 1 (reduced)
 * - len: number of elements in the range
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 100005;
const int N2 = 5000005;
bool np[N2];
int tot, prime[N2], phi[N2];
void sieve(int n) {
  np[1] = true;
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!np[i]) {
      prime[tot++] = i;
      phi[i] = i - 1;
    }
    for (int j = 0, k; (k = i * prime[j]) <= n; j++) {
      np[k] = true;
      if (i % prime[j] == 0) {
        phi[k] = phi[i] * prime[j];
        break;
      }
      phi[k] = phi[i] * (prime[j] - 1);
    }
  }
}
int a[N];
struct Node {
  int val, e, flag, len;
} tr[N << 2];
void push_up(Node &u, const Node &lson, const Node &rson) {
  u.len = lson.len + rson.len;
  u.flag = lson.flag && rson.flag;
  u.val = lson.val + rson.val;
  int x = lson.e, y = rson.e;
  while (x != y) {
    if (x > y) {
      x = phi[x];
      u.val += lson.len;
    } else {
      y = phi[y];
      u.val += rson.len;
    }
  }
  u.e = x;
}
void build(int u, int l, int r) {
  if (l == r) {
    tr[u] = {0, a[l], a[l] == 1, 1};
    return;
  }
  int mid = l + r >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  push_up(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void update(int u, int l, int r, int x, int y) {
  if (tr[u].flag)
    return;
  if (l == r) {
    tr[u].e = phi[tr[u].e];
    tr[u].flag = tr[u].e == 1;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid)
    update(u << 1, l, mid, x, y);
  if (y > mid)
    update(u << 1 | 1, mid + 1, r, x, y);
  push_up(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
Node query(int u, int l, int r, int x, int y) {
  if (x <= l && r <= y)
    return tr[u];
  int mid = l + r >> 1;
  if (x > mid)
    return query(u << 1 | 1, mid + 1, r, x, y);
  if (y <= mid)
    return query(u << 1, l, mid, x, y);
  Node res;
  push_up(res, query(u << 1, l, mid, x, y),
          query(u << 1 | 1, mid + 1, r, x, y));
  return res;
}
int main() {
  sieve(5e6);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  build(1, 1, n);
  while (m--) {
    int op, l, r;
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      update(1, 1, n, l, r);
    } else {
      printf("%d\n", query(1, 1, n, l, r).val);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/