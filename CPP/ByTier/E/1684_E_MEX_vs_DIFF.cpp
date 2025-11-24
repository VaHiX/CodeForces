// Problem: CF 1684 E - MEX vs DIFF
// https://codeforces.com/contest/1684/problem/E

/*
 * Problem: E. MEX vs DIFF
 * 
 * Purpose: Given an array of non-negative integers, we can change at most k elements
 * to minimize the difference between DIFF (number of distinct elements) and MEX 
 * (smallest missing non-negative integer). This solution uses a greedy approach
 * to find the optimal assignment of values.
 * 
 * Algorithms:
 * - Greedy selection of elements to minimize cost
 * - Sorting and prefix sum concept to determine how many operations are needed
 * 
 * Time Complexity: O(n * log n) per test case due to sorting and map operations
 * Space Complexity: O(n) for storing the array and auxiliary structures
 */

#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>

using namespace std;
const int N = 1e5 + 2;
int T, n, k, mex, cnt, b[N * 2], m;
map<int, int> p;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    // Reset the auxiliary array b
    for (int i = 0; i <= n; ++i)
      b[i] = 0;
    // Count occurrences of elements <= n in b, others in map p
    for (int i = 1, x; i <= n; ++i) {
      scanf("%d", &x);
      x > n ? ++p[x] : ++b[x];
    }
    // Compute initial mex and count of missing numbers
    for (mex = cnt = 0; cnt <= k && mex <= n; ++mex)
      cnt += !b[mex];
    --mex, m = n, cnt = 0;
    // Transfer elements from map p to array b for processing
    for (auto it = p.begin(); p.size(); it = p.erase(it))
      b[++m] = it->second;
    // Sort the portion of b that represents counts from large values
    sort(b + mex, b + m + 1);
    // Use greedy to decide how many operations to save
    for (int i = mex; i <= m; ++i) {
      k -= b[i];
      if (k < 0)
        ++cnt;
    }
    printf("%d\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/