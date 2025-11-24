// Problem: CF 1975 I - Mind Bloom
// https://codeforces.com/contest/1975/problem/I

/*
 * Problem: Slay the Spire
 * Description:
 *   Jellyfish plays a one-player card game. The goal is to compute the probability that 
 *   she can empty the draw pile completely by repeatedly playing cards and drawing new ones.
 *   Cards have powers, and when played, they're placed back into the draw pile.
 *   Then, a random subset of size equal to that card's power is drawn from the draw pile.
 *
 * Approach:
 *   - Dynamic programming with memoization
 *   - Preprocess inverses for modular arithmetic
 *   - Use inclusion-exclusion or probabilistic transitions depending on hand state
 *   - Track probabilities of reaching empty draw pile given current configurations
 *
 * Time Complexity: O(n^3), where n <= 120
 * Space Complexity: O(n^3)
 */

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
const int P = 1e9 + 7, N = 125;
int T, n, a[N], inv[N], f[N][N][N], g[N][N][N], h[N], F[N][N], ct[N];
char s[N];

// Fast exponentiation to compute modular inverse
int ksm(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % P)
    if (y & 1)
      res = 1ll * res * x % P;
  return res;
}

// Add with modular arithmetic
inline void Add(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}

// Main DP function to calculate transition probabilities for a specific card at index i and value x
void DP(int i, int x) {
  if (!a[i])
    return f[i][x][x] = 1, void();  // Base case: no more cards of this type
  int sum = a[i];
  for (int j = 1; j <= x; ++j)
    sum += a[j];
  if (sum >= n)
    return;  // Early termination condition
  if (x + a[i] >= n)
    return;  // Another early termination

  int up = n;
  if (i < n && a[i] == a[i + 1]) {
    for (int j = i - 1; j <= i; ++j)
      for (int y = 0; y <= n; ++y)
        g[x][j][y] = 0;  // Clear transitions if same power
    up = i + 1;
  } else {
    memset(g[x], 0, sizeof(g[x]));  // Clear memory and initialize
    g[x][n][x + a[i]] = 1;
  }

  memset(h, 0, sizeof(h));  // Initialize helper array
  int lim = x + a[i];
  for (int j = up; j >= i; --j)
    for (int y = j; y >= lim; --y)
      if (g[x][j][y]) {
        int p = 1ll * (y - x) * inv[j - x] % P;  // Probability component
        Add(g[x][j - 1][y], 1ll * (1 + P - p) * g[x][j][y] % P);  // Transition update for staying in hand
        p = 1ll * p * g[x][j][y] % P;  // Update probability weight

        // Process valid transitions to future states
        for (int z = a[j] + y - 1; z <= j - 1; ++z) {
          if (j == i && y - 1 == x)
            Add(h[z], p);  // Special case handling for early termination
          else
            Add(g[x][j - 1][z], 1ll * p * f[j][y - 1][z] % P);  // Regular state transition
        }
      }

  // Finalize results by computing probability coefficients
  for (int y = x; y < i; ++y)
    f[i][x][y] = 1ll * g[x][i - 1][y] * ksm(1 + P - h[y], P - 2) % P;
}

// Solve individual test case
void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  scanf("%s", s + 1);

  // Count prefix sum of '1's in string s (number of cards in hand)
  for (int i = 1; i <= n; ++i)
    ct[i] = ct[i - 1] + (s[i] == '1');

  if (ct[n] == n)
    return puts("1"), void(); // All cards already in hand, success with full probability
  if (!ct[n])
    return puts("0"), void(); // No cards in hand, impossible

  if (a[1] > 1)
    return puts("1"), void(); // First card gives high power, likely to win quickly
  if (a[n] == 1)
    return puts("0"), void(); // Last card is just 1 power -> will never be able to clear draw pile

  memset(f, 0, sizeof(f)); // Reset DP tables
  for (int i = n; i; --i)
    for (int x = i - 1; ~x; --x)
      DP(i, x);  // Process each possible hand configuration

  memset(F, 0, sizeof(F));
  F[0][0] = 1; // Base case: zero cards played with zero probability of failure

  // Forward DP to accumulate probabilities
  for (int i = 1; i <= n; ++i)
    for (int x = ct[i]; x <= i; ++x) {
      for (int y = 0; y < i; ++y)
        Add(F[i][x], 1ll * f[i][x - 1][y] * F[i - 1][y] % P);  // Accumulate over states

      if (s[i] == '1')
        continue;  // Card drawn from draw pile, skip drawing logic

      int p = 1ll * (x - ct[i]) * inv[i - ct[i]] % P;
      F[i][x] = 1ll * F[i][x] * p % P;  // Probability of drawing specific subset
      Add(F[i][x], 1ll * (1 + P - p) * F[i - 1][x] % P);  // Transition from previous state
    }

  printf("%d\n", (P + 1 - F[n][ct[n]]) % P);  // Final computed probability
}

int main() {
  for (int i = 1; i <= 120; ++i)
    inv[i] = ksm(i, P - 2);  // Precompute modular inverses

  scanf("%d", &T);
  while (T--)
    solve();

  return 0;
}


// https://github.com/VaHiX/codeForces/