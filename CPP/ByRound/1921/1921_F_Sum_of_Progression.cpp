// Problem: CF 1921 F - Sum of Progression
// https://codeforces.com/contest/1921/problem/F

/*
 * Problem: F. Sum of Progression
 * 
 * Purpose: 
 *   Given an array of n numbers and q queries, each query asks for a sum of elements 
 *   in an arithmetic progression starting at index s, step size d, with k elements.
 *   The sum is computed by multiplying each element by its position in the sequence.
 * 
 * Techniques:
 *   - Preprocessing with prefix sums for optimization.
 *   - Optimization based on step size: for small steps (d < M), use optimized prefix sums;
 *     for large steps (d >= M), compute directly.
 * 
 * Time Complexity: O(n * M + q * sqrt(n)) where M = 333
 * Space Complexity: O(n + q)
 */
#include <algorithm>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(a, b) memset((a), (b), sizeof(a))
const LL INF = 1e9 + 7;
const int N = 2e5 + 10;
const int M = 333;
vector<tuple<int, int, int>> vp[N]; // Store queries grouped by step size 'd'
LL sum1[N]; // Prefix sum of array elements
LL sum2[N]; // Prefix sum of (a[i] * (i / d)) for optimization
int a[N]; // Input array
LL ans[N]; // Result array for queries

// Helper function to calculate range sum using prefix sums
LL getsum(LL sum[], int l, int r) {
  LL ans = sum[r];
  if (l >= 0)
    ans -= sum[l];
  return ans;
}

int main() {
  int ncase;
  scanf("%d", &ncase);
  while (ncase--) {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
      vp[i].clear(); // Clear previous queries
    for (int i = 1; i <= q; i++) {
      int s, d, k;
      scanf("%d%d%d", &s, &d, &k);
      int l = s;
      int r = s + (k - 1) * d;
      vp[d].emplace_back(l, r, i); // Group queries by step size
    }
    
    // Process queries where d is small (less than M)
    for (int d = 1; d < M && d <= n; d++) {
      if (vp[d].empty())
        continue;
      // Build prefix sums for optimized calculation
      for (int i = 1; i <= n; i++) {
        sum1[i] = a[i];
        sum2[i] = 1LL * a[i] * (i / d);
        if (i >= d) {
          sum1[i] += sum1[i - d];
          sum2[i] += sum2[i - d];
        }
      }
      // Process all queries for this step size
      for (auto &[l, r, id] : vp[d]) {
        LL res1 = getsum(sum1, l - d, r); // Sum of elements
        LL res2 = getsum(sum2, l - d, r); // Weighted sum of elements
        ans[id] = res2 - (l / d - 1) * res1; // Final formula for sum of weighted terms
      }
    }
    
    // Process queries where d is large (>= M)
    for (int d = M; d <= n; d++) {
      for (auto &[l, r, id] : vp[d]) {
        LL tot = 0;
        int cur = 1;
        // Direct calculation for large step size
        while (l <= r) {
          tot += 1LL * a[l] * cur++;
          l += d;
        }
        ans[id] = tot;
      }
    }
    
    // Output results for the current test case
    for (int i = 1; i <= q; i++) {
      printf("%lld ", ans[i]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/