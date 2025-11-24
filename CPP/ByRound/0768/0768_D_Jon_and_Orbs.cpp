// Problem: CF 768 D - Jon and Orbs
// https://codeforces.com/contest/768/problem/D

/*
Code Purpose:
This program calculates the minimum number of days Jon Snow needs to wait to collect at least one of each of k types of orbs with a probability of at least p (scaled by a factor of 2000). It uses dynamic programming to compute the probability of collecting all k types of orbs in t days, then answers queries using binary search on the precomputed probabilities.

Algorithms/Techniques:
- Dynamic Programming (DP) with states f[u][t] = probability of collecting exactly u unique orb types in t days
- Binary search to find the minimum t such that the probability >= p

Time Complexity: O(k * D) for DP computation + O(q * log D) for queries
Space Complexity: O(k * D) for the DP table and O(D) for the probability array g
Where D = 10 * k (predefined maximum days), k is number of orb types, q is number of queries
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const double eps = 1e-7;  // Small epsilon for precision
  const double DIV = 2000;  // Scaling factor for probability input
  long k, q;
  scanf("%ld %ld", &k, &q);
  long D = 10 * k;  // Set maximum possible days based on k
  std::vector<std::vector<double>> f(k + 1, std::vector<double>(D, 0));  // DP table: f[u][t] = prob of u unique orbs in t days
  f[0][0] = 1;  // Base case: 0 orbs in 0 days = 100% probability
  for (long u = 1; u <= k; u++) {  // For each number of unique orbs from 1 to k
    for (long t = 1; t < D; t++) {  // For each day from 1 to D
      // Transition: either get a new orb (u orbs, t-1 days) or repeat an old one (u-1 orbs, t-1 days)
      f[u][t] = (1.0 * u / k) * f[u][t - 1] +
                (1 - 1.0 * (u - 1.0) / k) * f[u - 1][t - 1];
    }
  }
  std::vector<double> g(D);  // Store cumulative probability of collecting all k orbs by day t
  for (long p = 0; p < D; p++) {
    g[p] = f[k][p];  // f[k][p] is prob of collecting all k orbs by day p
  }
  while (q--) {  // Process each query
    double prob;
    scanf("%lf", &prob);
    prob /= DIV;  // Scale probability to actual value
    std::vector<double>::iterator it =  // Find first day where cumulative probability >= input prob
        std::lower_bound(g.begin(), g.end(), prob);
    printf("%ld\n", (it - g.begin()));  // Output the minimum number of days
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/