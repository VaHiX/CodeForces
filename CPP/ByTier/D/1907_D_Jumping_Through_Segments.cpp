// Problem: CF 1907 D - Jumping Through Segments
// https://codeforces.com/contest/1907/problem/D

/*
Algorithm: Binary search on the answer + greedy validation
Time Complexity: O(n * log(max_range)) where max_range <= 1e9
Space Complexity: O(n) for storing segments

The problem asks to find the minimum jump distance k such that a player can move
through n segments starting from 0, where each move must land within the
corresponding segment and the player can jump at most k distance.

Approach:
1. Binary search on k (the jump distance)
2. For a given k, check if it's possible to complete the level (validate
function)
3. In validation:
   - Start at 0
   - For each segment, compute the valid range of positions where we can start
the move
   - This range is [max(l_i, prev_pos - k), min(r_i, prev_pos + k)]
   - If at any point the valid range becomes empty, return false
   - If we can traverse all segments, return true

Key optimization:
- Instead of simulating moves, we can validate greedily by tracking the overlap
  of valid ranges across segments
*/

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

namespace Fread {
const int SIZE = 1 << 16;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 16;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite

void solve();
int main() {
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> g(n);
  for (int x = 0; x < n; x++)
    cin >> g[x].first >> g[x].second;
  auto chk = [&](int mi) {
    int l = 0, r = 0;
    for (int x = 0; x < n; x++) {
      l = max(g[x].first, l - mi);  // Update lower bound for current segment
      r = min(g[x].second, r + mi); // Update upper bound for current segment
      if (r < g[x].first || g[x].second < l) // No valid range for segment
        return false;
    }
    return true;
  };
  int l = 0, r = 1e9, ans = r;
  while (l <= r) {
    int mi = (l + r) / 2;
    if (chk(mi))
      ans = mi, r = mi - 1; // Valid k, try smaller
    else
      l = mi + 1; // Invalid k, try larger
  }
  cout << ans << endl;
}

// https://github.com/VaHiX/CodeForces/