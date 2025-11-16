// Problem: CF 2045 H - Missing Separators
// https://codeforces.com/contest/2045/problem/H

/*
 * Problem: H. Missing Separators
 * Algorithm: Dynamic Programming with LCP (Longest Common Prefix) optimization
 * 
 * Approach:
 * - Use dynamic programming to find the maximum number of words that can be split
 *   from the string such that the words are in lexicographical order.
 * - The DP state f[l][r] represents the maximum number of words that can be formed
 *   starting from position l to r in the string.
 * - LCP table is precomputed for efficient comparison when checking if one word
 *   is a prefix of another.
 * - The trace table keeps track of how to split segments for reconstruction.
 * 
 * Time Complexity: O(n^3) where n is the length of the string S.
 * Space Complexity: O(n^2) for DP table, LCP table and trace table.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2> void maximize(T1 &a, T2 b) {
  if (b > a)
    a = b;
}
template <class T1, class T2> void minimize(T1 &a, T2 b) {
  if (b < a)
    a = b;
}
template <class T> void read(T &number) {
  bool negative = false;
  register int c;
  number = 0;
  c = getchar();
  while (c != '-' && !isalnum(c))
    c = getchar();
  if (c == '-') {
    negative = true;
    c = getchar();
  }
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
  if (negative)
    number *= -1;
}
template <class T, class... Ts> void read(T &a, Ts &...args) {
  read(a);
  read(args...);
}
#define fi first
#define se second
#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for (type i = (b); i >= (a); i--)
#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)
#define MAX 5005
#define MOD 1000000007
string s;
int n;
int lcp[MAX][MAX];
void buildLCP() {
  REV(int, i, n, 1)
  REV(int, j, n, i + 1)
  lcp[i][j] = (s[i] == s[j]) ? lcp[i + 1][j + 1] + 1 : 0;
}
int f[MAX][MAX];
int saveMinR2[MAX][MAX];
int trace[MAX][MAX];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> s;
  n = s.length();
  s = " " + s; // 1-indexed
  buildLCP();
  REV(int, l, n, 1) {
    f[l][n] = 1; // Base case: single word
    trace[l][n] = n; // trace to end
    for (int r = n - 1, l2 = n; r >= l; r--, l2--) {
      int same = min(lcp[l][l2], r - l + 1);
      lcp[l][l2] = 0; // Reset for next use
      int minR2 = l2 + same;
      if (minR2 > n)
        continue;
      if (same <= r - l && s[l + same] > s[minR2])
        continue;
      if (f[l2][minR2] == 0)
        continue;
      lcp[l][l2] = minR2;
      f[l][r] = f[l2][minR2] + 1;
      trace[l][r] = r;
    }
    REV(int, r, n - 1, l)
    if (f[l][r + 1] > f[l][r]) {
      f[l][r] = f[l][r + 1];
      trace[l][r] = trace[l][r + 1];
    }
  }
  int l = 1, r = trace[1][1]; // Start from beginning
  vector<string> all;
  while (l <= n) {
    string cur = "";
    FOR(int, i, l, r) cur += s[i];
    all.push_back(cur);
    int minR2 = lcp[l][r + 1]; // Next segment start
    l = r + 1;
    r = trace[l][minR2];
  }
  cout << all.size() << '\n';
  for (string s : all)
    cout << s << '\n';
}


// https://github.com/VaHiX/CodeForces/