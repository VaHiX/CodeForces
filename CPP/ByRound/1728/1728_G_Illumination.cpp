// Problem: CF 1728 G - Illumination
// https://codeforces.com/contest/1728/problem/G

/*
 * Problem: G. Illumination
 *
 * Purpose: This code solves a dynamic programming problem where we need to count the number of valid ways
 * to assign power values to lanterns such that all points of interest are illuminated, under the constraint 
 * that each lantern's power is an integer from 0 to d inclusive. Each query adds a new lantern, calculates 
 * the number of valid assignments, then removes the lantern.
 *
 * Algorithms/Techniques:
 * 1. Preprocessing of intervals between consecutive points of interest.
 * 2. Dynamic programming with inclusion-exclusion principle and prefix sums.
 * 3. Efficient processing with segment-based interval counting and update via copying arrays.
 *
 * Time Complexity: O(n * m^2 + q * m^2)
 *   - Precomputation: O(n * m^2) due to nested loops over lanterns and intervals.
 *   - Each query: O(m^2) to compute the DP and reset the working array.
 * Space Complexity: O(m^2)
 *   - Storage for c and d matrices of size (m+2) x (m+2).
 *
 * Input format:
 *   - d, n, m
 *   - n lantern coordinates
 *   - m point of interest coordinates
 *   - q queries (each adding one lantern at coordinate f_i)
 *
 * Output:
 *   - For each query, the number of valid assignments modulo 998244353.
 */

#include <algorithm>
#include <iostream>

using namespace std;
using I = long long;
#define F(i, j, k) for (I i = j; i <= k; i++)
const I P = 998244353, N = 3e5, M = 20;
I c[M][M], d[M][M], D, n, m, a[N], p[M], f[M], x, q;
signed main() {
  cin >> D >> n >> m;
  F(i, 1, n) cin >> a[i];
  F(i, 1, m) cin >> p[i];
  sort(p + 1, p + 1 + m);
  p[0] = -2 * D;
  p[m + 1] = 3 * D;
  F(i, 0, m) fill(c[i] + i, c[i] + m + 2, 1);
  F(L, 0, m)
  F(R, L + 1, m + 1) F(i, 1, n) if (p[L] < a[i] && a[i] < p[R])(
      c[L][R] *= min({a[i] - p[L], p[R] - a[i], D + 1})) %= P;
  F(i, 0, m + 1) copy(c[i], c[i] + 2 + m, d[i]);
  cin >> q;
  while (q--) {
    cin >> x;
    F(L, 0, m)
    F(R, L + 1, m + 1) if (p[L] < x && x < p[R])(
        d[L][R] *= min({x - p[L], p[R] - x, D + 1})) %= P;
    fill(f, f + 2 + m, 0);
    f[0] = P - 1;
    F(i, 1, m + 1) F(j, 0, i - 1)(f[i] += f[j] * (P - 1) % P * d[j][i]) %= P;
    cout << f[m + 1] << endl;
    F(i, 0, m + 1) copy(c[i], c[i] + 2 + m, d[i]);
  }
}


// https://github.com/VaHiX/CodeForces/