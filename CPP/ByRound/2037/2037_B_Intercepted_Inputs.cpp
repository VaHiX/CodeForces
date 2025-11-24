// Problem: CF 2037 B - Intercepted Inputs
// https://codeforces.com/contest/2037/problem/B

/*
Purpose: This program determines possible dimensions (n, m) of a grid based on a shuffled input stream.
         Given k integers, we need to find two integers n and m such that n * m equals the number of unique values
         in the input (excluding duplicates) plus 2, i.e., k - 2 = n * m.

Algorithms/Techniques:
  - Use a set to store unique values and identify duplicates.
  - Iterate through all possible divisors of (k - 2) to find valid n and m.
  - Time complexity: O(k * sqrt(k)) due to checking divisors.
  - Space complexity: O(k) for storing the set of values.

Time Complexity: O(k * sqrt(k)) per test case
Space Complexity: O(k)
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    std::set<long> vs, ds;  // vs: unique values, ds: duplicate values
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      if (vs.count(x)) {
        ds.insert(x);  // If already exists in vs, add to duplicates
      } else {
        vs.insert(x);  // Otherwise, add to unique values
      }
    }
    long target(k - 2), n(-1), m(-1);  // target = total elements - 2 (since one value is repeated twice)
    for (std::set<long>::iterator it = vs.begin(); it != vs.end(); it++) {
      long dv = *it;
      if (!dv || target % dv) {
        continue;  // Skip invalid divisors
      }
      if (dv * dv == target && ds.count(dv)) {  // Check if dv is a perfect square and exists in duplicates
        n = m = dv;
        break;
      } else if (vs.count(target / dv)) {  // Check if complement divisor exists in unique values
        n = dv;
        m = target / dv;
        break;
      }
    }
    printf("%ld %ld\n", n, m);
  }
}


// https://github.com/VaHiX/CodeForces/