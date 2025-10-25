// Problem: CF 2072 A - New World, New Me, New Array
// https://codeforces.com/contest/2072/problem/A

/*
 * Problem: A. New World, New Me, New Array
 * Purpose: Determine the minimum number of operations to make the sum of an array of n zeros equal to k,
 *          where each element can be changed by at most p in one operation.
 *
 * Algorithms/Techniques:
 *   - Mathematical reasoning and greedy approach
 *   - Check if it's possible to reach k given constraints
 *   - Calculate minimum operations using ceiling division
 *
 * Time Complexity: O(t), where t is the number of test cases (constant time per test case)
 * Space Complexity: O(1), only using a few variables
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, p;
    scanf("%ld %ld %ld", &n, &k, &p);
    
    // Check if it is impossible to reach sum k
    // Maximum possible sum = n * p, minimum = -n * p
    if (k < -n * p || n * p < k) {
      puts("-1");
      continue;
    }
    
    // If k is negative, convert to positive for calculation purposes
    if (k < 0) {
      k = -k;
    }
    
    // Calculate minimum operations required using ceiling division
    // Each operation can change the sum by at most p
    printf("%ld\n", (k + p - 1) / p);
  }
}


// https://github.com/VaHiX/codeForces/