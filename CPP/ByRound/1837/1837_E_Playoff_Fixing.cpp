// Problem: CF 1837 E - Playoff Fixing
// https://codeforces.com/contest/1837/problem/E

/*
 * Problem: Playoff Fixing
 *
 * Purpose: Given k, we have 2^k teams numbered 1 to 2^k in order of decreasing
 * strength. Each team is assigned a seed (1 to 2^k). The tournament proceeds in
 * a binary tree fashion, where the winner of each match advances to the next
 * round. We are given a partial assignment of seeds to teams, and we need to
 * count the number of valid completions such that the final standings match the
 * desired placements.
 *
 * Algorithms/Techniques:
 *  - Recursion with memoization
 *  - Tree-based simulation of tournament
 *  - Combinatorial counting using factorials and powers of 2
 *
 * Time Complexity: O(2^k * k) due to recursive calls on tournament structure
 * and operations. Space Complexity: O(2^k) for storing factorials and auxiliary
 * arrays.
 */

#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <vector>

using namespace std;
typedef long long ll;

// Helper I/O module
namespace IO {
char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline ll read() {
  ll x = 0, h = 1;
  char ch = getchar();
  while (!(ch == '-' || (ch >= '0' && ch <= '9')))
    ch = getchar();
  if (ch == '-')
    h = -1, ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x * h;
}
inline void print(ll x) {
  if (x > 9)
    print(x / 10);
  putchar(x % 10 + '0');
}
inline void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  print(x);
}
} // namespace IO
using namespace IO;

// Mathematical functions
namespace MathLab {
inline ll ksm(ll _x, ll _k, ll _mod) {
  ll _res = 1;
  while (_k) {
    if (_k & 1)
      _res = _res * _x % _mod;
    _x = _x * _x % _mod;
    _k >>= 1;
  }
  return _res;
}
inline ll phi(ll _x) {
  ll _res = _x;
  for (ll _i = 2; _i * _i <= _x; _i++) {
    if (_x % _i == 0) {
      while (_x % _i == 0)
        _x /= _i;
      _res = _res * (_i - 1) / _i;
    }
  }
  if (_x > 1)
    _res = _res * (_x - 1) / _x;
  return _res;
}
inline ll gcd(ll _x, ll _y) { return _y ? gcd(_y, _x % _y) : _x; }
inline ll lcm(ll _x, ll _y) { return _x * _y / gcd(_x, _y); }
inline bool IsPrime(ll _x) {
  if (_x <= 1)
    return 0;
  for (ll _i = 2; _i * _i <= _x; _i++)
    if (_x % _i == 0)
      return 1;
  return 0;
}
inline void AddMod(ll &_x, ll _y, ll _mod) {
  _x = (_x + _y >= _mod ? _x + _y - _mod : _x + _y);
}
inline void MulMod(ll &_x, ll _y, ll _mod) { _x = _x * _y % _mod; }
inline ll GetMid(ll _x) {
  return (_x & 1LL) ? ((_x >> 1LL) + 1LL) : (_x >> 1LL);
}
inline ll GetFac(ll _x, ll _mod) {
  return _x ? GetFac(_x - 1, _mod) * _x % _mod : 1LL;
}
inline ll Inv(ll _x, ll _mod) { return ksm(_x, _mod - 2, _mod); }
} // namespace MathLab

#define File(name)                                                             \
  freopen(#name ".in", "r", stdin);                                            \
  freopen(#name ".out", "w", stdout);
#define ERR assert(0)
#define RunTime ((double)clock() / CLOCKS_PER_SEC)

// Main solution logic
namespace YYZ {
const ll N = 1 << 20;
const ll K = 24;
const ll mod = 998244353;
ll k;
ll fac[N], gtw[N];

// Recursive function to calculate valid assignments
ll solve(vector<ll> T) {
  if (T.size() == 1)
    return 1;

  // Divide the current tournament into two halves for left and right subtrees
  ll n = T.size(), base = n / 2;
  ll c = 0, d = n / 2; // c = number of pairs with both elements unassigned
                       // d = number of slots in right subtree to be filled with
                       // elements from left subtree

  // Count how many elements from left subtree are already paired with elements
  // from right subtree
  for (auto v : T)
    d -= (v <= base ? 0 : 1);

  vector<ll> P;
  for (ll i = 0; i < base; i++) {
    ll p = 2 * i, q = 2 * i + 1;
    // Check if both elements in the pair are from the same side (impossible)
    if (0 <= T[p] && T[p] <= base && 0 <= T[q] && T[q] <= base)
      return 0;
    if (0 <= T[p] && T[p] > base && 0 <= T[q] && T[q] > base)
      return 0;

    // If both are unassigned
    if (T[p] == -1 && T[q] == -1)
      c++;

    // Determine which side each element comes from
    if (T[q] != -1 && T[q] <= base)
      P.push_back(T[q]);
    else if (T[p] != -1 && T[p] <= base)
      P.push_back(T[p]);
    else
      P.push_back(-1);
  }

  // Multiply the result of the subproblem with combinations of choices
  return solve(P) * gtw[c] % mod * fac[d] % mod;
}

void main() {
  // Precompute factorials and powers of 2
  fac[0] = 1;
  for (ll i = 1; i <= N - 10; i++)
    fac[i] = fac[i - 1] * i % mod;
  gtw[0] = 1;
  for (ll i = 1; i <= N - 10; i++)
    gtw[i] = gtw[i - 1] * 2 % mod;

  k = read();
  k = (1 << k); // 2^k

  vector<ll> S;
  for (ll i = 1; i <= k; i++)
    S.push_back(read());

  printf("%lld\n", solve(S));
}

} // namespace YYZ

int main() {
  ll T = 1;
  while (T--)
    YYZ::main();
  fprintf(stderr, "TIME:%.3lf s\n", RunTime);
  return 0;
}

// https://github.com/VaHiX/CodeForces/