// Problem: CF 1654 H - Three Minimums
// https://codeforces.com/contest/1654/problem/H
//
// Algorithm Overview:
// - Goal: Count sequences of n elements where exactly m constraint operators (<
// or >) are satisfied,
//   and all three of min/max/median values occur exactly once.
// - Key Techniques:
//   1. Compute forward DP f[i] = count of valid sequences ending at position i.
//   2. Compute backward DP g[i] = count of valid sequences starting at position
//   i.
//   3. Use divide-and-conquer with NTT-based polynomial multiplication to
//   accelerate DP transitions.
//   4. Precompute combinatorial coefficients and constraint-dependent lookup
//   tables.
//   5. Combine forward and backward DPs with binomial weights to get final
//   answer.
// - Data Structures:
//   - NTT (Number Theoretic Transform): Fast polynomial multiplication mod
//   998244353.
//   - Factorials (jc), inverse factorials (ny), powers of 2 (mi): For
//   combinatorial lookups.
//   - Lookup table lk: Precomputed constraint-dependent multipliers.
//   - DP arrays: f (forward), g (backward), rf (backward reflection), ff
//   (forward extended).
// - Time Complexity: O(n log^2 n) per test case via divide-and-conquer NTT.

#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
const int dg = 3;
// Precomputed arrays (unused in this version; kept for compatibility).
long long int pmmx[(int)(1e6)], pnsx[(int)(1e6)];
long long int atet[100000000], pmx[(int)(1e6)], px[(int)(1e6)];

// Modular exponentiation: compute x^y mod p.
int P(int x, int y = p - 2) {
  int z = 1;
  // Binary exponentiation: multiply z by x^(bit) for each bit of y.
  for (; y; x = 1ll * x * x % p, y >>= 1)
    if (y & 1)
      z = 1ll * z * x % p;
  return z;
}
const int fdg = P(dg);
// Scalar multiply: B[i] = k * A[i] mod p.
void kA(int *B, int *A, int k, int le) {
  for (int i = 0; i < le; i++)
    B[i] = 1ll * A[i] * k % p;
}
// Pointwise multiply: C[i] = A[i] * B[i] mod p.
void AB(int *C, int *A, int *B, int le) {
  for (int i = 0; i < le; i++)
    C[i] = 1ll * A[i] * B[i] % p;
}
// Macro: copy le integers from B to A.
#define cop(A, B, le) memcpy(A, B, sizeof(int) * (le))
// Macro: clear le integers in A (set to 0).
#define cle(A, le) memset(A, 0, sizeof(int) * (le))
int fz[530000];
// Number-Theoretic Transform (NTT): Fast polynomial multiplication mod
// p=998244353. op=1: DFT (forward); op=0: IDFT (inverse).
void NTT(int *F, int l, int op) {
  // Bit-reversal permutation: map index i to its bit-reversed position.
  for (int i = 0; i < l; i++)
    fz[i] = (fz[i >> 1] >> 1) | ((i & 1) ? l >> 1 : 0);
  // Swap F[i] with F[fz[i]] to reorder coefficients for FFT.
  for (int i = 0; i < l; i++)
    if (i < fz[i])
      swap(F[i], F[fz[i]]);
  // Cooley-Tukey FFT: process each butterfly level.
  for (int le = 2; le <= l; le <<= 1) {
    int ml = le >> 1;
    // Primitive le-th root of unity (or its inverse for IDFT).
    int tg = P(op ? dg : fdg, (p - 1) / le);
    for (int i = 0; i < l; i += le) {
      int G = 1;
      // Butterfly operation: combine pairs F[j] and F[j+ml] using twiddle
      // factors.
      for (int j = i; j < i + ml; j++) {
        int tt = 1ll * G * F[j + ml] % p;
        F[j + ml] = F[j] - tt, F[j] = F[j] + tt;
        F[j + ml] += F[j + ml] < 0 ? p : 0, F[j] -= F[j] >= p ? p : 0;
        G = 1ll * G * tg % p;
      }
    }
  }
}
// Forward NTT transform: map polynomial to frequency domain.
void DFT(int *A, int le) { NTT(A, le, 1); }
// Inverse NTT transform: map polynomial back from frequency domain; divide by
// le.
void IDFT(int *A, int le) { NTT(A, le, 0), kA(A, A, P(le), le); }
int L[530000];
// Polynomial multiplication using NTT: F := F * G mod x^nel (truncate to nel
// terms).
void cheng(int *F, int *G, int len, int nel) {
  cop(L, G, len);
  // Pad to power of 2 size for NTT.
  int le = 1;
  while (le < (len << 1))
    le <<= 1;
  // Transform, multiply pointwise, and transform back.
  DFT(F, le), DFT(L, le), AB(F, F, L, le), IDFT(F, le);
  // Clear high-order terms and temporary storage.
  cle(F + nel, le - nel), cle(L, le);
}
int jc[200005], ny[200005], mi[200005];
// Main variables: n (sequence length), m (constraint count), op (operators),
// f/rf/g (DP arrays), ans (answer). ff: extended forward DP; lg: coefficient
// array for divide-and-conquer. lk: lookup table for constraint-dependent
// multipliers.
int n, m, op[105], f[200005], rf[200005], g[200005], ans;
int ff[200005], lg[200005];
int lk[105][200105];

