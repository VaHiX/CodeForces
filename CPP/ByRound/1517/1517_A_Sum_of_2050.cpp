// Problem: CF 1517 A - Sum of 2050
// https://codeforces.com/contest/1517/problem/A

/*
 * Problem: A. Sum of 2050
 * 
 * Purpose: Determine the minimum number of 2050-numbers (i.e., 2050, 20500, 205000, ...) 
 *          needed to sum up to a given number n. If impossible, output -1.
 * 
 * Algorithms/Techniques:
 *   - Check divisibility by 2050
 *   - Extract digits of quotient and sum them
 * 
 * Time Complexity: O(log n) per test case due to digit extraction
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
typedef long long ll;

int main() {
  const ll A = 2050; // Constant representing the base 2050 number
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    
    // If n is not divisible by 2050, it's impossible to represent as sum of 2050-numbers
    if (n % A) {
      puts("-1");
      continue;
    }
    
    ll d = n / A; // Quotient when dividing n by 2050
    ll res(0);    // Result to store sum of digits of quotient
    
    // Extract digits of the quotient and compute their sum
    while (d > 0) {
      res += (d % 10); // Add last digit to result
      d /= 10;         // Remove last digit
    }
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/