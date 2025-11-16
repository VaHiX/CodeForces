// Problem: CF 2154 B - Make it Zigzag
// https://codeforces.com/contest/2154/problem/B

/*
Algorithm: Greedy with prefix maximums and cost calculation
Approach:
1. First, apply operation 1 (prefix max) on even indices to ensure they are at least as large as all previous elements.
2. Then, calculate the minimum cost to make the array zigzag by iterating over odd indices.
3. For each odd index i, we want a[i] < min(a[i-1], a[i+1]), so we compute required decrease.
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define ll long long
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pb push_back
#define re exit(0);
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)
#define LOOP(a) for (int i = 0, _a = (a); i < _a; i++)
#define left id << 1
#define right id << 1 | 1
#define _lower(v, x) lower_bound(v.begin(), v.end(), x) - v.begin() + 1
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
template <typename T> void chkmin(T &x, T y) {
  if (y < x)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (y > x)
    x = y;
}
const int mod = 1e9 + 7;
void add(int &a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
  if (a < 0)
    a += mod;
}
int _pow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b % 2 == 1)
      ans = 1ll * ans * a % mod;
    a = 1ll * a * a % mod;
    b /= 2;
  }
  return ans;
}
void rf() { freopen("input.inp", "r", stdin); }
const int maxn = 2e5;
int a[maxn + 5];
int n;
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  int cur_max = 0;
  // Apply operation 1 to even positions: set a[i] = max(a[1], ..., a[i])
  for (int i = 1; i <= n; i++) {
    chkmax(cur_max, a[i]);
    if (i % 2 == 0)
      a[i] = cur_max;
  }
  // Add sentinel values to simplify boundary checks
  a[0] = 1e9 + 7;
  a[n + 1] = 1e9 + 7;
  long long res = 0;
  // For each odd index, check if it needs to be decreased to satisfy zigzag condition
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      int d = min(a[i + 1], a[i - 1]);
      if (a[i] - d >= 0)
        res += a[i] - d + 1;
    }
  }
  cout << res << '\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int numTest;
  cin >> numTest;
  while (numTest--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/