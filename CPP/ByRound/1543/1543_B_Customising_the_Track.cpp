// Problem: CF 1543 B - Customising the Track
// https://codeforces.com/contest/1543/problem/B

/*
B. Customising the Track

Purpose:
This code solves the problem of minimizing the "inconvenience" of a traffic track, 
which is defined as the sum of absolute differences between all pairs of sub-track car counts.
We are allowed to move cars between sub-tracks to minimize this value.

Algorithm/Technique:
The key insight is that to minimize the sum of absolute differences, we want all values to be as close to each other as possible.
If we can redistribute the total number of cars evenly among the sub-tracks, then the optimal solution occurs when:
- Each sub-track has either floor(total/n) or ceil(total/n) cars.
- The inconvenience is minimized to m * (n - m), where m = total % n.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cstdio>
typedef long long ll;

int main() {
  long t;                           // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n;                           // Number of sub-tracks
    scanf("%lld", &n);
    ll s(0);                        // Total sum of cars
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      s += x;                       // Accumulate total number of cars
    }
    ll m = s % n;                   // Remainder when dividing total by n
    printf("%lld\n", m * (n - m));  // Minimum inconvenience formula
  }
}


// https://github.com/VaHiX/codeForces/