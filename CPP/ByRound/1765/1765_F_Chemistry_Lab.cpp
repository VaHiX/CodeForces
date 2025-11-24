// Problem: CF 1765 F - Chemistry Lab
// https://codeforces.com/contest/1765/problem/F

// # Maximum Expected Profit in Chemistry Lab
// ## Algorithms/Techniques
// - Dynamic Programming with Optimization
// - Sorting and Greedy Approach
// - Mathematical Optimization for Expected Value Calculation
// - Convex Optimization Techniques

// ## Time and Space Complexity
// - **Time Complexity**: O(n²) where n is the number of contracts. This is due to the nested loops in the dynamic programming approach.
// - **Space Complexity**: O(n) for storing the contract information and the DP array.

#include <stdio.h>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5005;
int n;
ld k, f[N];
array<ll, 3> p[N];
int main() {
  cin >> n >> k;
  k /= 100; // Normalize k to be between 0 and 1
  for (int i = 0; i < n; ++i) {
    auto &[x, y, w] = p[i]; // x: concentration, y: contract cost, w: customer price
    scanf("%lld %lld %lld", &x, &w, &y);
  }
  sort(p, p + n); // Sort contracts by concentration
  
  ld ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    f[i] = 0;
    // For each contract i, evaluate all possible subsequent contracts j
    for (int j = i + 1; j < n; ++j) {
      // Calculate profit for choosing contract i followed by contract j
      // This involves computing the expected value of mixing solutions
      f[i] = max(f[i], f[j] + 0.5 * k * (p[j][0] - p[i][0]) * (p[j][1] + p[i][1]) - p[j][2]);
    }
    // The maximum profit is the profit of starting with contract i,
    // minus the cost of signing that contract
    ans = max(ans, f[i] - p[i][2]);
  }
  printf("%0.12f\n", (double)ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/