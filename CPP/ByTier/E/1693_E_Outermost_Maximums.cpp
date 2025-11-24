// Problem: CF 1693 E - Outermost Maximums
// https://codeforces.com/contest/1693/problem/E

/*
Algorithm: Range Query and Segment Tree (Fenwick Tree) based approach to count inversions or operations needed.
Time Complexity: O(n log n) due to sorting and Fenwick Tree operations.
Space Complexity: O(n) for storing the array and Fenwick Tree.

The problem involves minimizing the number of operations to reduce all elements in an array to zero,
where each operation reduces either the leftmost or rightmost maximum element to the maximum of elements on its left or right respectively.

This solution uses a Fenwick Tree (Binary Indexed Tree) to efficiently count how many elements are in a range.
It processes elements from the largest to smallest, updates the tree, and counts how many elements are in a specific range.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define F first
#define S second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pr;
inline LL rd() {
  LL x = 0, y = 1;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    if (c == '-')
      y = -1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return x * y;
}
const LL N = 200005;
LL n, m, t[N];
vector<LL> vc[N];
void add(LL x, LL y) {
  for (; x <= n; x += x & -x)  // Update Fenwick Tree
    t[x] += y;
}
LL qr(LL x) {
  LL y = 0;
  for (; x; x -= x & -x)  // Query Fenwick Tree
    y += t[x];
  return y;
}
int main() {
  n = rd();
  for (LL i = 1; i <= n; ++i)
    vc[rd()].push_back(i);  // Group indices by value
  LL L = 1, R = n;
  for (LL i = n; i; --i)
    if (vc[i].size()) {
      for (auto j : vc[i])
        add(j, 1);  // Update the Fenwick Tree with current index
      LL l = min(R + 1, vc[i][0]), r = max(L - 1, vc[i].back());
      m += qr(r) - qr(l - 1);  // Count of elements in [l, r] using Fenwick Tree
      L = l;
      R = r;
    }
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/