// Problem: CF 1712 A - Wonderful Permutation
// https://codeforces.com/contest/1712/problem/A

/*
 * Problem: A. Wonderful Permutation
 * Algorithm: Greedy approach to minimize the sum of first k elements in a permutation
 * Time Complexity: O(n) per test case, where n is the length of the permutation
 * Space Complexity: O(1), only using a constant amount of extra space
 *
 * Approach:
 * - For each test case, we want to minimize the sum of the first k elements.
 * - We iterate through the first k elements and count how many of them are greater than k.
 * - Each such element needs to be swapped out with an element that is <= k.
 * - The number of such swaps needed equals the count of elements > k in first k positions.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long cnt(k); // Initialize counter to k, as we will decrement it for elements <= k in first k positions
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p >= k) {
        // Only process the first k elements to determine how many need to be replaced
        continue;
      }
      if (x <= k) {
        // If current element is <= k, we can use it in front part (reduce counter)
        --cnt;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/