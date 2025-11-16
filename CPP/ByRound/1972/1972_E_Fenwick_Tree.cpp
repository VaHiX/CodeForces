// Problem: CF 1972 E - Fenwick Tree
// https://codeforces.com/contest/1972/problem/E

/*
Algorithm: Fenwick Tree inverse computation
Purpose: Given an array b and a positive integer k, find an array a such that
f^k(a) = b. The algorithm computes the inverse transformation of the Fenwick
tree to recover the original array.

Techniques:
- Modular arithmetic with custom Modint class
- Inverse Fenwick tree transformation using binary lifting concepts
- Precomputed inverses for modular division
- Efficient lowbit operation for binary indexing

Time Complexity: O(n * log(n) * k) where n is array length and k is the power of
f Space Complexity: O(n) for storing arrays and precomputed inverses
*/
#include <iostream>
#include <random>
#include <stdio.h>

#define rep(x, y, z) for (int x = (y); x <= (z); ++x)
#define per(x, y, z) for (int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define endl '\n'
using namespace std;
typedef long long ll;
template <typename T> void chkmin(T &x, T y) {
  if (x > y)
    x = y;
}
template <typename T> void chkmax(T &x, T y) {
  if (x < y)
    x = y;
}
template <int mod> inline unsigned int down(unsigned int x) {
  return x >= mod ? x - mod : x;
}
template <int mod> struct Modint {
  unsigned int x;
  Modint() = default;
  Modint(unsigned int x) : x(x) {}
  friend istream &operator>>(istream &in, Modint &a) { return in >> a.x; }
  friend ostream &operator<<(ostream &out, Modint a) { return out << a.x; }
  friend Modint operator+(Modint a, Modint b) { return down<mod>(a.x + b.x); }
  friend Modint operator-(Modint a, Modint b) {
    return down<mod>(a.x - b.x + mod);
  }
  friend Modint operator*(Modint a, Modint b) { return 1ULL * a.x * b.x % mod; }
  friend Modint operator/(Modint a, Modint b) { return a * ~b; }
  friend Modint operator^(Modint a, int b) {
    Modint ans = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1)
        ans *= a;
    return ans;
  }
  friend Modint operator~(Modint a) { return a ^ (mod - 2); }
  friend Modint operator-(Modint a) { return down<mod>(mod - a.x); }
  friend Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
  friend Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
  friend Modint &operator*=(Modint &a, Modint b) { return a = a * b; }
  friend Modint &operator/=(Modint &a, Modint b) { return a = a / b; }
  friend Modint &operator^=(Modint &a, int b) { return a = a ^ b; }
  friend Modint &operator++(Modint &a) { return a += 1; }
  friend Modint operator++(Modint &a, int) {
    Modint x = a;
    a += 1;
    return x;
  }
  friend Modint &operator--(Modint &a) { return a -= 1; }
  friend Modint operator--(Modint &a, int) {
    Modint x = a;
    a -= 1;
    return x;
  }
  friend bool operator==(Modint a, Modint b) { return a.x == b.x; }
  friend bool operator!=(Modint a, Modint b) { return !(a == b); }
};
const int N = 1e6 + 100, mod = 998244353;
typedef Modint<mod> mint;
int T, n, k;
mint a[N], inv[N];
inline int lowbit(int x) { return x & -x; }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // Precompute modular inverses for division
  inv[0] = inv[1] = 1;
  rep(i, 2, N - 1) inv[i] = (mod - mod / i) * inv[mod % i];
  for (cin >> T; T; --T) {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    // Invert the transformations, starting from the end
    rep(i, 1, n) {
      mint mul = 1;
      // Traverse up the Fenwick tree structure applying reverse transformations
      for (int u = i + lowbit(i), d = 1; u <= n; u += lowbit(u), ++d) {
        mul *= (d + k - 1) * inv[d]; // Adjust multiplier
        a[u] -= mul * a[i];          // Update values
      }
    }
    rep(i, 1, n) cout << a[i] << " \n"[i == n];
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/