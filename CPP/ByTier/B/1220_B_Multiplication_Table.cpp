// Problem: CF 1220 B - Multiplication Table
// https://codeforces.com/contest/1220/problem/B

/*
B. Multiplication Table
Algorithm: Restore sequence a such that M[i][j] = a[i] * a[j]
Techniques: Math, Square Root
Time Complexity: O(n^2)
Space Complexity: O(n^2)

The problem provides an n x n multiplication table where M[i][j] = a[i] * a[j].
We know that:
- M[0][0] = a[0]^2
- M[1][0] = a[1] * a[0]
- M[2][0] = a[2] * a[0]

From these relationships we derive:
- x = sqrt(M[1][0] * M[2][0] / M[1][2]) gives us a[0]
- For each column j, a[j] = M[0][j] / a[0]

We reconstruct the first row (a[0], ..., a[n-1]) using this algorithm.
*/

#include <cmath>
#include <cstdio>
#include <vector>
typedef long long ll;

ll gcd(ll a, ll b) {
  return (b == 0) ? a : gcd(b, a % b);
}

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<std::vector<ll>> m(n, std::vector<ll>(n, 0));
  
  // Read the multiplication table
  for (ll row = 0; row < n; row++) {
    for (ll col = 0; col < n; col++) {
      scanf("%lld", &m[row][col]);
    }
  }

  // Calculate a[0] using the formula derived from M[1][0], M[2][0], and M[1][2]
  ll x = sqrt(m[1][0] * m[2][0] / m[1][2]); // This computes a[0]
  
  printf("%lld ", x); // Print a[0]

  // Compute the rest of the elements using a[j] = M[0][j] / a[0]
  for (ll col = 1; col < n; col++) {
    printf("%lld ", m[0][col] / x);
  }
  
  puts(""); // Print newline
  return 0;
}


// https://github.com/VaHiX/codeForces/