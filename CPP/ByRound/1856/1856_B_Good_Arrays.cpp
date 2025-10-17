// Problem: CF 1856 B - Good Arrays
// https://codeforces.com/contest/1856/problem/B

/*
B. Good Arrays
Algorithm: For each test case, we analyze if we can construct a "good" array b such that:
- All elements of b are positive integers
- Sum of elements in b equals sum of elements in a
- No element in b is equal to the corresponding element in a

The key insight:
- If n == 1, there's no way to make a good array (only one element, so b[0] must equal a[0])
- For n > 1, we compute a "cost" value cs by processing each element of array a.
    - If x == 1, we decrement the cost (cs--), as this is the minimal possible
      contribution if we are to avoid using 1 in b.
    - Otherwise, we add (x - 1) to the cost, which represents how much extra we 
      can afford to have in our constructed array to still maintain valid sum, 
      while avoiding equality with a[i].

If at any point the sum of such adjustments (cs) is non-negative,
we can construct a good array; otherwise not.

Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long cs(0); // Cost variable to track adjustments needed
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == 1) {
        --cs; // If current element is 1, we decrease cost (we're saving 1 for later)
      } else {
        cs += (x - 1); // Add the surplus we can use to construct good array
      }
    }
    puts((n > 1) && (cs >= 0) ? "YES" : "NO"); // Output result based on conditions
  }
}


// https://github.com/VaHiX/codeForces/