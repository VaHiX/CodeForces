// Problem: CF 1776 K - Uniform Chemistry
// https://codeforces.com/contest/1776/problem/K

/*
 * Problem: K. Uniform Chemistry
 * Purpose: Calculate the probability that each researcher wins the SWERC prize
 *          when they are independently trying to discover element n through fusion experiments.
 *
 * Approach:
 * - Each researcher starts with an element s[i].
 * - Every year, each researcher fuses their current element a into a random element b from [a+1, n].
 * - The process continues until someone discovers element n.
 * - The solution uses generating functions and numerical approximation techniques to compute
 *   the probability that each researcher discovers element n first.
 *
 * Time Complexity: O(n * A^2) where A = 100 is the number of terms used in the series expansion.
 * Space Complexity: O(n * A) for storing the generating functions and partial sums.
 *
 * Algorithms/Techniques:
 * - Generating Functions
 * - Series Expansion and Partial Sums
 * - Numerical Integration for Power Sums
 * - Fast Exponential Calculation of Series
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#define For(i, a, b) for (int i = a; i <= b; i++)
#define Rev(i, a, b) for (int i = a; i >= b; i--)
#define Fin(file) freopen(file, "r", stdin)
#define Fout(file) freopen(file, "w", stdout)
#define assume(expr)                                                           \
  ((!!(expr)) || (exit((fprintf(stderr, "Assumption Failed: %s on Line %d\n",  \
                                #expr, __LINE__),                              \
                        -1)),                                                  \
                  false))
using namespace std;
#define double long double
const int N = 105;
typedef long long ll;
using Vec = vector<double>;
const int A = 100;
ll nnn;
int n;
Vec F[N], S[N];
const int M = 5e5;
Vec Pre[A];
void InitPowSum() {
  // Precompute power sums for efficient calculation of series
  For(w, 1, A - 1) {
    int sz = M / A;
    Pre[w].resize(sz);
    For(k, 1, sz - 1) Pre[w][k] = Pre[w][k - 1] + pow(k, -1.0L * w);
  }
}
double Powsum(ll t, int w) {
  // Compute sum of k^{-w} for k=1 to t using precomputed values or numerical integration
  if (t == 0)
    return 0.0;
  assume(Pre[w].size());
  if (t < ll(Pre[w].size()))
    return Pre[w][t];
  double a = Pre[w].size() - 0.5, b = t + 0.5;
  double ans = Pre[w].back();
  if (w == 1)
    ans += log(b) - log(a);
  else
    ans += (pow(b, 1.0L - w) - pow(a, 1.0L - w)) / (1.0L - w);
  return ans;
}
Vec Exp(const Vec &f) {
  // Compute exponential of a power series
  Vec g;
  int sz = f.size();
  g.resize(sz);
  g[0] = exp(f[0]);
  For(i, 0, sz - 2) {
    For(j, 0, i) g[i + 1] += (j + 1) * f[j + 1] * g[i - j];
    ;
    g[i + 1] /= (i + 1.0L);
  }
  return g;
}
signed main() {
  InitPowSum();  // Initialize precomputed power sums
  cin >> nnn >> n;  // Read n and m
  For(i, 1, n) {
    ll a;
    cin >> a, a = nnn - a;  // Transform elements to work backwards
    F[i].resize(A);  // Initialize generating function for researcher i
    F[i][0] = -log(a);
    For(w, 1, A - 1) F[i][w] = ((w & 1) ? 1.0L : -1.0L) / w * Powsum(a - 1, w);
    F[i] = Exp(F[i]);  // Exponentiate to get the final generating function
    S[i].resize(A);
    partial_sum(F[i].begin(), F[i].end(), S[i].begin());  // Calculate partial sums
  }
  For(i, 1, n) {
    double ans = F[i][0];  // Start with the first term
    For(j, 1, A - 1) {
      double tt = F[i][j];
      For(k, 1, n) if (k != i) tt *= (1 - S[k][j - 1]);  // Multiply with probabilities of others not winning
      ;
      ans += tt;
    }
    cout << setprecision(20) << fixed << ans << '\n';  // Output the final probability
  }
  cerr << "Time = " << clock() << " ms" << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/