// Problem: CF 1771 F - Hossam and Range Minimum Query
// https://codeforces.com/contest/1771/problem/F

/*
Algorithm: Persistent Segment Tree with Coordinate Compression
Time Complexity: O(n * log n + q * log n)
Space Complexity: O(n * log n)

This code handles range minimum queries where we need to find the smallest number 
that appears an odd number of times in a given range. It uses a persistent segment 
tree with coordinate compression to efficiently track the parity of elements.

The persistent segment tree is built on top of the compressed coordinates of the 
elements in the array. Each node stores a bitmask representing the parity of elements 
in that segment. The XOR operation helps track odd/even occurrences.
*/

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
const int N = 2e5 + 5;
int n, q, cnt;
int a[N], rt[N], hsh[N];
vector<int> in;
struct node {
  int l, r, v;
} t[N * 20];
void update(int l, int r, int &i, int x, int v, int k) {
  i = ++cnt; // Increment count for new node
  t[i] = t[k]; // Copy parent node
  t[i].v ^= v; // XOR with new value (toggle parity)
  if (l == r)
    return; // Base case: leaf node
  int m = (l + r) / 2;
  if (x <= m)
    update(l, m, t[i].l, x, v, t[k].l); // Go left
  else
    update(m + 1, r, t[i].r, x, v, t[k].r); // Go right
}
int query(int l, int r, int x, int y) {
  if (t[x].v == t[y].v) // If parity is same, no odd count elements
    return 0;
  if (l == r) // Reached leaf node, return coordinate
    return l;
  int m = (l + r) / 2;
  int res = query(l, m, t[x].l, t[y].l); // Check left subtree
  if (res)
    return res;
  return query(m + 1, r, t[x].r, t[y].r); // Check right subtree
}
mt19937 rng(time(0));
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  in.push_back(0); // Add dummy element for coordinate compression
  for (int i = 1; i <= n; i++)
    cin >> a[i], in.push_back(a[i]);
  sort(in.begin(), in.end()); // Sort for coordinate compression
  for (int i = 1; i <= n; i++)
    a[i] = lower_bound(in.begin(), in.end(), a[i]) - in.begin(); // Compress coordinates
  for (int i = 1; i <= n; i++)
    hsh[i] = rng(); // Random hash values for XOR tracking
  for (int i = 1; i <= n; i++)
    update(1, n, rt[i], a[i], hsh[a[i]], rt[i - 1]); // Build persistent segment tree
  cin >> q;
  int ans = 0;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l ^= ans; // Decode query parameters
    r ^= ans;
    ans = in[query(1, n, rt[l - 1], rt[r])]; // Query and decode result
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/