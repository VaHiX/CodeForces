// Problem: CF 1815 E - Bosco and Particle
// https://codeforces.com/contest/1815/problem/E

/*
Algorithm: KMP-based cycle detection and prime factorization for computing cycle length.
Time Complexity: O(N), where N is the sum of lengths of all binary strings.
Space Complexity: O(N), for storing strings and auxiliary arrays.

This solution computes the cycle length of a particle moving through a line with oscillators.
Each oscillator has a binary state string that changes on interaction with the particle.
The particle reverses direction when hitting a 1-state oscillator or at boundary points (0 or n+1).
The key insight is to compute the periodicity of each oscillator's behavior and combine
these periods using number theory (LCM computation via prime factorization).
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
#define N 1000005
#define MOD 998244353
const int up = 1e6;
int n, o, ans, inv[N], fail[N], z[N];
char a[N];

// Add y to x, handling modular arithmetic
void W(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}

// Compute the smallest period of string a using KMP failure function
int calc(int n) {
  for (int i = 2, j = 0; i <= n; ++i) {
    while (j && a[i] != a[j + 1])
      j = fail[j];
    if (a[i] == a[j + 1])
      ++j;
    fail[i] = j;
  }
  for (int i = fail[n]; i; i = fail[i])
    if (!(n % (n - i)))
      return n - i;
  return n;
}

// Update prime factorization counts for LCM calculation
void upd(int x, int vl) {
  for (int i = 2; i <= x; ++i)
    while (!(x % i)) {
      x /= i;
      z[i] += vl;
      if (z[i] < 0)
        z[i] = 0, o = 1ll * o * i % MOD, ans = 1ll * ans * i % MOD;
    }
}

int main() {
  scanf("%d", &n);
  o = ans = 1;
  
  // Precompute modular inverses
  for (int i = 1; i <= up; ++i)
    inv[i] = i > 1 ? 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD : 1;
    
  for (int i = 1, t, x; i <= n; ++i) {
    bool s = 0;
    scanf("%s", a + 1);
    t = calc(strlen(a + 1)); // Get the minimal period of the string
    x = 0;
    
    // Compute the effective period based on whether the final state is 1 or 0
    for (int j = 1; j <= t; ++j)
      s ^= a[j] == '0', x += (!s);
      
    if (s & 1)
      x = t, t *= 2;
      
    // Adjust the prime factorization of the cycle lengths
    upd(x, -1);
    upd(t - x, 1);
    
    if (t == x)
      break;
      
    // Update the answer with modular multiplication and inverse
    o = 1ll * o * (t - x) % MOD * inv[x] % MOD;
    W(ans, o);
  }
  
  // Double the result for final modulo output
  W(ans, ans);
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/