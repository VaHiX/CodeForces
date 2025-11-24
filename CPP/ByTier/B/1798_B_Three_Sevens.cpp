// Problem: CF 1798 B - Three Sevens
// https://codeforces.com/contest/1798/problem/B

/*
B. Three Sevens
Purpose: 
  This code solves a greedy matching problem where each day of a lottery 
  has participants, and a winner from each day must be selected such that 
  no participant can win more than once across all days. The goal is to 
  find any valid assignment of winners or determine if it's impossible.
Algorithms/Techniques:
  - Greedy approach
  - Hashing with boolean vector for tracking used numbers
Time Complexity: O(sum of n_i) per test case, where sum of n_i <= 50000
Space Complexity: O(N) where N = 50007 (constant space for fixed-size vectors)
*/

#include <cstdio>
#include <vector>
int main() {
  const long N = 50007; // Fixed size for participant numbers
  long t;
  scanf("%ld", &t);
  while (t--) {
    long m;
    scanf("%ld", &m);
    std::vector<std::vector<long>> v(m); // Store participants per day
    
    // Read input data
    for (long p = 0; p < m; p++) {
      long n;
      scanf("%ld", &n);
      for (long u = 0; u < n; u++) {
        long x;
        scanf("%ld", &x);
        v[p].push_back(x); // Add participant to day p
      }
    }
    
    std::vector<bool> f(N, 0); // Track which numbers are already used
    std::vector<long> w(m, -1); // Store chosen winner for each day
    
    // Process in reverse order (greedy approach from last day)
    for (long p = m - 1; p >= 0; p--) {
      // Traverse all participants of current day
      for (long u = 0; u < v[p].size(); u++) {
        long x = v[p][u];
        
        // If number hasn't been used yet and no winner chosen for this day yet
        if (!f[x] && w[p] < 0) {
          w[p] = x;
        }
        
        f[x] = 1; // Mark number as used
      }
      
      // If we couldn't assign a winner for this day, no solution exists
      if (w[p] < 0) {
        break;
      }
    }
    
    // Output result
    if (w[0] < 0) {
      puts("-1");
    } else {
      for (long p = 0; p < m; p++) {
        printf("%ld ", w[p]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/codeForces/