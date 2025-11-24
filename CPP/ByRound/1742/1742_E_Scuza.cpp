// Problem: CF 1742 E - Scuza
// https://codeforces.com/contest/1742/problem/E

/*
Code Purpose:
This solution efficiently handles multiple queries about the maximum height Timur can reach when climbing a staircase, given that his leg length determines which steps he can climb. The approach uses prefix sums for fast height calculation and binary search to quickly determine how many steps can be climbed for each query.

Algorithms/Techniques:
- Prefix Sum Array: To quickly compute cumulative heights.
- Binary Search: To find the maximum number of steps that can be climbed for a given leg length.
- Preprocessing: To keep track of the maximum height at each step and the corresponding index.

Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    std::vector<ll> a(n + 1, 0), b(n + 1, 0), c(1, 0), d(1, 0);
    // Build prefix sum array 'b' and maintain monotonic increasing max heights 'c' with indices 'd'
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &a[p]);
      b[p] = b[p - 1] + a[p]; // Prefix sum of heights
      if (a[p] > c.back()) {
        c.push_back(a[p]); // Maintain strictly increasing max heights
        d.push_back(p);    // Store the step index corresponding to this max height
      }
    }
    c.push_back(2e9); // Sentinel value to avoid boundary checks
    d.push_back(n + 1); // Sentinel index
    while (q--) {
      ll k;
      scanf("%lld", &k);
      ll left(0), right(c.size() - 1), res(0);
      // Binary search on max height that can be climbed
      while (left <= right) {
        ll mid = (left + right) / 2;
        ll chk = c[mid];
        if (k < chk) {
          res = b[d[mid] - 1]; // Height reached before this step
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      }
      printf("%lld ", res);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/