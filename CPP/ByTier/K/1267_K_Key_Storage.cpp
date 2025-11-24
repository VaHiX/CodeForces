// Problem: CF 1267 K - Key Storage
// https://codeforces.com/contest/1267/problem/K

/*
K. Key Storage
Algorithms/Techniques: Combinatorics, Number Theory, Multiset Representation, Preprocessing

The problem involves calculating how many other keys produce the same fingerprint as a given key.
A fingerprint is computed by repeatedly dividing the number by increasing integers starting from 2,
collecting remainders until reaching 0.
The task reduces to counting how many numbers produce the same multiset of remainders.

Time Complexity: O(T * log^2(K) + MAX_N^2), where T is the number of test cases and K is the maximum key value.
Space Complexity: O(MAX_N^2), for precomputed binomial coefficients.

This problem essentially computes a "multinomial coefficient" that counts arrangements
of remainders. It uses:
1. Preprocessing to build combinatorial table (binomial coefficients)
2. Decomposing input number into its representation using division by 2,3,4,...
3. Using multinomial coefficients to count how many other numbers map to same pattern.
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

#define int long long
using namespace std;
int i, j, k, T, x, s, p, c[23][23], f[23];
void solve() {
  for (i -= 2, j = 1; i >= 0; i--, j++) {
    if (!i)
      j--;
    s *= c[j][f[i]], j -= f[i]; // Compute multinomial coefficient using precomputed combinations
  }
  return;
}
signed main() {
  scanf("%lld", &T);
  for (i = c[0][0] = 1; i < 21; i++)
    for (c[i][0] = j = 1; j <= i; j++)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j]; // Precompute binomial coefficients
  while (T--) {
    memset(f, 0, sizeof(f)); // Reset frequency array for current test case
    scanf("%lld", &x);
    i = 2;
    s = 1;
    p = 0;
    while (x) {
      f[x % i]++; // Decompose number into remainders when divided by 2, 3, 4, ...
      x /= i;
      i++;
    }
    k = i;
    for (i -= 2, j = 1; i >= 0; i--, j++) {
      if (!i)
        j--;
      s *= c[j][f[i]]; // Calculate total permutations of current remainder combination
      j -= f[i];
    }
    i = k - 1;
    f[0]--; // Adjust for special case: avoid over-counting one arrangement
    if (!f[k - 2])
      for (p = 1, i -= 2, j = 1; i >= 0; i--, j++) {
        if (!i)
          j--;
        p *= c[j][f[i]]; // Compute second term in subtraction for final answer
        j -= f[i];
      }
    printf("%lld\n", s - p - 1); // Output number of other keys with same fingerprint
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/