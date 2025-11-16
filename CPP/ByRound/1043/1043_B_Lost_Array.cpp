// Problem: CF 1043 B - Lost Array
// https://codeforces.com/contest/1043/problem/B

/*
B. Lost Array
Purpose:
  Given an array 'a' of length n+1 where a_0 = 0 and a_i = x_{(i-1)%k} + a_{i-1} for i > 0,
  find all possible values of k (length of the original array x).

Algorithm:
  - Compute differences d[i] = a[i+1] - a[i] for all valid i.
  - For each candidate k from 1 to n:
    * Check if the sequence d[0..n-1] has period k by comparing elements at intervals.
    * If valid, add k to results.
  - Add n to the result list (always valid).
  
Time Complexity: O(n^3)
Space Complexity: O(n)

Techniques:
  - Difference array technique
  - Period detection in sequences
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0); // Array a of size n+1 initialized to 0
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]); // Read values of a[1] to a[n]
  }
  std::vector<long> d(n); // Compute differences d[i] = a[i+1] - a[i]
  for (long p = 0; p < n; p++) {
    d[p] = a[p + 1] - a[p];
  }
  std::vector<long> res; // Store possible values of k
  for (long g = 1; g < n; g++) { // Try each possible period length from 1 to n-1
    bool possible(true);
    for (long u = 0; u + g < n; u++) { // Check if pattern repeats with period g
      if (d[u] != d[u + g]) {
        possible = false;
        break;
      }
    }
    if (possible) {
      res.push_back(g); // Add valid period length to result list
    }
  }
  res.push_back(n); // n is always a valid answer
  printf("%ld\n", res.size());
  for (long p = 0; p < res.size(); p++) {
    printf("%ld ", res[p]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/