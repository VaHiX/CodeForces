// Problem: CF 1881 E - Block Sequence
// https://codeforces.com/contest/1881/problem/E

/*
 * Problem: E. Block Sequence
 * Algorithm: Dynamic Programming with Reverse Iteration
 * 
 * Approach:
 * - A beautiful sequence is made of blocks, where each block starts with its length,
 *   followed by that many elements.
 * - We use dynamic programming to find the minimum number of deletions required.
 * - Let f[i] represent the minimum deletions needed to make the suffix starting at index i beautiful.
 * - For each position i, if a[i] is the length of a block, we check the next block starting at i + a[i] + 1.
 * - The recurrence is:
 *   - If i + a[i] < n: f[i] = min(f[i + a[i] + 1], f[i + 1] + 1)
 *   - Else: f[i] = f[i + 1] + 1
 * - The base case is initialized such that f[n] = 0.
 * 
 * Time Complexity: O(n) - Each element is processed once in the loop.
 * Space Complexity: O(n) - Extra space for the DP array f.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#define all(x) x.begin(), x.end()
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++);
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline long long read() {
  long long x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - 48;
    ch = getchar();
  }
  return x * f;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  int n = v.size();
  for (int i = 0; i < n; ++i)
    os << v[i] << ' ';
  return os;
}
using namespace std;
using i64 = long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = read();
  while (T--) {
    int n = read();
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      a[i] = read();
    }
    vector<int> f(n + 1);
    iota(f.rbegin(), f.rend(), 0);  // Initialize f[n] = 0, f[n-1] = 1, ..., f[1] = n-1, f[0] = n
    for (int i = n - 1; ~i; --i) {   // Iterate backwards from n-1 to 0
      if (i + a[i] < n) {
        // If there are enough elements to form a valid block after this one
        f[i] = min(f[i + a[i] + 1], f[i + 1] + 1);
      } else {
        // If extending the block goes beyond the array, delete current element
        f[i] = f[i + 1] + 1;
      }
    }
    cout << f[0] << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/