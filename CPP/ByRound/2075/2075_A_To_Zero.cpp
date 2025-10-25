// Problem: CF 2075 A - To Zero
// https://codeforces.com/contest/2075/problem/A

/*
 * Problem: A. To Zero
 * Purpose: Given two integers n and k (k is an odd number >= 3), find the minimum 
 *          number of operations to reduce n to 0 by subtracting values from [1, k] 
 *          under parity constraints (even n requires even x, odd n requires odd x).
 *
 * Algorithm:
 * - Greedy approach: If n <= k, we can subtract directly with one operation.
 * - Otherwise, since k is odd and we must maintain parity during each step:
 *   - Odd numbers require odd subtractions; even numbers require even subtractions.
 *   - To minimize operations, greedily use the largest possible x (i.e., k) when 
 *     possible.
 * - For odd n: subtract k and reduce to even, then proceed in pairs.
 * - For even n: subtract k from large enough n values until remainder is small.
 * - The formula derived from pattern analysis:
 *   result = (n + k - 3) / (k - 1)
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", (n + k - 3) / (k - 1)); // Key formula for minimum operations
  }
}


// https://github.com/VaHiX/codeForces/