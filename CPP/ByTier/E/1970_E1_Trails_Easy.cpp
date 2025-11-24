// Problem: CF 1970 E1 - Trails (Easy)
// https://codeforces.com/contest/1970/problem/E1

/*
 * Problem: Harry Potter hiking in the Alps with m cabins, each connected to a lake by short/long trails.
 *          Each day, he walks from a cabin to lake and then back to any cabin (possibly same),
 *          with at least one of the two trails being short.
 *          Count valid combinations of trails over n days starting from cabin 1.
 *
 * Approach:
 *  - Dynamic Programming with Matrix Exponentiation
 *  - State: (short_trails, long_trails) from current cabin to lake and back
 *  - Matrix exponentiation to compute transitions efficiently in O(log n) time
 *  - State transition matrix encodes valid moves with constraints (at least one short)
 *  - Time Complexity: O(m^3 * log(n)) due to matrix multiplication and exponentiation
 *  - Space Complexity: O(1) since matrix size is constant (2x2)
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const long long P = 2;
const long long MOD = 1e9 + 7;

// Matrix structure for transition
struct node {
  long long A[3][3]; // 2x2 matrix (indexed from 1)
} B, C;

long long f[3], ans[3];
long long n, m, sum, s[100010], l[100010];

// Multiply two matrices
node operator*(node a1, node a2) {
  long long i, j, k;
  node t;
  for (i = 1; i <= P; ++i)
    for (j = 1; j <= P; ++j) {
      t.A[i][j] = 0;
      for (k = 1; k <= P; ++k)
        t.A[i][j] = (t.A[i][j] + a1.A[i][k] * a2.A[k][j]) % MOD;
    }
  return t;
}

// Fast matrix exponentiation
node ksm(long long b) {
  if (b == 1)
    return B;
  node t = ksm(b / 2);
  if (b % 2)
    return t * t * B;
  else
    return t * t;
}

int main() {
  long long i;
  scanf("%lld %lld", &m, &n);
  for (i = 1; i <= m; ++i)
    scanf("%lld", &s[i]);
  for (i = 1; i <= m; ++i)
    scanf("%lld", &l[i]);

  // Initial state (from cabin 1)
  f[1] = s[1], f[2] = l[1];
  --n;
  if (!n)
    ans[1] = f[1], ans[2] = f[2];
  else {
    // Build transition matrix
    for (i = 1; i <= m; ++i) {
      B.A[1][1] = (B.A[1][1] + (s[i] + l[i]) * s[i]) % MOD;
      B.A[2][1] = (B.A[2][1] + s[i] * s[i]) % MOD;
      B.A[1][2] = (B.A[1][2] + (s[i] + l[i]) * l[i]) % MOD;
      B.A[2][2] = (B.A[2][2] + s[i] * l[i]) % MOD;
    }
    C = ksm(n); // Compute B^n
    ans[1] = (f[1] * C.A[1][1] + f[2] * C.A[2][1]) % MOD;
    ans[2] = (f[1] * C.A[1][2] + f[2] * C.A[2][2]) % MOD;
  }
  // Sum all valid combinations to answer
  for (i = 1; i <= m; ++i)
    sum = (sum + ans[1] * (s[i] + l[i]) + ans[2] * s[i]) % MOD;
  printf("%lld", sum);
  return 0;
}


// https://github.com/VaHiX/CodeForces/