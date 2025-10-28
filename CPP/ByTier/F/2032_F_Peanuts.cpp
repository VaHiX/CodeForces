// Problem: CF 2032 F - Peanuts
// https://codeforces.com/contest/2032/problem/F

/*
F. Peanuts
Algorithm: Dynamic Programming with Bitmask and Prefix XOR
Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem is about determining the number of valid box divisions that allow Alice to win in a game.
This game is a variant of the classic Nim-like game where each move involves removing peanuts from the leftmost non-empty box.
By modeling the game with prefix XORs and dynamic programming, we precompute states to determine whether a position leads to a winning or losing state.

Key Concepts:
- A position is losing if all moves lead to winning positions for the opponent.
- The game can be analyzed using Grundy numbers (Nimbers) or through prefix XOR analysis.
- This solution uses prefix XOR and DP to count valid distributions where Alice has a winning strategy.
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int mod = 998244353;
const int N = 1e6;
int v[N];
int ps[N + 1]; // prefix XOR array
int p[N + 1];  // powers of 2 modulo mod
int f[4];      // DP state for different XOR values (0,1,2,3)
void solve() {
  f[0] = f[1] = f[2] = f[3] = 0; // Initialize DP array
  p[0] = 1;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    ps[i + 1] = (ps[i] ^ v[i]);  // Compute prefix XOR
    p[i + 1] = 1ll * p[i] * 2 % mod; // Precompute powers of 2
  }
  int nr = 0;
  while (nr < n && v[nr] == 1) {
    nr++; // Count leading ones
  }
  if (nr == n) {  // Special case: all elements are 1
    cout << (n % 2 == 1 ? p[n - 1] : 0) << '\n';
    return;
  }
  int sum = 0;
  for (int i = nr; i < n; i++) {
    int x = min((ps[nr] ^ ps[i + 1]), 2); // Determine XOR value, capped at 2
    f[x] = (f[x] + p[max(n - i - 2, 0)]) % mod; // Update DP state with contribution
  }
  int sum2 = (((f[0] + f[1]) % mod + f[2]) % mod + f[3]) % mod;
  int ans = 0;
  for (int i = 0; i <= nr; i++) {
    int x = (ps[nr] ^ ps[i]); // XOR value from prefix
    int nr_val = p[max(i - 1, 0)]; // Power of 2 based on index
    if (i % 2 == 0) {
      ans = (ans + 1ll * nr_val * (sum2 - f[x] + mod) % mod) % mod; // Alice wins via losing state
    } else {
      ans = (ans + 1ll * nr_val * f[x] % mod) % mod; // Alice wins via winning state
    }
  }
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/