// Problem: CF 2107 F2 - Cycling (Hard Version)
// https://codeforces.com/contest/2107/problem/F2

/*
F2. Cycling (Hard Version)
Algorithms/Techniques: Convex Hull Trick (CHT), Segment Tree with Dynamic Updates
Time Complexity: O(n log n) per test case
Space Complexity: O(n) 

This problem involves finding the minimum cost for Leo to get ahead of the first cyclist 
by performing a series of swaps and moves. The solution uses dynamic programming with a 
Convex Hull Trick (CHT) approach on a segment tree to efficiently maintain and query 
optimal linear functions.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <utility>

#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn = 1e6 + 5;
int n;
int a[maxn], dp[maxn], ans[maxn];

// Structure to represent a line: k * x + b
struct line {
  int k, b;
  int f(int x) { return k * x + b; }
} tree[maxn << 2];

// Fast input function
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = ch == '-' ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}

// Build the segment tree with default line
void build(int l, int r, int rt) {
  tree[rt] = {0, inf};
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(l, mid, ls);
  build(mid + 1, r, rs);
}

// Update the segment tree with a new line
void upd(line ln, int l = 1, int r = n, int rt = 1) {
  int lp = tree[rt].f(l), rp = tree[rt].f(r);
  int lq = ln.f(l), rq = ln.f(r);
  if (lq <= lp && rq <= rp)
    tree[rt] = ln;
  else if (lq < lp || rq < rp) {
    int mid = (l + r) >> 1;
    if (ln.f(mid) < tree[rt].f(mid))
      swap(ln, tree[rt]);
    if (ln.f(l) < tree[rt].f(l))
      upd(ln, l, mid, ls);
    else
      upd(ln, mid + 1, r, rs);
  }
}

// Query the minimum value of a line at a given point
int que(int pos, int l = 1, int r = n, int rt = 1) {
  int res = tree[rt].f(pos);
  if (l == r)
    return res;
  int mid = (l + r) >> 1;
  if (pos <= mid)
    res = min(res, que(pos, l, mid, ls));
  else
    res = min(res, que(pos, mid + 1, r, rs));
  return res;
}

// Solve the problem for a given input array
void solve() {
  n = read();
  build(1, n, 1);
  stack<int> stk;
  stk.push(0);
  for (int i = 1, j; i <= n; i++) {
    a[i] = read();
    // Maintain monotonicity in stack
    while (a[j = stk.top()] > a[i])
      stk.pop();
    // Compute dp based on previous state and current element
    dp[i] = ans[j] + i - j - 1 + (i - j) * a[i];
    // Update the segment tree with new line
    upd({a[i] + 2, dp[i] - (a[i] + 2) * i});
    // Query the minimum cost to reach current position
    ans[i] = que(i), stk.push(i);
  }
  for (int i = 1; i <= n; i++)
    printf("%lld ", ans[i]);
  putchar('\n');
}

signed main() {
  int t = read();
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/