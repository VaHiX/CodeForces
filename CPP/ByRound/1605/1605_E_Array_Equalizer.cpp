// Problem: CF 1605 E - Array Equalizer
// https://codeforces.com/contest/1605/problem/E

/*
Algorithm: Number Theoretic Transform, Prefix Sum, Binary Search
Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

This code solves the problem of converting array 'a' to array 'b' using specific operations.
The key insight is to use Mobius inversion and prefix sums to efficiently answer queries
about the minimum operations needed for different guesses of b[1].

The approach involves:
1. Transforming the problem using mobius function
2. Preprocessing prefix sums for efficient range queries
3. For each query, using binary search to find optimal solution
*/

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
enum { N = 200009 };
int mu[N]; // Mobius function array
long long a[N], v[N], w[N], z; // Temporary arrays for computation
int main() {
  int n, m, i, j;
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> n, i = 1; i <= n; ++i)
    cin >> a[i];
  for (i = 1; i <= n; ++i)
    cin >> j, a[i] = (i == 1 ? 0 : j) - a[i]; // Adjusting values based on b[1] being unknown
  for (mu[1] = i = 1; i <= n; ++i) {
    for (j = i + i; j <= n; j += i)
      mu[j] -= mu[i], a[j] -= a[i]; // Apply mobius inversion and accumulate differences
    mu[i] ? v[++*v] = a[i] / mu[i] : z += abs(a[i]); // Store transformed values or accumulate absolute values
  }
  sort(v + 1, v + *v + 1), partial_sum(v + 1, v + *v + 1, w + 1); // Sort and compute prefix sums
  for (cin >> m; m--;
       cout << z - 1ll * i * j - w[j] + 1ll * i * (*v - j) + w[*v] - w[j]
            << '\n') // Output answer for each query using precomputed values
    cin >> i, j = upper_bound(v + 1, v + *v + 1, -i) - v - 1; // Find position using binary search
}


// https://github.com/VaHiX/CodeForces/