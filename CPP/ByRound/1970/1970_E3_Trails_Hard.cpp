// Problem: CF 1970 E3 - Trails (Hard)
// https://codeforces.com/contest/1970/problem/E3

// Purpose: Solve the problem of counting valid trail combinations for Harry Potter's hike over n days,
//          where each day he must take at least one short trail in either direction.
//          Uses matrix exponentiation to efficiently compute the result for large n.
//
// Algorithms:
//   - Matrix Exponentiation (fast computation of large powers of matrix)
//   - Dynamic Programming with state tracking
//
// Time Complexity: O(m + log(n)) due to matrix exponentiation and linear pass over m
// Space Complexity: O(1) for the processing (excluding input storage)

#include <stdio.h>
#include <iosfwd>

using namespace std;
const long long P = 2;
const long long MOD = 1e9 + 7;

// Define a structure to represent 2x2 matrix for matrix multiplication
struct node {
  long long A[3][3];  // Matrix elements (1-indexed for simplicity)
} B, C;

long long f[3], ans[3];
long long n, m, sum, s[100010], l[100010];

// Multiply two 2x2 matrices under modulo
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

// Fast matrix exponentiation to compute B^b
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

  // f[1] represents number of short trails from cabin 1, f[2] represents long trails
  f[1] = s[1], f[2] = l[1];

  --n;
  if (!n)
    ans[1] = f[1], ans[2] = f[2];
  else {
    // Build transition matrix B based on all cabins
    for (i = 1; i <= m; ++i) {
      B.A[1][1] = (B.A[1][1] + (s[i] + l[i]) * s[i]) % MOD;
      B.A[2][1] = (B.A[2][1] + s[i] * s[i]) % MOD;
      B.A[1][2] = (B.A[1][2] + (s[i] + l[i]) * l[i]) % MOD;
      B.A[2][2] = (B.A[2][2] + s[i] * l[i]) % MOD;
    }

    // Compute B^n using fast matrix exponentiation
    C = ksm(n);

    // Apply the computed matrix to initial state vector f
    ans[1] = (f[1] * C.A[1][1] + f[2] * C.A[2][1]) % MOD;
    ans[2] = (f[1] * C.A[1][2] + f[2] * C.A[2][2]) % MOD;
  }

  // Accumulate final answer by summing contributions from all cabins
  for (i = 1; i <= m; ++i)
    sum = (sum + ans[1] * (s[i] + l[i]) + ans[2] * s[i]) % MOD;
  printf("%lld", sum);
  return 0;
}


// https://github.com/VaHiX/CodeForces/