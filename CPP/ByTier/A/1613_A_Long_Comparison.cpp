// Problem: CF 1613 A - Long Comparison
// https://codeforces.com/contest/1613/problem/A

/*
Problem: A. Long Comparison
Purpose: Compare two large numbers represented as (x, p) where x is the base number and p is the number of trailing zeros.
Algorithms/Techniques:
    - Determine number of digits in each number by counting divisions by 10
    - Align the numbers by appending zeros to the smaller one
    - Compare digit by digit after alignment
Time Complexity: O(log(max(x1, x2))) per test case due to digit counting and comparison
Space Complexity: O(1) - only using a constant amount of extra variables

Input:
    - t: number of test cases
    - For each test case:
        - x1, p1: base number and trailing zeros for first number
        - x2, p2: base number and trailing zeros for second number
Output:
    - "<", ">", or "=" depending on comparison result
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, r;
    scanf("%lld %lld", &x, &r); // read first number's base and trailing zeros
    ll y, s;
    scanf("%lld %lld", &y, &s); // read second number's base and trailing zeros
    ll u(r), tx(x);
    while (tx) { // count digits in x
      tx /= 10;
      ++u;
    }
    ll v(s), ty(y);
    while (ty) { // count digits in y
      ty /= 10;
      ++v;
    }
    if (u < v) { // if first number has fewer digits, it's smaller
      puts("<");
    } else if (u > v) { // if first number has more digits, it's larger
      puts(">");
    } else { // same number of digits, align and compare
      while (r < s) { // append zeros to first number until lengths match
        y *= 10;
        --s;
      }
      while (s < r) { // append zeros to second number until lengths match
        x *= 10;
        --r;
      }
      if (x < y) {
        puts("<");
      } else if (x > y) {
        puts(">");
      } else if (x == y) {
        puts("=");
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/