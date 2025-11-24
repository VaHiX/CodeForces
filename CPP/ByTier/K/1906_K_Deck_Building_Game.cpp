// Problem: CF 1906 K - Deck-Building Game
// https://codeforces.com/contest/1906/problem/K

// Problem: K. Deck-Building Game
// Purpose: Count the number of ways to split N cards into two non-overlapping decks such that both have equal XOR power.
// Algorithms: 
//   - Fast Walsh-Hadamard Transform (FWHT) for efficient computation on XOR operations
//   - Modular arithmetic for large results
// Time Complexity: O(N log N)
// Space Complexity: O(N)

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long LL;
typedef double DB;
const int N = 1 << 17; // Power of 2 size to enable bit manipulation tricks (for FWHT)
const int MO = 998244353; // Modulo value for all operations

void ad(int &x, int y) { // Add with modulo handling
  x += y;
  if (x >= MO)
    x -= MO;
}

int mul(int x, int y) { return (LL)x * y % MO; } // Multiplication with modulo

int w, n, m, a[N], c[N], d[N];

int main() {
  int i, j, x, s;
  scanf("%d", &w); // Read the number of cards
  for (i = 1; i <= w; i++)
    scanf("%d", &x), a[x]++; // Count frequency of each card value

  m = 17; // Max bit length to handle up to 100000 values (log2(100000) < 17)
  n = 1 << m; // Size of the array for FFT-based operations, power of 2

  // FWHT-like prefix sum transformation
  for (j = 0; j < m; j++)
    for (i = 0; i < n; i++)
      if (i & (1 << j))
        ad(a[i ^ (1 << j)], a[i]); // This is the forward Walsh-Hadamard transform step

  c[0] = 1;
  for (i = 1; i <= m; i++)
    c[i] = mul(c[i - 1], MO - 2); // Inverse of 2 mod MO, used to normalize coefficients

  for (i = 0; i < n; i++)
    a[i] = mul(a[i], c[__builtin_popcount(i)]); // Normalize by number of 1s in binary representation

  // Backward FWHT transform
  for (j = 0; j < m; j++)
    for (i = 0; i < n; i++)
      if (i & (1 << j))
        ad(a[i], a[i ^ (1 << j)]); // Again, applying inverse operation

  d[0] = 1;
  for (i = 1; i <= w; i++)
    d[i] = mul(d[i - 1], MO - 3); // Inverse of 3 mod MO used later for normalization

  s = 0;
  for (i = 0; i < n; i++)
    ad(s, d[(w + a[i]) % MO / 2]); // Accumulate result using the transformed values

  if (w % 2) // If odd number of cards are considered
    s = mul(s, MO - 1); // Multiply by -1 mod MO

  for (i = 0; i < m; i++) // Apply transformation factor (2^m)
    s = mul(s, (MO + 1) / 2);

  printf("%d\n", s);
  return 0;
}


// https://github.com/VaHiX/codeForces/