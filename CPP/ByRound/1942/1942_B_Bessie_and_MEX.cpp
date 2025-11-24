// Problem: CF 1942 B - Bessie and MEX
// https://codeforces.com/contest/1942/problem/B

/*
Bessie and MEX

Algorithm:
This problem involves reconstructing a permutation from a given array 'a' where each element of 'a' is defined as:
a[i] = MEX(p[0..i]) - p[i]
We need to reconstruct a valid permutation 'p' such that the above condition holds.

Approach:
- For each position i, we compute p[i] using the relation: p[i] = MEX(p[0..i-1]) - a[i]
- We maintain a boolean vector m to keep track of which numbers are present in current prefix
- We also maintain a variable 'mex' that represents the minimum excluded value
- For every new element, we update the mex by checking if it's already present in the set
- This is a greedy approach where at each step we compute the valid value for p[i]

Time Complexity: O(n) amortized per test case. Although there's an inner while loop, over all operations,
                 each number from 0 to n is visited once, so total complexity is linear.

Space Complexity: O(n). We use vectors of size n to store the permutation and membership information.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<bool> m(n, 0); // Tracks which numbers are currently in the prefix
    std::vector<long> v(n);    // Stores the result permutation
    long mex(0);               // Current MEX value, starts at 0
    for (int p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      // Compute value of p[i] using the inverse of the formula: p[i] = MEX - a[i]
      v[p] = mex - (a < 0 ? a : 0);
      m[v[p]] = 1;              // Mark this value as seen
      while (m[mex]) {          // Update mex to smallest missing non-negative integer
        ++mex;
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/