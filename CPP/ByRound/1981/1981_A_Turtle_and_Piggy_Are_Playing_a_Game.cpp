// Problem: CF 1981 A - Turtle and Piggy Are Playing a Game
// https://codeforces.com/contest/1981/problem/A

/*
 * Problem: A. Turtle and Piggy Are Playing a Game
 * Purpose: Find the maximum score achievable by repeatedly dividing a number x in range [l, r] 
 *          by its smallest prime factor until x becomes 1.
 * 
 * Algorithm/Techniques:
 *   - The maximum number of operations is determined by the number of times we can divide 
 *     by the smallest possible prime factor (2) before reaching 1.
 *   - For any number in range [l, r], if we want to maximize operations, we should choose 
 *     the largest number with the most factors of 2 (i.e., x = 2^k where 2^k <= r).
 *   - The number of times we can divide by 2 is simply log2(r) + 1 if we consider all 2-powers,
 *     but since the number must be in [l, r] and 2*l <= r, the actual answer is the maximum 
 *     power of 2 that fits into [l, r], which simplifies to finding how many times you can 
 *     double before exceeding r.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long cnt(0);          // Counter for number of operations
    long x(1);            // Start with x = 1, used to find maximum power of 2 <= r
    for (long p = 1; 2 * p <= r; p *= 2, ++cnt)  // Loop until 2*p > r
      ;
    printf("%ld\n", cnt); // Output the number of operations
  }
}


// https://github.com/VaHiX/codeForces/