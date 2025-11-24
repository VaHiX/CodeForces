// Problem: CF 1931 B - Make Equal
// https://codeforces.com/contest/1931/problem/B

/*
B. Make Equal
Algorithms/Techniques: Simulation with prefix sum
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

The problem asks whether we can make all containers have equal water amounts using operations that allow pouring water from container i to container j where i < j. 
This is possible if and only if the cumulative excess water (relative to average) never becomes negative when traversing from left to right.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    ll s(0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      s += a[p];
    }
    ll g = s / n; // Target amount of water in each container
    bool possible(true);
    ll cur(0); // Cumulative excess water from left to right
    for (long p = 0; possible && p < n; p++) {
      cur += (a[p] - g); // Add the excess or deficit at current position
      if (cur < 0) {     // If we ever go negative, it's impossible
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/