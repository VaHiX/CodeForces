// Problem: CF 1155 C - Alarm Clocks Everywhere
// https://codeforces.com/contest/1155/problem/C

/*
Code Purpose:
This program determines whether it's possible to set an alarm clock such that it rings at all given event times.
The alarm clock has a starting time 'y' and a fixed interval 'p_j' from a list of allowed intervals.
The solution uses the fact that if the alarm rings at times y, y+p, y+2p, ..., then all event times must be congruent to y modulo p.
This allows us to compute the GCD of differences between consecutive events and check if any of the allowed intervals divides this GCD.

Algorithms/Techniques:
- GCD computation using Euclidean algorithm
- Modular arithmetic
- Linear search through allowed interval values

Time Complexity: O(n + m + log(max(x_i))) where n is number of events and m is number of intervals
Space Complexity: O(1) - only using a constant amount of extra space

*/

#include <cstdio>

typedef long long ll;

// Function to compute greatest common divisor
ll gcd(ll a, ll b) { 
    return (b == 0) ? a : gcd(b, a % b); 
}

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  ll start;
  scanf("%lld", &start);
  ll g(0);  // Initialize GCD of differences
  
  // Compute GCD of differences between consecutive event times
  for (ll p = 0; p < n - 1; p++) {
    ll x;
    scanf("%lld", &x);
    g = gcd(g, x - start);  // Update GCD with difference
  }
  
  ll idx(-1), dur(-1);  // Index and duration of valid interval
  
  // Check each allowed interval to see if it divides the GCD
  for (ll p = 1; p <= m; p++) {
    ll h;
    scanf("%lld", &h);
    if (g % h == 0) {  // If current interval divides GCD
      idx = p;         // Store index
      dur = h;         // Store duration
      break;           // Found valid interval, exit loop
    }
  }
  
  // Output result
  if (idx > 0) {
    puts("YES");
    printf("%lld %lld\n", start, idx);
  } else {
    puts("NO");
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/