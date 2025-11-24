// Problem: CF 1392 B - Omkar and Infinity Clock
// https://codeforces.com/contest/1392/problem/B

/*
B. Omkar and Infinity Clock
Algorithms/Techniques: Simulation with cycle detection
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage

The problem involves applying a specific transformation k times to an array:
1. Find maximum value d in the array.
2. Replace each element a[i] with (d - a[i]).

After observing patterns, it becomes clear that after 2 operations, the array will
repeat its state. Therefore, we only need to simulate up to 2 operations regardless
of how large k is.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll mx(-2e18);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      mx = (mx > a[p]) ? mx : a[p]; // Find maximum value in array
    }
    for (ll p = 0; p < n; p++) {
      a[p] = mx - a[p]; // First operation: transform array
    }
    k = (k - 1) % 2; // Reduce k to at most 1 since pattern repeats every 2 steps
    if (k) {
      mx = -2e18;
      for (ll p = 0; p < n; p++) {
        mx = (mx > a[p]) ? mx : a[p]; // Find new maximum value
      }
      for (ll p = 0; p < n; p++) {
        a[p] = mx - a[p]; // Second operation: transform again
      }
    }
    for (ll p = 0; p < n; p++) {
      printf("%lld ", a[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/