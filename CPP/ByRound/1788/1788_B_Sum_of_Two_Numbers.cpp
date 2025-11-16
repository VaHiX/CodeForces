// Problem: CF 1788 B - Sum of Two Numbers
// https://codeforces.com/contest/1788/problem/B

/*
 * Problem: Sum of Two Numbers
 * Algorithm: Greedy digit-by-digit construction
 * 
 * Approach:
 * - For each digit of the number n, we decide how to split it between x and y.
 * - We maintain a flag 'f' to balance the sums of digits of x and y.
 * - If a digit is odd, we flip the flag to redistribute the excess.
 * - Each digit is split such that the resulting sums of x and y differ by at most 1.
 * 
 * Time Complexity: O(log n) per test case, since we process each digit once.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(0), b(0), pow(1);
    bool f(0);
    while (n) {
      long x = n % 10;  // Extract last digit
      n /= 10;
      if (x % 2) {      // If digit is odd, toggle the flag to balance sums
        f = 1 - f;
      }
      a += pow * ((x + f) / 2);     // Distribute digit to x
      b += pow * ((x + 1 - f) / 2); // Distribute digit to y
      pow *= 10;                    // Move to next digit place
    }
    printf("%ld %ld\n", a, b);
  }
}


// https://github.com/VaHiX/CodeForces/