// Problem: CF 1863 C - MEX Repetition
// https://codeforces.com/contest/1863/problem/C

/*
C. MEX Repetition
Algorithms/Techniques: Simulation with cycle detection and modular arithmetic
Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem involves applying a specific operation k times on an array of distinct integers from 0 to n.
Each operation replaces each element with the MEX (Minimum EXcluded) of the entire array.
After some iterations, the sequence of arrays starts repeating in a cycle.
We use this periodicity to avoid simulating all k operations when k is large.
Instead, we simulate up to n+1 steps (since there are at most n+1 distinct states), and then compute
the final state using modular arithmetic based on the cycle length.
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
    std::vector<ll> a(n + 1); // Extra element to store MEX value
    a[n] = n * (n + 1) / 2;   // Initialize with sum of 0..n, which will be reduced by current elements
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      a[n] -= a[p];          // Subtract current element from total sum to get MEX
    }
    k %= (n + 1);            // Reduce k using cycle length
    for (ll p = 0; p < n; p++) {
      printf("%lld ", a[(p - k + n + 1) % (n + 1)]);  // Use modular arithmetic to get correct index
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/