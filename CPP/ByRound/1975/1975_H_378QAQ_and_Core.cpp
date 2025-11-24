// Problem: CF 1975 H - 378QAQ and Core
// https://codeforces.com/contest/1975/problem/H

/*
H. 378QAQ and Core
Problem: Rearrange a string to minimize the lexicographically smallest core.
Algorithm: Greedy + Simulation with clever indexing.
Time Complexity: O(n) amortized per test case, where n is the length of string s.
Space Complexity: O(n), for storing the string and auxiliary arrays.

Approach:
- The key insight is to minimize the core by ensuring that the largest characters appear as late as possible, so they do not dominate early in the string.
- We use a greedy strategy with a "val" array to track character placement order.
- The algorithm simulates how a minimal lexicographic core can be formed by rearranging characters optimally.

*/

#include <stdio.h>
#include <algorithm>
#include <numeric>

using namespace std;
template <typename Tp> void chmin(Tp &x, const Tp &y) { x = min(x, y); }
template <typename Tp> void chmax(Tp &x, const Tp &y) { x = max(x, y); }
using dbl = double;
using ll = long long;
using ldb = long double;
void init() {}
constexpr int MAX_N = 1e6 + 20;
constexpr int SIGMA = 26;
int n, cnt[SIGMA];
char s[MAX_N], sans[MAX_N];
int idcnt, nxt[MAX_N], val[MAX_N], btm[MAX_N];

void solve() {
  scanf("%d%s", &n, s + 1);
  fill(cnt, cnt + SIGMA, 0);
  for (int i = 1; i <= n; ++i) {
    ++cnt[s[i] - 'a'];
  }
  fill(nxt, nxt + n + 1, 0);
  fill(val + 1, val + n + 1, -2);
  idcnt = n;
  val[0] = -1;
  for (int i = 1, j = 0; i <= n; ++i) {
    while (!cnt[j])
      ++j;
    s[i] = j + 'a';  // Fill string with characters in ascending order
    val[i] = j;
    --cnt[j];
  }
  int p = n;
  iota(btm, btm + n + 1, 0);  // Initialize btm to identity mapping
  for (int i = 0, j = 0; i < n; ++i) {
    if (p == n) {  // If we're at the end of a section, update j to next unique character.
      while (p > i + 1 && val[p] == val[p - 1])
        --p;
      j = p;
    } else {
      ++p;
    }
    nxt[btm[p]] = i;  // Link btm[p] to current index
    btm[p] = btm[i];  // Update btm array for next step
    val[p] = idcnt += j == p || val[i - 1] != val[i];  // Assign new value to control merging logic
  }
  for (int i = 1;; ++i) {
    sans[i] = s[p];  // Build result from the chain
    if (!p)
      break;
    p = nxt[p];
  }
  printf("%s\n", sans + 1);
}

int main() {
  int t = 1;
  init();
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/