// Problem: CF 2146 E - Yet Another MEX Problem
// https://codeforces.com/contest/2146/problem/E

/*
E. Yet Another MEX Problem
Algorithms/Techniques: Segment Tree with Lazy Propagation, MEX calculation, Prefix-based maximum weight tracking.

Time Complexity: O(n log n) per test case due to segment tree operations.
Space Complexity: O(n) for the segment tree and auxiliary arrays.

This code solves the problem of finding the maximum weight of subarrays ending at each index,
where the weight is defined as the count of elements greater than the MEX of the subarray.
We use a segment tree with lazy propagation to efficiently maintain and query:
1. The maximum weight up to a certain point (maintained via modification operations).
2. Dynamic updates on element values in the current subarrays.
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 3e5 + 9, K = 20, M = 998244353;
#define ls (u << 1)
#define rs (u << 1 | 1)
int mx[N << 2], add[N << 2]; // Segment tree storage for max value and lazy updates

// Push up operation to update parent node with max of children
void pushup(int u) { mx[u] = max(mx[ls], mx[rs]); }

// Push down operation to propagate lazy updates
void pushdown(int u) {
  if (add[u]) {
    mx[ls] += add[u], mx[rs] += add[u];
    add[ls] += add[u], add[rs] += add[u];
    add[u] = 0;
  }
}

// Build the segment tree
void build(int u, int l, int r) {
  mx[u] = add[u] = 0;
  if (l < r) {
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
  }
}

// Range increment modification for segment tree
void modify(int u, int l, int r, int tagl, int tagr, int v) {
  if (tagl > tagr)
    return;
  if (l >= tagl && r <= tagr) {
    add[u] += v, mx[u] += v;
    return;
  }
  pushdown(u);
  int mid = (l + r) >> 1;
  if (mid >= tagl)
    modify(ls, l, mid, tagl, tagr, v);
  if (mid < tagr)
    modify(rs, mid + 1, r, tagl, tagr, v);
  pushup(u);
}

// Set the value at a specific position to zero
void modify1(int u, int l, int r, int pos) {
  if (l == r)
    mx[u] = 0;
  else {
    pushdown(u);
    int mid = (l + r) >> 1;
    if (mid >= pos)
      modify1(ls, l, mid, pos);
    else
      modify1(rs, mid + 1, r, pos);
    pushup(u);
  }
}

// Main solution logic for one test case
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    a[i]++; // Shift elements to match index requirements (so that elements are 1-based)
  }
  build(1, 1, n + 1); // Initialize the segment tree with size n+1
  for (int i = 1; i <= n; ++i) {
    modify(1, 1, n + 1, 1, a[i] - 1, 1); // Increment all positions from 1 to a[i]-1 by 1
    modify1(1, 1, n + 1, a[i]); // Reset position a[i] to 0 (to simulate MEX tracking)
    cout << mx[1] << " \n"[i == n]; // Output max value stored at root
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/