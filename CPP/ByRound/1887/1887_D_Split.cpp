// Problem: CF 1887 D - Split
// https://codeforces.com/contest/1887/problem/D

/*
Algorithm: Preprocessing with stack, sparse table, and BIT for range queries
Time Complexity: O(n log n + q log n)
Space Complexity: O(n log n + q)

The problem is to check if a subarray can be split into two parts such that all elements in the left part are strictly smaller than all elements in the right part.

Approach:
1. For each element, find the next greater element (nxt[i]) and previous greater element (lst[i]) using stack.
2. Use sparse table (ST) for range minimum queries to efficiently check if any element in a range is greater than a certain value.
3. For each query, process events using a BIT to maintain number of valid splits in range.
*/

#include <string.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
const int N = 3e5 + 7, L = 19;
int n, a[N];
int nxt[N], lst[N]; // nxt[i] = next greater element index, lst[i] = previous greater element index
int st[L + 1][N], lg[N], r[N]; // sparse table for range min queries and auxiliary array r
bool ans[N]; // store answers for each query
vector<int> e[N]; // events for BIT update
vector<array<int, 2>> p[N]; // queries for processing at position i
template <class T> struct BIT {
  int n;
  vector<T> bit;
  void init(int sz) { bit.resize(n = sz + 7); }
  void upd(int i, T x) {
    for (i++; i < n; i += i & -i) // update in BIT
      bit[i] += x;
  }
  T query(int i) {
    T ret = 0;
    for (i++; i > 0; i -= i & -i) // query in BIT
      ret += bit[i];
    return ret;
  }
  T query(int l, int r) { return query(r) - query(l - 1); }; // range query
};
int query(int l, int r) {
  int i = lg[r - l + 1]; // find lg for sparse table
  return min(st[i][l], st[i][r - (1 << i) + 1]);
}
int main() {
  cin.tie(0)->sync_with_stdio(false);
  lg[1] = 0;
  for (int i = 2; i < N; i++)
    lg[i] = lg[i / 2] + 1; // precompute logarithms
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    nxt[i] = n + 1; // initialize next greater element
  }
  stack<int> s;
  // Find next greater element for each index using stack
  for (int i = 1; i <= n; i++) {
    while (s.size() && a[i] > a[s.top()]) {
      nxt[s.top()] = i;
      s.pop();
    }
    s.push(i);
  }
  while (s.size())
    s.pop();
  // Find previous greater element for each index using stack
  for (int i = n; i >= 1; i--) {
    while (s.size() && a[i] > a[s.top()]) {
      lst[s.top()] = i;
      s.pop();
    }
    s.push(i);
  }
  // Build sparse table for range minimum queries
  memset(st, 0x3f, sizeof(st));
  for (int i = 1; i <= n; i++)
    st[0][i] = a[i];
  for (int i = 1; i <= L; i++)
    for (int j = 0; j + (1 << i) < N; j++)
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
  // Process valid splits
  for (int i = 1; i <= n; i++) {
    int lo = nxt[i], hi = n;
    while (lo < hi) {
      int mid = (lo + hi + 1) / 2;
      if (query(nxt[i], mid) > a[i]) // check if all elements in range are greater than a[i]
        lo = mid;
      else
        hi = mid - 1;
    }
    if (nxt[i] <= n) {
      r[i] = lo;
      e[lst[i] + 1].push_back(i); // mark event for BIT update
    }
  }
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
    int l, r;
    cin >> l >> r;
    p[l].push_back({r, i}); // store queries grouped by left boundary
  }
  BIT<int> bit;
  bit.init(n + 2);
  for (int i = 1; i <= n; i++) {
    // Process events at position i
    for (int j : e[i]) {
      bit.upd(nxt[j], 1);
      bit.upd(r[j] + 1, -1);
    }
    // Process queries at position i
    for (auto &[r, j] : p[i])
      ans[j] = bit.query(1, r);
    if (nxt[i] <= n) {
      bit.upd(nxt[i], -1); // undo previous update
      bit.upd(r[i] + 1, 1); // update with new range
    }
  }
  for (int i = 1; i <= q; i++)
    cout << (ans[i] ? "Yes" : "No") << '\n'; // output answers
  return 0;
}


// https://github.com/VaHiX/CodeForces/