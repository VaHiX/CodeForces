// Problem: CF 1928 C - Physical Education Lesson
// https://codeforces.com/contest/1928/problem/C

/*
Purpose: 
  This code solves the problem of finding how many valid values of k exist such that 
  a person at position n (1-indexed) gets number x (1-indexed) in the described settling pattern.

Algorithm:
  The settling pattern repeats every 2*k - 2 positions and has a specific structure:
  - First k numbers are 1, 2, ..., k
  - Next k-2 numbers are k-1, k-2, ..., 2
  - Then repeats.

Approach:
  We use mathematical analysis instead of brute-force to compute possible k values.
  The solution leverages the fact that we can analyze divisors of some derived expressions.
  It defines a helper function D() that counts valid k values for a given condition.

Time Complexity: O(√n) per test case due to divisor enumeration
Space Complexity: O(1) as only a few variables and precomputed values are used

*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <cstdio>
#include <vector>
#include <functional>
#include <utility>

#define X first
#define Y second
#define PB push_back
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<pii, int> ppi;
typedef pair<int, pii> pip;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
const int N = 3e5 + 500;
const int M = 1e6 + 500;
const int OFF = (1 << 18);
const int ALP = 30;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
namespace modulo_ops {
inline int add(int A, int B) {
  if (A + B >= MOD)
    return A + B - MOD;
  return A + B;
}
inline int sub(int A, int B) {
  if (A - B < 0)
    return A - B + MOD;
  return A - B;
}
inline int mul(int A, int B) { return (ll)A * B % MOD; }
inline int pot(int A, int B) {
  int ret = 1, bs = A;
  for (; B; B >>= 1) {
    if (B & 1)
      ret = mul(ret, bs);
    bs = mul(bs, bs);
  }
  return ret;
}
int fak[N], inv[N];
void precompute_fak() {
  fak[0] = 1;
  for (int i = 1; i < N; i++)
    fak[i] = mul(fak[i - 1], i);
  inv[N - 1] = pot(fak[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; i--)
    inv[i] = mul(inv[i + 1], i + 1);
}
int choose(int n, int k) { return mul(fak[n], mul(inv[k], inv[n - k])); }
} // namespace modulo_ops
inline int get_int() {
  int x;
  scanf("%d", &x);
  return x;
}
inline ll get_ll() {
  ll x;
  scanf("%lld", &x);
  return x;
}
void pyes() { printf("Yes\n"); }
void pno() { printf("No\n"); }
int multi_test = 1;
int D(int x, int bar) {
  int ans = 0;
  for (int i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      // Check if i is a valid divisor satisfying the condition
      ans += i % 2 == 0 && (i + 2) / 2 >= bar;
      if (x / i > i) {
        // Check the other corresponding divisor
        ans += (x / i) % 2 == 0 && ((x / i) + 2) / 2 >= bar;
      }
    }
  }
  return ans;
}
void solve() {
  int x, n;
  scanf("%d%d", &n, &x);
  x--;
  n--;
  if (x != 0) {
    // Compute count based on two derived expressions
    int ans = D(n - x, x + 2);
    ans += D(n + x, x + 2);
    // Manually check if (n % (2 * x)) == x to adjust the result
    if (n % (2 * x) == x)
      ans++;
    printf("%d\n", ans);
  } else {
    // Special case for x = 0
    printf("%d\n", D(n, 0));
  }
}
int main() {
  int T = multi_test ? get_int() : 1;
  for (; T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/