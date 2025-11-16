// Problem: CF 1845 F - Swimmers in the Pool
// https://codeforces.com/contest/1845/problem/F

/*
 * Problem: F. Swimmers in the Pool
 * 
 * Purpose: Calculate the number of meeting moments when swimmers are at the same position in a pool,
 *          considering they swim back and forth. This usesFFT-based convolution and inclusion-exclusion
 *          principles to count overlapping swimmer positions efficiently.
 * 
 * Algorithms/Techniques:
 *  - Fast Fourier Transform (FFT) with NTT (Number Theoretic Transform) for polynomial multiplication
 *  - Inclusion-exclusion principle to avoid overcounting
 *  - Modular arithmetic for large numbers
 * 
 * Time Complexity: O(N log N + S log S), where N is the number of distinct speeds (up to 2e5),
 *                   and S is the size of the problem domain (up to 2e5).
 * Space Complexity: O(N + S), for storing arrays of size up to 2^19 and S.
 */

#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
const int N = 1 << 19, S = 2e5 + 4;
int l, t, n, a[N], A[N], B[N], rv[N];
const int M = 998244353, G = 3, I = 332748118;
int myp(int x, int t) {
  int a = 1;
  for (; t; t >>= 1, x = (ll)x * x % M)
    if (t & 1)
      a = (ll)a * x % M;
  return a;
}
void ntt(int *A, int z) {
  for (int i = 0; i < N; i++)
    if (i < rv[i])
      swap(A[i], A[rv[i]]);
  for (int t = 0; t < 19; t++) {
    int W = myp(~z ? G : I, (M - 1) >> (t + 1)), T = 1 << t;
    for (int i = 0; i < N; i += T + T) {
      for (int j = 0, Wn = 1; j < T; j++, Wn = (ll)Wn * W % M) {
        int x = A[i + j], y = (ll)A[i + T + j] * Wn % M;
        A[i + j] = x + y < M ? x + y : x + y - M,
              A[i + T + j] = x - y < 0 ? x - y + M : x - y;
      }
    }
  }
  if (z < 0) {
    int iv = myp(N, M - 2);
    for (int i = 0; i < N; i++)
      A[i] = (ll)A[i] * iv % M;
  }
}
const int P = 1e9 + 7;
bool ok[S * 2];
int dp[S * 2], ans;
int main() {
  cin >> l >> t >> n, l *= 2; // Double length because swimming back and forth
  for (int i = 0; i < n; i++)
    cin >> a[i]; // Read swimmer speeds
  for (int i = 0; i < n; i++)
    A[a[i]]++, B[200000 - a[i]]++; // Use two arrays: one for speed counts, one for reverse speeds
  for (int i = 1; i < N; i++)
    rv[i] = (rv[i >> 1] >> 1) + ((i & 1) << 18); // Precompute bit-reversal indices
  ntt(A, 1), ntt(B, 1); // Apply NTT to both arrays
  for (int i = 0; i < N; i++)
    B[i] = (ll)B[i] * A[i] % M, A[i] = (ll)A[i] * A[i] % M; // Multiply A*A and A*B
  ntt(A, -1), ntt(B, -1); // Perform inverse NTT to get the result
  for (int i = 0; i < n; i++)
    A[a[i] * 2]--; // Subtract self-interactions
  for (int i = 1; i < S * 2; i++)
    if (A[i])
      ok[i] = 1; // Mark valid intervals where overlaps occur
  for (int i = 1; i < S; i++)
    if (B[200000 + i])
      ok[i] = 1; // Check for valid positions based on reverse speeds
  for (int i = 1; i < S * 2; i++)
    for (int j = i + i; j < S * 2; j += i)
      ok[i] |= ok[j]; // Propagate valid flags using inclusion-exclusion
  for (int i = 1; i < S * 2; i++)
    if (ok[i]) {
      if ((dp[i] += (ll)t * i / l % P) >= P)
        dp[i] -= P;
      for (int j = i + i; j < S * 2; j += i)
        if ((dp[j] -= dp[i]) < 0)
          dp[j] += P;
      if ((ans += dp[i]) >= M)
        ans -= P;
    }
  cout << ans; // Output the final answer modulo M
}


// https://github.com/VaHiX/CodeForces/