// Problem: CF 1731 A - Joey Takes Money
// https://codeforces.com/contest/1731/problem/A

/*
 * Problem: A. Joey Takes Money
 * Purpose: Given an array of positive integers, perform operations to maximize
 *          the sum of the array elements, then multiply the result by 2022.
 * Algorithm:
 *   - Key Insight: To maximize the sum, we want to minimize the number of
 *     elements that are greater than 1. Each operation allows us to split
 *     two elements into two new elements whose product equals their original product.
 *   - Strategy: 
 *     1. Compute the product of all elements in the array.
 *     2. Add (n - 1) to the product (since we can reduce n elements to 1s by splitting,
 *        and we are left with one element whose value is the product).
 *     3. Multiply the final result by 2022.
 * Time Complexity: O(n) per test case, since we iterate through array once.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long n;
    scanf("%ld", &n); // Read size of array
    ll res(1); // Initialize result as 1, will hold the product of all elements
    
    for (long p = 0; p < n; p++) { // Iterate through each element
      ll x;
      scanf("%lld", &x); // Read current element
      res *= x; // Multiply it to the running product
    }
    
    res += (n - 1); // Add (n-1) to convert the final array into one large number and n-1 ones
    
    printf("%lld\n", 2022 * res); // Output result multiplied by 2022 as required
  }
}


// https://github.com/VaHiX/codeForces/