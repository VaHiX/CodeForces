// Problem: CF 1614 A - Divan and a Store
// https://codeforces.com/contest/1614/problem/A

/*
 * Problem: A. Divan and a Store
 * Purpose: Maximize the number of chocolate bars Divan can buy within budget,
 *          considering price constraints [l, r].
 *
 * Algorithms/Techniques:
 *   - Filtering valid items based on price range [l, r]
 *   - Sorting valid items in ascending order to use greedy approach
 *   - Greedily selecting cheapest items first until budget runs out
 *
 * Time Complexity: O(n log n) per test case due to sorting step.
 * Space Complexity: O(n) for storing the filtered list of valid items.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, l, r, k;
    scanf("%ld %ld %ld %ld", &n, &l, &r, &k);
    std::vector<long> v; // Vector to store valid chocolate prices in [l, r]
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a < l || a > r) { // Skip items outside the acceptable price range
        continue;
      }
      v.push_back(a); // Add valid item to vector
    }
    sort(v.begin(), v.end()); // Sort prices in ascending order for greedy selection
    long cnt(0);
    for (long p = 0; p < v.size(); p++) {
      if (v[p] > k) { // If current price exceeds remaining budget, stop
        break;
      }
      k -= v[p]; // Deduct the price from budget
      ++cnt; // Increment count of selected bars
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/