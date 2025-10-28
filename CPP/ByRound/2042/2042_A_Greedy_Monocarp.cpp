// Problem: CF 2042 A - Greedy Monocarp
// https://codeforces.com/contest/2042/problem/A

/*
 * Problem: Greedy Monocarp
 * 
 * Purpose: Given n chests with initial coin counts and a target k,
 *          we must add minimum coins such that when greedy Monocarp
 *          takes chests in descending order of coin count until total
 *          reaches at least k, he ends up with exactly k coins.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: Sort chests in descending order to simulate
 *     Monocarp's selection process
 *   - Preprocessing: Check if any chest already has >= k coins or sum >= k
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for the vector storing chest values
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(n);
    long sum(0), mx(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      mx = (mx > v[p] ? mx : v[p]); // Track maximum coin count in chests
      sum += v[p];                  // Compute total coins
    }
    if (mx >= k) {
      puts("0");                    // No need to add more if max already meets or exceeds k
      continue;
    } else if (sum <= k) {
      printf("%ld\n", k - sum);     // Add difference to reach exactly k
      continue;
    }
    sort(v.rbegin(), v.rend());     // Sort in descending order to simulate greedy selection
    long cs(0), res(0);
    for (long p = 0; p < v.size(); p++) {
      cs += v[p];                   // Accumulate coins taken by Monocarp
      if (cs > k) {
        break;                      // Stop when excess coins are accumulated
      }
      res = k - cs;                 // Minimum coins needed to reach exactly k
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/