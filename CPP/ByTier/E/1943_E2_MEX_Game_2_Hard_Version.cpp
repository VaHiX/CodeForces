// Problem: CF 1943 E2 - MEX Game 2 (Hard Version)
// https://codeforces.com/contest/1943/problem/E2

/*
 * Problem: E2. MEX Game 2 (Hard Version)
 * Purpose: Determine the maximum MEX (minimum excludant) Alice can achieve when playing optimally against Bob,
 *          given that:
 *          - Alice picks 1 element per turn, Bob picks up to k elements per turn.
 *          - Array a is given in compressed format with frequencies.
 *          - Alice starts first.
 *          - Both players play optimally.
 * 
 * Algorithms/Techniques:
 * - Binary search on the answer (MEX).
 * - Dynamic programming to precompute optimal Bob moves.
 * - Greedy approach in checking if a certain MEX is achievable.
 * 
 * Time Complexity: O(m * log(m)) per test case, where m = max element in the array
 * Space Complexity: O(m) per test case
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch - '0');
    ch = getchar();
  }
  return x;
}
void print(cint x) {
  if (x < 10) {
    putchar(x + '0');
    return;
  }
  print(x / 10);
  putchar(x % 10 + '0');
}
void princh(cint x, const char ch) {
  print(x);
  putchar(ch);
}
int n, k;
int a[200001], idx[200001], p[200001];
vector<int> f;
ll s[200001], dp[200001];
inline ll sum(cint l, cint r) {
  if (l == 0)
    return s[r];
  return s[r] - s[l - 1];
}
bool check(cint x) {
  f.clear();
  for (int i = 0; i <= n; ++i) {
    if (idx[i] <= x)
      f.push_back(a[idx[i]]);
  }
  s[0] = f[0];
  for (int i = 1; i <= x; ++i) {
    s[i] = s[i - 1] + f[i];
  }
  p[0] = 1;
  for (int i = 1; i <= x; ++i) {
    p[i] = p[i - 1];
    // This while loop adjusts `p[i]` to maintain the constraint that
    // the total moves used by Bob up to position i satisfies the game logic
    while (sum(p[i], i) - 1ll * f[p[i]] * (i - p[i] + 1) > 1ll * p[i] * k)
      ++p[i];
    // Check if current choice of p[i] makes it impossible for Alice to complete her turn
    if (sum(p[i], i) - 1ll * p[i] * k <= dp[i - p[i] + 1])
      return 0;
  }
  return 1;
}
bool cmp_idx(cint x, cint y) { return a[x] < a[y]; }
int find(cint l, cint r) {
  cint mid = l + r + 1 >> 1;
  if (l >= r)
    return mid;
  if (check(mid))
    return find(mid, r);
  return find(l, mid - 1);
}
void solve() {
  n = read();
  k = read();
  for (int i = 0; i <= n; ++i) {
    a[i] = read();
    idx[i] = i;
  }
  sort(idx, idx + n + 1, cmp_idx);
  dp[1] = 0;
  // Precompute dp values representing minimum moves for Bob to secure enough elements
  // to prevent Alice from achieving higher MEX
  for (int i = 2; i <= n; ++i) {
    dp[i] = dp[i - 1] + k + (dp[i - 1] + k) / (i - 1);
  }
  princh(find(0, n) + 1, '\n');
}
int main() {
  int T = read();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/