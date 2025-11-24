// Problem: CF 1355 A - Sequence with Digits
// https://codeforces.com/contest/1355/problem/A

/*
 * Problem: A. Sequence with Digits
 * Algorithm: Recurrence relation simulation with digit extraction
 * Time Complexity: O(log a_1) per test case, since we process each digit once per step,
 *                  and the number of steps is bounded by a small constant due to the nature of the sequence.
 * Space Complexity: O(1), only using a few variables for computation.
 *
 * The recurrence relation is defined as:
 * a_{n+1} = a_n + minDigit(a_n) * maxDigit(a_n)
 *
 * We simulate this process, but optimize by stopping early if minDigit becomes 0,
 * because multiplying by 0 will not change the number further.
 */

#include <cstdio>
typedef long long ll;

// Function to compute product of minimum and maximum digits of a number
int getProduct(ll x) {
  int mn(10), mx(0);  // Initialize mn to 10 (max possible digit), mx to 0
  while (x > 0) {
    int cur = (x % 10);        // Extract last digit
    mn = (mn < cur) ? mn : cur; // Update minimum digit
    mx = (mx > cur) ? mx : cur; // Update maximum digit
    x /= 10;                   // Remove last digit
  }
  return mn * mx;  // Return product of min and max digits
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    // Simulate the recurrence up to k steps or until product becomes 0
    for (ll p = 1; p < k; p++) {
      int term = getProduct(n);   // Get min * max digit product
      if (term == 0) {            // If product is 0, no further change possible
        break;
      }
      n += term;                  // Add the product to current number
    }
    
    printf("%lld\n", n);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/