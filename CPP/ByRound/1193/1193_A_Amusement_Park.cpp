// Problem: CF 1193 A - Amusement Park
// https://codeforces.com/contest/1193/problem/A

#include <iostream>

using namespace std;
const int mod = 998244353;
int n, m, f[1 << 18], u[400], v[400];
bool can[1 << 18];
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++)
    cin >> u[i] >> v[i], --u[i], --v[i]; // Read edges and convert to 0-based indexing
  f[0] = 1; // Base case: no slides selected, one way to assign elevation (all same)
  for (int i = 1; i < (1 << n); i++) {
    can[i] = 1; // Initially assume all subsets are valid
    for (int j = 1; j <= m; j++) {
      if ((i >> u[j] & 1) && (i >> v[j] & 1))
        can[i] = 0; // If both nodes of an edge are selected, then it's invalid since we would have a cycle
    }
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int j = i; j; j = (j - 1) & i) { // For each subset j of i
      if (can[j])
        f[i] = ((f[i] + (__builtin_popcount(j) & 1 ? 1 : -1) * f[i ^ j]) % mod +
                mod) %
               mod; // Inclusion-exclusion: add or subtract based on parity of set size
    }
  }
  cout << 1ll * 499122177 * f[(1 << n) - 1] % mod * m % mod << endl; // Final result computed using modular inverse and multiplication by m
}


// https://github.com/VaHiX/codeForces/