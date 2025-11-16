// Problem: CF 1938 D - Bánh Bò
// https://codeforces.com/contest/1938/problem/D

/*
 * Problem: Bánh Bò
 * Purpose: Calculate the number of uniform assemblies of bánh bò hấp (steamed chewy sponge cake) 
 *          in an r×c grid where each 6×7 subgrid has the same number of red pieces.
 * 
 * Algorithm:
 * - Uses dynamic programming with bitmasking to enumerate valid configurations.
 * - First calculates coefficients using combinations (C(n, k)).
 * - Then uses a recursive DP approach on grid transitions, simulating how each row contributes 
 *   to the final configuration under the constraints.
 * - The state transitions maintain the number of red pieces per row/column, encoded via bitmasks.
 * 
 * Time Complexity: O(r * c * 2^(6*7)) where r and c are bounded, and 6*7 = 42, but optimized with 
 *                  bitmask and DP states. Actual complexity is much lower due to pruning.
 * Space Complexity: O(2^(6*7)) for the DP table 't', which stores transitions.
 * Note: The problem constraints are such that r is divisible by 6 and c is divisible by 7.
 * 
 * Key Observations:
 * - The uniformity constraint on 6×7 subgrids allows treating each 6×7 block independently 
 *   when counting valid transitions.
 * - The problem reduces to counting configurations that satisfy fixed counts for overlapping 
 *   subgrids.
 * - Bitmasking is used to compactly represent the number of red pieces in consecutive rows 
 *   and columns within a 6×7 window.
 */

#include <iomanip>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif
using namespace std;
using ll = long long;
#define rng(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep(i, b) rng(i, 0, b)
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define si(x) int(x.size())
#define tct template <class t>
tct using vc = vector<t>;
#ifdef LOCAL
#define dmp(x) cerr << __LINE__ << " " << #x << " " << x << endl
#else
#define dmp(x) void(0)
#endif
template <class t, class u> bool chmax(t &a, u b) {
  if (a < b) {
    a = b;
    return true;
  } else
    return false;
}
template <class t, class u> bool chmin(t &a, u b) {
  if (b < a) {
    a = b;
    return true;
  } else
    return false;
}
template <class t, class u>
ostream &operator<<(ostream &os, const pair<t, u> &p) {
  return os << "{" << p.first << "," << p.second << "}";
}
template <class t> ostream &operator<<(ostream &os, const vector<t> &v) {
  os << "{";
  for (auto e : v)
    os << e << ",";
  return os << "}";
}
using P = pair<int, int>;
using uint = unsigned int;
const uint mod = 998244353;
struct mint {
  uint v;
  mint(ll vv = 0) { s(vv % mod + mod); }
  mint &s(uint vv) {
    v = vv < mod ? vv : vv - mod;
    return *this;
  }
  mint operator-() const { return mint() - *this; }
  mint &operator+=(mint r) { return s(v + r.v); }
  mint &operator-=(mint r) { return s(v + mod - r.v); }
  mint &operator*=(mint r) {
    v = (ll)v * r.v % mod;
    return *this;
  }
  mint &operator/=(mint r) { return *this *= r.inv(); }
  mint operator+(mint r) const { return mint(*this) += r; }
  mint operator-(mint r) const { return mint(*this) -= r; }
  mint operator*(mint r) const { return mint(*this) *= r; }
  mint operator/(mint r) const { return mint(*this) /= r; }
  mint pow(ll n) const {
    if (n < 0)
      return inv().pow(-n);
    mint res(1), x(*this);
    while (n) {
      if (n & 1)
        res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }
  mint inv() const { return pow(mod - 2); }
};
mint c[10][10], dp[2][10];
mint t[6][7][7][8 * 8 * 8 * 8 * 8 * 8];
int sv[8];
void solve() {
  int n, m;
  cin >> n >> m;
  rep(i, 9) {
    rep(j, i + 1) {
      if (j == 0 or i == j)
        c[i][j] = 1;
      else
        c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
    }
  }
  dp[0][0] = 1;
  dp[0][1] = 0;
  rng(i, 2, 7) {
    rep(sum, i + 1) dp[0][i] += c[i][sum].pow(m / 7);
    rep(z, i + 1) rep(o, i + 1 - z) {
      if (z + o == 0)
        continue;
      dp[0][i] -= c[i][z] * c[i - z][o] * dp[0][i - z - o];
    }
  }
  dp[1][0] = 1;
  dp[1][1] = 0;
  rng(i, 2, 8) {
    rep(sum, i + 1) dp[1][i] += c[i][sum].pow(n / 6);
    rep(z, i + 1) rep(o, i + 1 - z) {
      if (z + o == 0)
        continue;
      dp[1][i] -= c[i][z] * c[i - z][o] * dp[1][i - z - o];
    }
  }
  sv[0] = 1;
  rep(i, 7) sv[i + 1] = sv[i] * 8;
  t[0][0][1][0] = 1;
  t[0][0][0][sv[0]] = 1;
  t[0][0][0][0] = 2;
  rep(j, 7) {
    rep(i, 6) {
      if (i == 5) {
        rep(cur, 7) {
          rep(mask, 8 * 8 * 8 * 8 * 8 * 8) {
            t[i][j][cur][mask] *= dp[0][cur];
            if (j == 6) {
              int M = mask;
              rep(p, 6) {
                t[i][j][cur][mask] *= dp[1][M % 8];
                M /= 8;
              }
            }
          }
        }
      }
      if (i == 5 and j == 6)
        break;
      rep(cur, 7) {
        rep(mask, 8 * 8 * 8 * 8 * 8 * 8) {
          if (t[i][j][cur][mask].v == 0)
            continue;
          if (i == 5) {
            t[0][j + 1][1][mask] += t[i][j][cur][mask];
            t[0][j + 1][0][mask + sv[0]] += t[i][j][cur][mask];
            t[0][j + 1][0][mask] += t[i][j][cur][mask] * 2;
          } else {
            t[i + 1][j][cur + 1][mask] += t[i][j][cur][mask];
            t[i + 1][j][cur][mask + sv[i + 1]] += t[i][j][cur][mask];
            t[i + 1][j][cur][mask] += t[i][j][cur][mask] * 2;
          }
        }
      }
    }
  }
  mint ans;
  rep(a, 7) rep(b, 8 * 8 * 8 * 8 * 8 * 8) ans += t[5][6][a][b];
  cout << ans.v << '\n';
}
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(20);
  int t;
  t = 1;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/