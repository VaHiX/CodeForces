// Problem: CF 1912 G - Great City Saint Petersburg
// https://codeforces.com/contest/1912/problem/G

/*
 * Problem: Saint Petersburg Rainwater Accumulation
 * 
 * Purpose: Compute the amount of rainwater that accumulates on a street with varying heights,
 *          considering updates to the street heights over time. The street is modeled as a
 *          1D array of heights where water collects based on the "valleys" formed.
 *
 * Algorithms/Techniques:
 * - Segment Tree with Lazy Propagation to efficiently handle range updates and queries
 * - Two-pass algorithm to precompute water level, and dynamic updates for each construction event
 * 
 * Time Complexity: O(n log n + q log n) where n is number of sections and q is number of updates
 * Space Complexity: O(n) for the segment tree storage
 */

#include <stdint.h>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;
constexpr int N = 2e5 + 2, S = 1 << 18;
array<int, 2> t[N + S]; // Segment tree with lazy propagation
int64_t s, n, q; // s: total accumulated water, n: number of sections, q: number of updates

// Function to get maximum height from left/right side
template <int dir> int mx(int r) {
  r += S;
  int res = -1e9;
  while (r > 7) {
    if (r & 1 ^ !!~dir)
      res = max(res, t[r + dir][0]);
    res += t[r /= 2][1];
  }
  while (r != (~dir ? 7 : 4))
    res = max(res, t[r += dir][0]);
  return res;
}

// Function to find index of height x from left/right
template <int dir> int find(int x) {
  x = mx<dir - !dir>(x);
  int i = dir ? 7 : 4;
  while (i != (dir ? 3 : 8) && t[i][0] <= x)
    i += !dir ?: -1;
  if (i == (dir ? 3 : 8))
    return dir ? -1 : n;
  while (i < S)
    x -= t[i][1], i = 2 * i + (dir ? t[2 * i + 1][0] > x : t[2 * i][0] <= x);
  return i - S;
}

// Function to update range [l, r) in segment tree
void inc(int l, int r) {
  l += S - 1, r += S;
  while (1) {
    if (r > l + 1) {
      if (~l & 1)
        ++t[l + 1][0], ++t[l + 1][1];
      if (r & 1)
        ++t[r - 1][0], ++t[r - 1][1];
    }
    if (l <= 7)
      break;
    l /= 2, r /= 2;
    t[l][0] = max(t[2 * l][0], t[2 * l + 1][0]) + t[l][1];
    t[r][0] = max(t[2 * r][0], t[2 * r + 1][0]) + t[r][1];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> t[i + S][0];
  n += 2;
  for (int i = 0, mx = 0; ++i < n;)
    s += mx = max(mx, t[i + S][0]), s -= t[i + S][0];
  for (int i = n, mx = 0; i--;)
    s += mx = max(mx, t[i + S][0]);
  for (int i = S + n; --i;)
    t[i / 2][0] = max(t[i / 2][0], t[i][0]);
  while (cout << s - max_element(t + 4, t + 8)[0][0] * n << '\n', q--) {
    int l, r;
    cin >> l >> r;
    s += find<0>(r + 1) - find<1>(l - 1) + l - 1;
    inc(l, r + 1);
    s -= find<0>(l) - find<1>(r) + r;
  }
}


// https://github.com/VaHiX/CodeForces/