// Problem: CF 479 E - Riding in a Lift
// https://codeforces.com/contest/479/problem/E

/*
E. Riding in a Lift

Purpose:
This code calculates the number of distinct sequences of floor numbers that can be visited in exactly k trips
in a building with n floors, starting from floor a and avoiding floor b (which has a secret lab).
Each move must satisfy the condition that the distance to the next floor is strictly less than the distance to floor b.

Algorithms:
- Dynamic Programming with state compression.
- For each step (trip), we compute valid transitions based on current positions.
- The transition uses prefix sums and modular arithmetic to efficiently count valid paths.
- We track transitions using two arrays: f (current) and g (next).

Time Complexity: O(n * k)
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll M = 1000000007; // Modulo value for large results
  ll n, a, b, k;
  scanf("%lld %lld %lld %lld", &n, &a, &b, &k);
  
  // Optimize: ensure a <= b for easier handling
  if (a > b) {
    a = n - a + 1;
    b = n - b + 1;
  }
  
  // f and g arrays represent the number of ways to reach each floor at current and next step
  std::vector<ll> f(b), g(b);
  
  // Initialize: start at floor a
  f[a] = 1;
  
  // Perform k steps (trips)
  for (int step = 0; step < k; step++) {
    // g[p] = total ways to reach p minus the number of ways that were already counted (f[p])
    for (int p = 1; p < b; p++) {
      g[p] = (M - f[p]) % M;
    }
    
    // Prefix sum: f[p] accumulates all previous values up to p
    for (int p = 1; p < b; p++) {
      f[p] += f[p - 1];
      f[p] %= M;
    }
    
    // g[p] = updated ways to reach floor p, considering valid neighbors based on the constraint
    for (int p = 1; p < b; p++) {
      g[p] += f[(p + b - 1) / 2];  // Add number of paths to a specific floor determined by formula
      g[p] %= M;
    }
    
    // Swap arrays: move to next step
    std::vector<ll> temp = f;
    f = g;
    g = temp;
  }
  
  // Sum all the ways to reach any valid floor (excluding b)
  ll total(0);
  for (int p = 1; p < b; p++) {
    total += f[p];
    total %= M;
  }
  
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/