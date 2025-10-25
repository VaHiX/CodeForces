// Problem: CF 2066 D1 - Club of Young Aircraft Builders (easy version)
// https://codeforces.com/contest/2066/problem/D1

/*
 * Problem: Club of Young Aircraft Builders (easy version)
 *
 * Purpose:
 *   Given a building with n floors and constraints on how many airplanes must be launched
 *   before residents on each floor can launch their own. The goal is to count the number
 *   of valid ways to fill in the missing data (indicated by 0) in a sequence of airplane launches,
 *   such that all conditions are met.
 *
 * Algorithm:
 *   - Precompute factorials and inverse factorials modulo 1e9 + 7 for combinatorial calculations.
 *   - The problem reduces to choosing which floors launch which airplanes while maintaining
 *     the constraint: at any point, floor i can only launch an airplane if at least c airplanes
 *     have been launched so far from floors 1 to i.
 *   - This becomes a classic ballot problem or ballot-like combinatorics.
 *   - Using inclusion-exclusion or direct combinatorial counting based on valid sequences.
 *
 * Time Complexity: O(MAX + t * m) where MAX = 1e4
 * Space Complexity: O(MAX)
 */

#include <iosfwd>
#include <stdio.h>
using namespace std;

const int MAX = 1e4 + 5;
const int MOD = 1e9 + 7;
int fact[MAX], ifact[MAX];

// Fast multiplication under modulo
inline int mul(int x, int y) { return (long long)x * y % MOD; }

// Precompute factorials and inverse factorials
void init() {
  ifact[1] = 1;
  for (int i = 2; i < MAX; i++)
    ifact[i] = MOD - mul(MOD / i, ifact[MOD % i]); // Using Fermat's little theorem
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < MAX; i++) {
    fact[i] = mul(fact[i - 1], i);          // Compute factorial
    ifact[i] = mul(ifact[i - 1], ifact[i]); // Compute inverse factorial
  }
}

int main() {
  init();
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int N, C, M;
    scanf("%d%d%d", &N, &C, &M);
    // Calculate combination using precomputed factorials and their inverses
    printf("%d\n", mul(fact[C * (N - 1)], mul(ifact[M - C], ifact[C * N - M])));
    // Skip reading the actual array values since all are 0 in this version
    while (M--)
      scanf("%*d");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/