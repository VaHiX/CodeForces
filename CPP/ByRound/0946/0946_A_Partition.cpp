// Problem: CF 946 A - Partition
// https://codeforces.com/contest/946/problem/A

/*
 * Problem: Partition
 * Purpose: To find the maximum possible value of B - C, where B is the sum of elements in sequence b,
 *          and C is the sum of elements in sequence c. Each element of the input sequence must belong
 *          to exactly one of the two sequences.
 * 
 * Algorithm/Technique: Greedy approach
 *   - For each element in the array, if it's positive, add it to B (maximize B).
 *   - If it's negative, we add its absolute value to B and subtract it from C (effectively adding it to B).
 *   - This effectively maximizes B - C by ensuring all positive numbers go to B and all negative
 *     numbers are treated as if they contribute positively to B.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;                     // Read number of elements
  scanf("%ld", &n);
  long res(0);                // Initialize result to 0
  while (n--) {               // Process each element
    long x;
    scanf("%ld", &x);
    if (x > 0) {              // If element is positive, add it to result
      res += x;
    } else {                  // If element is negative, subtract it (equivalent to adding absolute value)
      res -= x;
    }
  }
  printf("%ld\n", res);       // Print the maximum value of B - C
  return 0;
}


// https://github.com/VaHiX/CodeForces/