// Fast input for integer reading.
int dr() {
  int xx = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    ch = getchar();
  while (ch >= '0' && ch <= '9')
    xx = xx * 10 + ch - '0', ch = getchar();
  return xx;
}
// Binomial coefficient C(x, y) = x! / (y! * (x-y)!) mod p.
int C(const int &x, const int &y) {
  return y < 0 || y > x ? 0 : 1ll * jc[x] * ny[y] % p * ny[x - y] % p;
}
int L1[530000], L2[530000];
// Divide-and-conquer forward DP: compute f[i] from extending valid sequences to
// position i.
void work1(int l, int r) {
  if (l == r) {
    // Base case: for positions > m+1, compute f[l] from ff[l]; update ff[l] as
    // normalized coefficient.
    if (l > m + 1)
      f[l] = 1ll * ff[l] * jc[l - 2] % p, ff[l] = 1ll * f[l] * ny[l - 1] % p;
    return;
  }
  int mid = (l + r) >> 1;
  work1(l, mid);
  // Collect extended DP values ff[i] for i in [l, mid] into polynomial L1.
  for (int i = l; i <= mid; i++)
    L1[i - l] = i > m + 1 ? ff[i] : 0;
  for (int i = mid + 1; i <= r; i++)
    L1[i - l] = 0;
  // Collect constraint-dependent coefficients lg[i-l] into polynomial L2.
  for (int i = l; i <= r; i++)
    L2[i - l] = lg[i - l];
  // Multiply L1 * L2 to propagate contributions from [l, mid] to [mid+1, r].
  cheng(L1, L2, r - l + 1, r - l + 1);
  // Update ff[i] for i in [mid+1, r] with convolution result.
  for (int i = mid + 1; i <= r; i++)
    ff[i] += L1[i - l], ff[i] -= ff[i] >= p ? p : 0;
  cle(L1, r - l + 1);
  work1(mid + 1, r);
}
// Divide-and-conquer backward DP: compute g[i] as count of valid continuations
// from position i.
void work2(int l, int r) {
  if (l == r) {
    // Base case: g[1] = 1; for others, normalize g[l] with factorials.
    if (l == 1)
      g[l] = 1;
    else
      g[l] = 1ll * g[l] * jc[l - 2] % p;
    g[l] = 1ll * g[l] * ny[l - 1] % p;
    return;
  }
  int mid = (l + r) >> 1;
  work2(l, mid);
  // Collect g[i] values for i in [l, mid] into polynomial L1.
  for (int i = l; i <= mid; i++)
    L1[i - l] = g[i];
  for (int i = mid + 1; i <= r; i++)
    L1[i - l] = 0;
  // Collect constraint-dependent coefficients into L2.
  for (int i = l; i <= r; i++)
    L2[i - l] = lg[i - l];
  // Multiply L1 * L2 to propagate backward contributions.
  cheng(L1, L2, r - l + 1, r - l + 1);
  // Update g[i] for i in [mid+1, r].
  for (int i = mid + 1; i <= r; i++)
    g[i] += L1[i - l], g[i] -= g[i] >= p ? p : 0;
  cle(L1, r - l + 1);
  work2(mid + 1, r);
}
int main() {
  n = dr(), m = dr();
  // Precompute factorials: jc[i] = i!
  jc[0] = ny[0] = ny[1] = mi[0] = 1;
  for (int i = 1; i <= n; i++)
    jc[i] = 1ll * i * jc[i - 1] % p;
  // Precompute modular inverses of factorials via: ny[i] = (p - p/i) * ny[p%i];
  // then cumulative product.
  for (int i = 2; i <= n; i++)
    ny[i] = 1ll * (p - p / i) * ny[p % i] % p;
  for (int i = 1; i <= n; i++)
    ny[i] = 1ll * ny[i] * ny[i - 1] % p;
  // Precompute powers of 2: mi[i] = 2^i mod p.
  for (int i = 1; i <= n; i++)
    mi[i] = 2ll * mi[i - 1] % p;
  // Precompute lookup table lk[t][i]: constraint-dependent multiplier for
  // constraint group t at index i.
  for (int i = m + 2; i <= n + m - 1; i++) {
    lk[m][i] = mi[i - m - 2];
    // Backward recurrence: compute lk values for earlier constraint groups.
    for (int t = 1; t < m; t++)
      lk[m - t][i - t] = lk[m - t + 1][i - t + 1] - C(i - m - 2, t - 1),
                    lk[m - t][i - t] += lk[m - t][i - t] < 0 ? p : 0;
  }
  // Read m constraint operators: '<' (ascending, op=0) or '>' (descending,
  // op=1).
  for (int i = 1; i <= m; i++) {
    char ch = getchar();
    while (ch != '<' && ch != '>')
      ch = getchar();
    op[i] = ch == '<' ? 0 : 1;
  }
  // Compute forward DP: f[i] = count of valid partial sequences up to position
  // i (for i <= m+1).
  for (int i = 1; i <= m + 1; i++) {
    if (i == 1) {
      f[i] = 1;
      continue;
    }
    // If op[i-1] is descending, no valid transition; f[i] = 0.
    if (!op[i - 1]) {
      f[i] = 0;
      continue;
    }
    f[i] = f[i - 1];
    // Find mid = first position j with ascending op (from right); le = first
    // position with descending op before mid.
    int mid = 0, le = 0;
    for (int j = i - 1; j; j--)
      if (mid == 0) {
        if (!op[j])
          mid = j + 1;
      } else {
        if (op[j]) {
          le = j + 1;
          break;
        }
      }
    if (le == 0)
      le = 1;
    // Add contribution: f[le] * C(i-2, le-1) * C(i-le-2, i-mid-1).
    f[i] = (f[i] +
            1ll * f[le] * C(i - 2, le - 1) % p * C(i - le - 2, i - mid - 1)) %
           p;
  }
  // Extend forward DP: compute ff[i] for positions i > m+1 using precomputed DP
  // values and constraints.
  for (int i = m + 2; i <= n; i++) {
    // Add base contribution from f[m+1] multiplied by binomial and power of 2.
    ff[i] = (ff[i] + 1ll * f[m + 1] * C(i - 2, m) % p *
                         mi[i == m + 2 ? 0 : i - m - 3]) %
            p;
    // Find constraint groups: mid (first ascending), le (first descending
    // before mid).
    int mid = 0, le = 0;
    for (int j = m; j; j--)
      if (mid == 0) {
        if (!op[j])
          mid = j + 1;
      } else if (op[j]) {
        le = j + 1;
        break;
      }
    if (le == 0)
      le = 1;
    // Add constraint-dependent contribution using precomputed lk table or
    // binomials.
    if (mid == m + 1)
      ff[i] = (ff[i] + 1ll * f[le] * C(i - 2, le - 1) % p * lk[le][i]) % p;
    else
      ff[i] = (ff[i] + 1ll * f[le] * C(i - 2, le - 1) % p *
                           C(i - le - 2, i - mid - 1)) %
              p;
  }
  // Normalize ff[i] by dividing by (i-2)!.
  for (int i = m + 2; i <= n; i++)
    ff[i] = 1ll * ff[i] * ny[i - 2] % p;
  // Precompute coefficient array lg[i] for divide-and-conquer polynomial
  // multiplication.
  for (int i = 1; i <= n; i++)
    lg[i] = 1ll * mi[i - 1 - (i > 1 ? 1 : 0)] * ny[i - 1] % p;
  // Execute divide-and-conquer forward and backward DP.
  work1(1, n), work2(1, n);
  // Denormalize g[i] by multiplying by (i-1)!.
  for (int i = 1; i <= n; i++)
    g[i] = 1ll * g[i] * jc[i - 1] % p;
  // Initialize backward reflection: rf[i] = g[n-i+1] for i > m.
  for (int i = m + 1; i <= n; i++)
    rf[i] = g[n - i + 1];
  // Compute backward DP: rf[i] = count of valid continuations from position i
  // (for i <= m).
  for (int i = m; i; i--) {
    // If op[i] is ascending, no valid backward continuation; rf[i] = 0.
    if (op[i]) {
      rf[i] = 0;
      continue;
    }
    rf[i] = rf[i + 1];
    // Find constraint groups: mid (first descending from right), ri (first
    // ascending before mid).
    int mid = 0, ri = 0;
    for (int j = i + 1; j <= m + 1; j++)
      if (mid == 0) {
        if (op[j - 1])
          mid = j - 1;
      } else if (!op[j - 1]) {
        ri = j - 1;
        break;
      }
    if (mid) {
      // If ri found, use binomial formula; else sum over all valid j.
      if (ri)
        rf[i] = (rf[i] + 1ll * rf[ri] * C(n - i - 1, n - ri) % p *
                             C(ri - i - 2, mid - i - 1)) %
                p;
      else
        for (int j = m + 1; j <= n; j++)
          rf[i] = (rf[i] + 1ll * rf[j] * C(n - i - 1, n - j) % p *
                               C(j - i - 2, mid - i - 1)) %
                  p;
    } else
      for (int j = m + 2; j <= n; j++)
        rf[i] = (rf[i] + 1ll * rf[j] * C(n - i - 1, n - j) % p * lk[i][j]) % p;
  }
  // Combine forward and backward DPs: ans = sum over all i of f[i] * rf[i] *
  // C(n-1, i-1).
  for (int i = 1; i <= n; i++)
    ans = (ans + 1ll * f[i] * rf[i] % p * C(n - 1, i - 1)) % p;
  printf("%d", ans);
}

// https://github.com/VaHiX/CodeForces/