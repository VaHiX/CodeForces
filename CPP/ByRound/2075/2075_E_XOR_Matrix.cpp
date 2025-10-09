// Problem: CF 2075 E - XOR Matrix
// https://codeforces.com/contest/2075/problem/E

/*
E. XOR Matrix
Purpose:
  Count the number of pairs of arrays (a, b) such that:
    - a has n elements from [0, A]
    - b has m elements from [0, B]
    - XOR matrix X[i][j] = a[i] ^ b[j] has at most 2 distinct values

Algorithms/Techniques:
  - Modular arithmetic with precomputed powers and modular inverse
  - Bitwise manipulation with bit-by-bit analysis
  - Inclusion-exclusion principle using linearity of expectation over bits

Time Complexity: O(30 * t) per test case, where 30 is the number of bits in integers up to 2^29
Space Complexity: O(1) — only constant extra space used

*/

#include <algorithm>
#include <iostream>
#include <utility>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int mod = 998244353;
inline int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }
inline int mul(int x, int y) { return (ll)x * y % mod; }
int pow(int x, int y) {
  int res = 1, pot = x;
  while (y) {
    if (y % 2)
      res = mul(res, pot);
    pot = mul(pot, pot);
    y /= 2;
  }
  return res;
}
void task() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  int res = mul(a + 1, b + 1); // All arrays where both a and b are constant
  res =
      add(res, mul(pow(2, n) + mod - 2, mul((ll)a * (a + 1) / 2 % mod, b + 1))); // Case with fixed value on rows only
  res =
      add(res, mul(pow(2, m) + mod - 2, mul((ll)b * (b + 1) / 2 % mod, a + 1))); // Case with fixed value on columns only
  
  int mu = mul(mul(pow(2, n) + mod - 2, pow(2, m) + mod - 2), pow(4, mod - 2)); // Precomputed coefficient
  for (int i = 0; i < 30; i++) {
    int aa = (a & (1 << i + 1) - 1), bb = (b & (1 << i + 1) - 1);
    // For each bit, calculate contribution from cases where values differ at this bit
    res = add(
        res, mul(mul(mu, 1 << i), mul(a - aa + 2 * max(0, aa - (1 << i) + 1),
                                      b - bb + 2 * max(0, bb - (1 << i) + 1))));
  }
  cout << res << "\n";
}
int main() {
  FIO;
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/codeForces/