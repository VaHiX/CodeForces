// Problem: CF 1704 C - Virus
// https://codeforces.com/contest/1704/problem/C

/*
C. Virus
Purpose: Determine the minimum number of houses that will be infected in the end when optimally protecting uninfected houses to stop virus spread on a circular line of houses.

Algorithm:
- Sort the initially infected houses.
- Compute gaps between consecutive infected houses (considering circular structure).
- For each gap, determine how many houses can be protected to save the maximum number of houses from infection.
- Greedily process the largest gaps first to minimize total infection.

Time Complexity: O(m log m), where m is the number of initially infected houses
Space Complexity: O(m), for storing vectors f and g

Techniques:
- Sorting
- Circular array handling 
- Greedy approach on gap sizes
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> f(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &f[p]);
    }
    sort(f.begin(), f.end()); // Sort infected houses
    std::vector<long> g(m);
    // Compute gaps between consecutive infected houses, including wrap-around gap
    g[0] = (n - f.back() + f[0] - 1);
    for (long p = 1; p < m; p++) {
      g[p] = f[p] - f[p - 1] - 1;
    }
    sort(g.rbegin(), g.rend()); // Sort gaps in descending order to process largest first
    long saved(0);
    for (long p = 0; p < g.size(); p++) {
      g[p] -= 4 * p; // Subtract 4*p because we are choosing the best strategy per gap position
      if (g[p] == 1) { 
        ++saved;
      } else if (g[p] > 1) {
        saved += (g[p] - 1); // Save as many houses as possible in this gap
      } else {
        break; // No more beneficial gaps to process
      }
    }
    printf("%ld\n", n - saved); // Output minimum number of infected houses
  }
}


// https://github.com/VaHiX/codeForces/