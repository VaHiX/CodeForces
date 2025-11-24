// Problem: CF 1614 D1 - Divan and Kostomuksha (easy version)
// https://codeforces.com/contest/1614/problem/D1

/*
Purpose: This program finds the maximum value of the sum of GCDs of prefixes of an array after reordering the elements.

Algorithms/Techniques:
- Sieve-like preprocessing to count multiples of each number
- Dynamic Programming on divisors to compute optimal prefix GCD sum
- Reordering strategy: place larger numbers first to maximize early GCD values

Time Complexity: O(M log M + n) where M = 5 * 10^6
Space Complexity: O(M) for the arrays e, f, and d

*/
#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;
int const M = 5000000;
int i, j, n, s, x, e[M + 100], f[M + 100], d[M + 100];
signed main() {
  scanf("%lld", &n);
  // Read input and count frequency of each element
  for (i = 1; i <= n; i++)
    scanf("%lld", &x), f[x]++;
  
  // Preprocessing: e[i] stores count of multiples of i in the array
  for (i = 1; i <= M; i++)
    for (j = i; j <= M; j += i)
      e[i] += f[j];
  
  // Dynamic Programming from largest to smallest divisor
  // d[i] represents maximum possible sum when first element has GCD i
  for (i = M; i > 0; i--) {
    for (s = 0, j = i * 2; j <= M; j += i)
      s = max(s, d[j] - e[j] * i); // s keeps track of best gain from smaller divisors
    d[i] = e[i] * i + s; // d[i] stores max value when GCD starts with i
  }
  
  printf("%lld\n", d[1]); // Result is the maximum value achievable with GCD starting from 1
  return 0;
}


// https://github.com/VaHiX/CodeForces/