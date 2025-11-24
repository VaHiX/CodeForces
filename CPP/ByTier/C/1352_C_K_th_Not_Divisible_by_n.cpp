// Problem: CF 1352 C - K-th Not Divisible by n
// https://codeforces.com/contest/1352/problem/C

/*
C. K-th Not Divisible by n
Algorithm: Mathematical approach to find the k-th number not divisible by n.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The idea is to observe that in every block of n consecutive numbers,
exactly (n - 1) are not divisible by n. So we can compute how many full blocks
we need to skip and then find the exact number within the remaining part.

For a given k, we calculate:
- How many full blocks of (n - 1) elements we need to skip: k / (n - 1)
- Then the position within the next block: k % (n - 1)
- Adjust for edge case where k is divisible by (n - 1), which means
  the result lies in the last element of the previous block.

*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld\n", &n, &k);
    // Compute how many full blocks of (n - 1) numbers we skip
    ll res = (k / (n - 1)) * n + (k % (n - 1));
    // Adjust if k is divisible by (n - 1), because in that case the result
    // is one less than what our formula computes (since the last element of
    // a block is divisible by n)
    if (k % (n - 1) == 0) {
      --res;
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/