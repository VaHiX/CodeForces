// Problem: CF 2103 E - Keep the Sum
// https://codeforces.com/contest/2103/problem/E

/*
E. Keep the Sum
time limit per test2.5 seconds
memory limit per test256 megabytes

Problem Description:
Given an array of integers and a target sum k, determine if it's possible to transform the array into non-decreasing order using a specific operation. The operation selects two indices i,j such that a[i] + a[j] = k; then performs a transfer of value x from index i to j (with constraints on x). 

Algorithms/Techniques:
- Two-pointer technique to find valid pairs with sum equal to k
- Sorting indices based on values in array
- Simulated movement of elements towards forming a non-decreasing sequence
- Operation simulation using cycle decomposition

Time Complexity: O(n log n) per test case, due to sorting and operations. In worst-case scenario for sorting and processing the elements.
Space Complexity: O(n) for storing arrays and auxiliary data structures.

*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
namespace qG {
const int sz = 1 << 17;
char buf[sz], *S, *T;
inline char g() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, sz, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct R {
  R &operator>>(int &x) {
    x = 0;
    char c = g();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = g();
    return *this;
  }
} r;
} // namespace qG
namespace qP {
const int sz = 1 << 20;
char buf[sz], *S = buf, *T = buf + sz;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void p(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct W {
  W &operator<<(int x) {
    if (!x) {
      p('0');
      return *this;
    }
    if (x < 0) {
      p('-');
      x = -x;
    }
    static int s[11];
    int tp = 0;
    while (x) {
      s[tp++] = x % 10;
      x /= 10;
    }
    while (tp)
      p('0' + s[--tp]);
    return *this;
  }
  W &operator<<(char c) {
    p(c);
    return *this;
  }
} w;
struct E {
  ~E() { flush(); }
} e;
} // namespace qP
#define cin qG::r
#define cout qP::w
#define rsz resize
#define vi vector<int>
#define a3 array<int, 3>
#define all(x) begin(x), end(x)
using namespace std;
int main() {
  int T, n, m;
  cin >> T;
  vi a, q;
  vector<a3> ans(6e5);
  while (T--) {
    cin >> n >> m;
    a.rsz(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    if (is_sorted(all(a))) { // If already sorted, no operations needed
      cout << 0 << '\n';
      continue;
    }
    q.rsz(n + 1);
    iota(all(q), 0); // Fill q with 0,1,...,n
    sort(begin(q) + 1, end(q), [&](int &x, int &y) { return a[x] < a[y]; }); // Sort indices based on values in array a
    
    int x = 1, y = n; // two pointers for finding sum equal to m
    while (x < y) {
      int d = a[q[x]] + a[q[y]] - m;
      if (!d)
        break; // Found pair with sum = m
      if (d > 0)
        y--;
      else
        x++;
    }
    if (x == y) { // No such pair exists, impossible to make array non-decreasing
      cout << -1 << '\n';
      continue;
    }
    
    int L = q[x], R = q[y];
    if (L > R) { // Make sure L <= R
      swap(L, R);
      swap(x, y);
    }

    vi v;
    for (int i = 1; i <= n; i++)
      if (q[i] == 1 || q[i] == n) {
        if (q[i] == 1)
          v.insert(v.begin(), i); // Insert at start
        else
          v.push_back(i); // Append to end
        if (v.size() == 2)
          break;
      }
    int tt = 0;
    auto mv = [&](int l, int r, int x) { // Transfer 'x' from index l to r
      x -= a[r];
      if (!x)
        return;
      a[l] -= x;
      a[r] += x;
      ans[tt++] = {l, r, x};
    };
    if (L ^ 1) { // If L is not at position 1
      q[v[0]] = q[x];
      mv(R, L, a[1]);
    }
    if (R ^ n) { // If R is not at position n
      q[v[1]] = q[y];
      mv(1, R, a[n]);
    }

    if (x > y)
      swap(x, y);
    while (x > 1) {
      q[x] = q[x - 1];
      x--;
    }
    while (y < n) {
      q[y] = q[y + 1];
      y++;
    }

    v.rsz(n);
    for (int i = 2; i < n; ++i)
      if (!v[i]) {
        v[i] = 1;
        for (int j = i, k = q[i]; !v[k]; j = k, k = q[k]) { /* Cycle decomposition */
          mv(1, n, a[j]);
          mv(1, j, a[k]);
          mv(1, k, a[n]);
          v[k] = 1;
        }
      }
    mv(1, n, m); // Final operation to set all elements to target sum m
    cout << tt << '\n';
    for (int i = 0; i < tt; i++) {
      auto &c = ans[i];
      cout << c[0] << ' ' << c[1] << ' ' << c[2] << '\n';
    }
  }
}


// https://github.com/VaHiX/codeForces/