// Problem: CF 2124 B - Minimise Sum
// https://codeforces.com/contest/2124/problem/B

/*
B. Minimise Sum

Algorithm:
This problem involves minimizing the sum of prefix minimums in an array after at most one operation.
The key insight is that we can combine two elements (i < j) by setting a[i] = a[i] + a[j] and a[j] = 0.
The goal is to find the optimal pair (i, j) to minimize the total prefix minimum sum.

Approach:
1. For each test case, read the array.
2. The first element a[0] will always contribute to the prefix minimum sum.
3. For the rest of the elements, we compute how combining two elements might reduce the sum.
4. To optimize, we only compare with the current minimum (either previous x or y).
5. If swapping the order of x and y could lead to a better (smaller) result, we do so.

Time Complexity: O(n) per test case, where n is size of array.
Space Complexity: O(1), only fixed extra variables used.

Techniques:
- Greedy approach with careful observation of prefix minimums.
- Single pass through the array with optimized comparisons.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(-1), y(-1);
    scanf("%ld %ld", &x, &y); // Read first two elements
    for (long p = 2; p < n; p++) {
      long z;
      scanf("%ld", &z); // Read remaining elements, but don't use them directly in this version
    }
    printf("%ld\n", x + (x < y ? x : y)); // Output minimum of first two elements as result
  }
}


// https://github.com/VaHiX/codeForces/