// Problem: CF 1759 B - Lost Permutation
// https://codeforces.com/contest/1759/problem/B

/*
B. Lost Permutation
Algorithm: Greedy + Set Simulation
Time Complexity: O(m + mx) where mx is the maximum element in b
Space Complexity: O(mx) for the boolean vector c

The problem asks whether we can extend a partial permutation with missing elements such that:
1. The sum of the missing elements equals s
2. The extended array becomes a full permutation (containing all integers from 1 to n)

Approach:
- Find the maximum element in the given sequence b, call it mx.
- Create a boolean vector c of size mx+1 to mark which numbers from 1 to mx are already present.
- Calculate how much sum we still need to cover by subtracting the numbers already in b from the ideal sum of 1+2+...+mx.
- If s is less than or equal to this remaining sum, then it's possible to form a permutation.
- If s exceeds what we can achieve with additional elements, we need to check if adding consecutive integers starting from mx+1 can exactly reach s.

The code does the following:
1. Read input values m and s
2. Read sequence b of length m and find maximum element mx
3. Mark elements present in b using boolean array c
4. Compute total sum of missing numbers in range [1, mx]
5. Adjust sum remaining to cover s if possible
6. Greedily add integers from mx+1 upwards to try to match s
7. Output YES if sum becomes 0, otherwise NO
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long m, s;
    scanf("%ld %ld", &m, &s);
    std::vector<long> b(m);
    long mx(0);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &b[p]);
      mx = (mx > b[p]) ? mx : b[p]; // Track maximum element
    }
    std::vector<bool> c(mx + 1, 0); // Boolean vector to mark present elements
    for (long p = 0; p < m; p++) {
      c[b[p]] = 1; // Mark elements that are already present
    }
    for (long p = 1; p < c.size(); p++) {
      if (!c[p]) {
        s -= p; // Subtract sum of missing numbers from the target sum s
      }
    }
    while (s > 0) {
      s -= ++mx; // Greedily add next consecutive integers to reach exact sum s
    }
    puts(s == 0 ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/