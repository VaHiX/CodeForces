// Problem: CF 2028 B - Alice's Adventures in Permuting
// https://codeforces.com/contest/2028/problem/B

/*
B. Alice's Adventures in Permuting
Algorithm: Simulation with mathematical analysis of arithmetic progression
Time Complexity: O(1) per test case
Space Complexity: O(1)

The array is defined as a[i] = b*(i-1) + c for i = 1 to n.
We simulate the process where we replace the maximum element with the MEX of the array.
If the array becomes a permutation of [0, ..., n-1], we stop.
If it's impossible, we return -1.

Key observations:
- If b == 0, all elements are equal (c), so MEX is always 0 and simulation fails unless c == 0.
- If b > 0, the array is an arithmetic sequence. We analyze step-by-step how many operations
  are needed for it to become a permutation.
*/
#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, b, c;
    scanf("%lld %lld %lld", &n, &b, &c);
    ll ans(-1);
    if (b) { // If b > 0, array is strictly increasing
      if (c >= n) { // If the first element is >= n, it's already out of valid range
        ans = n;
      } else {
        // Calculate how many operations needed:
        // g represents number of steps until we reduce max to a value in [0,n-1]
        ll g = 1 + (n - c - 1) / b;
        ans = n - (g > 0 ? g : 0);
      }
    } else { // If b == 0, all elements are equal to c
      if (c >= n) {
        ans = n; // Already not valid if c >= n
      } else if (c >= n - 2) {
        ans = n - 1; // Special case when c is close to n-1
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/