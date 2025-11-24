// Problem: CF 1970 E2 - Trails (Medium)
// https://codeforces.com/contest/1970/problem/E2

/*
 * Problem: E2. Trails (Medium)
 * 
 * Algorithm:
 * - Use matrix exponentiation to compute the number of valid trail combinations
 *   over n days.
 * - State representation:
 *   - State 0: Harry is at a cabin and the last trail was short.
 *   - State 1: Harry is at a cabin and the last trail was long.
 * - Transition matrix encodes valid moves:
 *   - From short trail to any cabin (short or long): sum of short and long trails.
 *   - From long trail to any cabin (short or long): sum of short and long trails.
 * - Matrix exponentiation used to efficiently compute transitions for n-1 steps.
 * 
 * Time Complexity: O(m + log(n)) where m is the number of cabins.
 * Space Complexity: O(1) excluding input storage.
 */

#include <string.h>
#include <iostream>
#include <utility>

using namespace std;
#define mod 1000000007
#define IOS ios::sync_with_stdio(0), cin.tie(0)
typedef long long ll;
typedef pair<ll, ll> p;
const int N = 2e5 + 5;
ll s[N], l[N];

// Matrix structure for fast exponentiation
struct matrix {
  ll a[2][2];
  matrix() { memset(a, 0, sizeof(a)); }
  matrix operator*(matrix &T) const {
    matrix ans;
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        for (int k = 0; k < 2; k++)
          ans.a[i][k] = (ans.a[i][k] + a[i][j] * T.a[j][k] % mod) % mod;
    return ans;
  }
  matrix operator^(ll y) {
    matrix bs = (*this);
    matrix ans;
    for (int i = 0; i < 2; i++)
      ans.a[i][i] = 1;
    for (; y;) {
      if (y & 1)
        ans = ans * bs;
      bs = bs * bs;
      y >>= 1;
    }
    return ans;
  }
};

// Precomputed sums for transition matrix calculation
ll sum_ss, sum_sl, sum_ls, sum_ll;
ll sum_l, sum_s;

int main() {
  IOS;
  ll m, n;
  cin >> m >> n;
  
  // Read input for short and long trails
  for (int i = 1; i <= m; i++)
    cin >> s[i], sum_s = (sum_s + s[i]) % mod;
  for (int i = 1; i <= m; i++)
    cin >> l[i], sum_l = (sum_l + l[i]) % mod;
    
  // Compute all pairwise sums needed for transition matrix
  for (int i = 1; i <= m; i++) {
    sum_ss = (sum_ss + s[i] * s[i] % mod) % mod;
    sum_sl = (sum_sl + s[i] * l[i] % mod) % mod;
    sum_ls = (sum_ls + s[i] * l[i] % mod) % mod;
    sum_ll = (sum_ll + l[i] * l[i] % mod) % mod;
  }
  
  // Build transition matrix
  matrix bs;
  bs.a[0][0] = (sum_ss + sum_ls) % mod;  // short -> short or long
  bs.a[0][1] = sum_ss;                   // short -> short only
  bs.a[1][0] = (sum_sl + sum_ll) % mod;  // long -> short or long
  bs.a[1][1] = sum_sl;                   // long -> short only

  // Exponentiate the matrix to n-1 steps
  bs = bs ^ (n - 1);
  
  // Initial state vector: start at cabin 1 with a short trail or long trail
  matrix ans;
  ans.a[0][0] = s[1];  // starting short trail from cabin 1
  ans.a[1][0] = l[1];  // starting long trail from cabin 1

  // Multiply transition matrix by initial state
  ans = bs * ans;

  // Final result calculation combining both possible starting states
  cout << (ans.a[0][0] * ((sum_s + sum_l) % mod) % mod +
           ans.a[1][0] * sum_s % mod) %
              mod
       << '\n';
}


// https://github.com/VaHiX/CodeForces/