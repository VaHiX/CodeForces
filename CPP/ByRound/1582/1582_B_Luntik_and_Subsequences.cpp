// Problem: CF 1582 B - Luntik and Subsequences
// https://codeforces.com/contest/1582/problem/B

/*
B. Luntik and Subsequences
Algorithm: Count subsequences with sum equal to total_sum - 1.
Time Complexity: O(n) per test case.
Space Complexity: O(1).

For each test case:
- Count number of zeros (z) and ones (a) in the array.
- The number of nearly full subsequences is:
  - If there are no zeros, then it's impossible to form a subsequence with sum s-1, so result is 0.
  - Otherwise, the answer is 2^z * a, where:
    - 2^z represents all possible subsets of zeros (each zero can either be included or not in a subsequence).
    - a counts how many ones there are that can contribute to forming the target sum.

This approach works because:
- We must exclude exactly one element from the original array to get sum s-1.
- The only way to do that is by excluding a 1 (if it exists), and then we can include or not include any of the 0s in our subsequence.
*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(0), z(0); // a counts 1s, z counts 0s
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      z += (x == 0); // increment zero counter
      a += (x == 1); // increment one counter
    }
    long long res = (1LL << z) * a; // calculate result using bit shift for 2^z
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/