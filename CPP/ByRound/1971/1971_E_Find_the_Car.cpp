// Problem: CF 1971 E - Find the Car
// https://codeforces.com/contest/1971/problem/E

/*
E. Find the Car

Purpose:
This program processes multiple test cases where each case defines a car's travel on a number line from 0 to n.
The car's position and time are known at k+1 checkpoints (including start and end).
Between any two points, the speed is constant. For each query, we determine the time it takes to reach a certain distance d.

Algorithms:
- Binary search using std::upper_bound for efficient lookup of the correct segment.
- Linear interpolation between known time points for computing intermediate times.

Time Complexity: O(k log k + q log k) per test case
Space Complexity: O(k) per test case

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k, q;
    scanf("%lld %lld %lld", &n, &k, &q);
    
    // Store positions and times
    std::vector<ll> a(k + 1, 0), b(k + 1, 0);
    
    // Read positions
    for (ll p = 1; p <= k; p++) {
      scanf("%lld", &a[p]);
    }
    
    // Read times
    for (ll p = 1; p <= k; p++) {
      scanf("%lld", &b[p]);
    }
    
    // Process queries
    for (ll p = 0; p < q; p++) {
      ll d;
      scanf("%lld", &d);
      
      // If query point is exactly at the final destination
      if (d == n) {
        printf("%lld ", b.back());
        continue;
      }
      
      // Find the index of the first element in 'a' greater than 'd'
      ll idx = std::upper_bound(a.begin(), a.end(), d) - a.begin();
      
      // Interpolate time using the formula:
      // t = t1 + (t2 - t1) * (d - d1) / (d2 - d1)
      printf("%lld ", b[idx - 1] + (b[idx] - b[idx - 1]) * (d - a[idx - 1]) /
                                       (a[idx] - a[idx - 1]));
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/