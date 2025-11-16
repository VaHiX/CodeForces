// Problem: CF 2029 A - Set
// https://codeforces.com/contest/2029/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, k;
    scanf("%ld %ld %ld", &l, &r, &k);
    long res = (r / k) - l + 1;
    printf("%ld\n", res > 0 ? res : 0);
  }
}
/*
Flowerbox:
Problem: Maximum Operations on a Set of Integers
Purpose: Given a range [l, r] and a value k, determine the maximum number of operations 
         where each operation removes an element x from the set such that there are at least k multiples of x in the set.

Algorithms/Techniques:
  - Greedy approach with mathematical insight using divisibility
  - Key idea: For each number x in the range, count how many multiples of x exist
    within [l, r]. If this count is at least k, then x can be chosen for an operation.
  - Optimized counting via integer division:
    Number of multiples of x in [l, r] = floor(r / x) - floor((l - 1) / x)
    But since we're choosing a representative element per group of size k, a simpler approach works.

Time Complexity: O(1)
Space Complexity: O(1)

The solution simplifies the logic by realizing that for maximum operations:
We can greedily select numbers in increasing order and remove them if they have at least k multiples.
A simplified formula computes result directly as (r / k) - l + 1, which is derived from 
grouping strategy over the range [l, r].
*/

// https://github.com/VaHiX/codeForces/