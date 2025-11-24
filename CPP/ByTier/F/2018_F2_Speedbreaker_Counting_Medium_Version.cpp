// Problem: CF 2018 F2 - Speedbreaker Counting (Medium Version)
// https://codeforces.com/contest/2018/problem/F2

/*
F2. Speedbreaker Counting (Medium Version)
Algorithms/Techniques: Dynamic Programming, Inclusion-Exclusion Principle, Modular Arithmetic

Time Complexity: O(n^3), due to nested loops for computing f[j] and ans[i], as well as inclusion-exclusion calculation.
Space Complexity: O(n^2), because of the arrays f and ans which are of size up to n.

This problem counts the number of valid arrays a such that for each i, city i is conquered no later than time a_i.
It uses dynamic programming with inclusion-exclusion technique on the number of good starting cities k.
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
const int N = 3e3 + 10;
typedef long long ll;
int n, T, mod;
ll sqr(ll x) { return x * x % mod; }
ll ans[N], f[N]; // ans[i]: number of valid arrays with exactly i good starting cities.

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &mod); // Read n and modulo
    for (int i = 1; i <= n; i++) {
      // Reset f array for each i
      for (int j = 1; j < i; j++)
        f[j] = 0;
      f[i] = 1; // Base case: Only one way to conquer city i in step i

      // Compute how many ways there are to reach city i in step i
      for (int j = 1; j <= i; j++)
        f[i] = f[i] * (n - max(j, i - j + 1) + 1) % mod;

      // Transition: compute values for j > i using recurrence relation
      for (int j = i + 1; j <= n; j++)
        f[j] = (2 * (n - (j - 1)) * f[j - 1] +
                sqr(n - (j - 1)) * (mod - f[j - 2])) %
               mod;

      ans[i] = f[n]; // Store result for current i
    }

    // Inclusion-exclusion principle to calculate valid configurations
    for (int i = n; i; i--)
      for (int j = i + 1; j <= n; j++)
        ans[i] = (ans[i] + (mod - ans[j]) * (j - i + 1)) % mod;

    ll s = 1;
    for (int i = 1; i <= n; i++)
      s = s * n % mod; // Total number of possible sequences

    // Subtract invalid ones (those with zero valid starting cities)
    for (int i = 1; i <= n; i++)
      s = (s - ans[i] + mod) % mod;

    printf("%lld ", s); // Print the result for k=0 case

    // Output all valid counts from k=1 to k=n
    for (int i = 1; i <= n; i++)
      printf("%lld%c", ans[i], " \n"[i == n]);
  }
}


// https://github.com/VaHiX/codeForces/