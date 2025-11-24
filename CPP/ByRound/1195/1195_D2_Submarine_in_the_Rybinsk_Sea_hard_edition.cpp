// Problem: CF 1195 D2 - Submarine in the Rybinsk Sea (hard edition)
// https://codeforces.com/contest/1195/problem/D2

/*
 * Problem: D2. Submarine in the Rybinsk Sea (hard edition)
 * Purpose: Calculate sum of function f(ai, aj) for all pairs (i,j) where f is alternating digits of two numbers.
 * Algorithms/Techniques:
 *   - Digit-by-digit processing with modular arithmetic
 *   - Preprocessing and optimization using digit decomposition
 * Time Complexity: O(log(max(a_i)) * n), where log(max(a_i)) represents number of digits
 * Space Complexity: O(n)
 *
 * The algorithm processes each digit level from least significant to most,
 * computes contributions of each digit pair, and accumulates result modulo 998244353.
 */
#include <stdio.h>
#include <algorithm>

using namespace std;
const long long N = 100005, NN = 998244353;
long long n, i, ii, a[N], l = 0, r = 0, m, s = 0, ss = 0, biao;
int main() {
  scanf("%lld", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]); // Read all numbers into array
  sort(a, a + n); // Sort the array for easier processing
  for (ii = 1; a[n - 1]; ii = ii * 100 % NN) { // Process digits from right to left
    biao = 0;
    l = r;
    for (i = r; i < n; i++) {
      ss += a[i] % 10; // Add current digit to sum
      a[i] /= 10;      // Remove last digit
      if (a[i] == 0) { // Check if number has no more digits
        biao = 1;
        r = i + 1;
      }
    }
    s = (s + ss * ii * 11 % NN * (n - l)) % NN; // Accumulate contribution of current digit level
    ss = 0;
    if (biao) { // If we've reached end of digits for some numbers
      for (i = r; i < n; i++)
        ss += a[i]; // Sum remaining digits for those numbers
      s = (s + ss % NN * (ii * 200 % NN) * (r - l)) % NN; // Add their contribution
      ss = 0;
    }
  }
  printf("%lld\n", s);
}


// https://github.com/VaHiX/codeForces/