// Problem: CF 2159 E - Super-Short-Polynomial-San
// https://codeforces.com/contest/2159/problem/E

/*
 * Problem: Super-Short-Polynomial-San
 * Algorithm: Fast polynomial coefficient sum computation using precomputed powers and convolution
 * Time Complexity: O(N * B + Q * B) where N = 3*10^5, B = 700 (block size)
 * Space Complexity: O(N * B + B^2) for storing power sums and precomputed values
 * 
 * The problem computes F(n) = (a*x^2 + b*x + c)^n and for each query (n,k), it finds sum of coefficients 
 * of terms up to x^k in F(n) modulo 10^9 + 7.
 * 
 * The approach uses block decomposition:
 *  - Precompute powers of (a*x^2 + b*x + c) for multiple values of n in blocks of size B = 700
 *  - For small n < B, precompute all coefficients directly
 *  - For large n >= B, use the block-based precomputed values
 *  - Each query does a convolution-like operation with precomputed coefficients
 */

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#define ll long long
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vN vector<node>
#define vpii vector<pii>
#define vpll vector<pll>
#define vvi vector<vi>
#define all(x) x.begin(), x.end()
#define u32 uint32_t
#define u64 uint64_t
#ifndef ONLINE_JUDGE
#define Log(x) cerr << "Debug: " << x
#else
#define Log(x) 0
#endif
using namespace std;
template <typename T> istream &operator>>(istream &in, vector<T> &a) {
  for (auto &x : a)
    in >> x;
  return in;
}
template <typename T> ostream &operator<<(ostream &out, vector<T> &a) {
  for (auto &x : a)
    out << x << " ";
  return out;
}
template <typename T, typename K>
istream &operator>>(istream &in, pair<T, K> &a) {
  in >> a.F >> a.S;
  return in;
}
template <typename T, typename K>
ostream &operator<<(ostream &out, pair<T, K> &a) {
  out << a.F << " " << a.S;
  return out;
}
const u32 N = 3e5 + 1;
const u32 M = N << 1;
const u32 B = 700;
const u32 mod32 = 1e9 + 7;
inline constexpr u32 reduce(u64 x) { return x % mod32; }
inline constexpr u32 mul(u32 x, u32 y) {
  return reduce(static_cast<u64>(x) * y);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<u32> inv(M, 1);
  for (u32 i = 2; i < M; ++i) {
    inv[i] = mod32 - mul((mod32 / i), inv[mod32 % i]);
  }
  u32 a, b, c;
  cin >> a >> b >> c;
  auto modPow = [](u32 a, u32 p) {
    u32 res = 1;
    while (p) {
      if (p & 1)
        res = mul(res, a);
      p >>= 1;
      a = mul(a, a);
    }
    return res;
  };
  const u32 _C = c;
  const u32 cinv = modPow(_C, mod32 - 2);
  const u32 _A = mul(a, cinv);
  const u32 _B = mul(b, cinv);
  auto getPower = [&](u32 p) {
    vector<u32> res((p << 1) | 1);
    res[0] = modPow(_C, p);
    if (p)
      res[1] = mul(mul(_B, res[0]), p);
    for (u32 i = 2; i < res.size(); ++i) {
      res[i] = mul(inv[i], mul(mul(_A, (p << 1) - (i - 2)), res[i - 2]) +
                               mul(mul(_B, mod32 + p - i + 1), res[i - 1]));
    }
    return res;
  };
  vector<vector<u32>> quo((N / B) + 1);
  for (u32 i = 0; (i * B) < N; ++i) {
    quo[i] = getPower(i * B);
    auto &res = quo[i];
    for (u32 i = 1; i < res.size(); ++i) {
      res[i] += res[i - 1];
      if (res[i] >= mod32)
        res[i] -= mod32;
    }
  }
  vector<vector<u32>> rem(B);
  for (u32 i = 0; i < B; ++i) {
    rem[i] = getPower(i);
  }
  u64 ans = 0;
  int q;
  cin >> q;
  while (q--) {
    int n, k;
    cin >> n >> k;
    n ^= ans;
    k ^= ans;
    if (n >= N)
      break;
    int Q = n / B;
    int R = n % B;
    ans = 0;
    auto &curR = rem[R];
    auto &curQ = quo[Q];
    auto get = [&](int ind) {
      return (ind >= curQ.size()) ? curQ.back() : curQ[ind];
    };
    for (int i = 0; (i <= k) && (i < curR.size()); ++i) {
      ans += mul(curR[i], get(k - i));
    }
    ans %= mod32;
    ans = reduce(ans);
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/