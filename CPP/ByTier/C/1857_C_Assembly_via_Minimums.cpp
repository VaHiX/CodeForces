// Problem: CF 1857 C - Assembly via Minimums
// https://codeforces.com/contest/1857/problem/C

/*
 * Problem: C. Assembly via Minimums
 * 
 * Purpose: Given a shuffled array of all pairwise minimums of an original array,
 *          reconstruct any possible original array that could have produced it.
 * 
 * Algorithm:
 * - Sort the given array of pairwise minimums.
 * - Construct the original array by taking elements from sorted minimums in a specific pattern.
 *   The idea is to build the array such that the smallest elements are placed first,
 *   and each subsequent element contributes to new pairwise minimums.
 * 
 * Time Complexity: O(n^2 * log(n^2)) due to sorting the array of size n*(n-1)/2,
 *                   and the construction process is O(n).
 * Space Complexity: O(n^2) for storing the array of minimums and the result array.
 * 
 * Techniques:
 * - Sorting
 * - Greedy construction based on pattern of minimums
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long m = n * (n - 1) / 2; // Total number of pairwise minimums
    std::vector<long> v(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the minimums
    long idx(0), step(n - 1); // idx tracks position in sorted array, step decreases each iteration
    std::vector<long> g; // Result array being built
    while (idx < m) {
      g.push_back(v[idx]); // Take the current minimum (smallest unused)
      idx += step; // Move to next set of minimums
      --step; // Reduce step size for next iteration
    }
    g.push_back(g.back()); // Add last element to match size n
    for (long p = 0; p < n; p++) {
      printf("%ld ", g[p]); // Output the reconstructed array
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/