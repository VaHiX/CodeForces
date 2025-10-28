// Problem: CF 1744 B - Even-Odd Increments 
// https://codeforces.com/contest/1744/problem/B

/*
B. Even-Odd Increments 
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithms/Techniques:
- Efficient processing of queries by tracking sums and counts of odd/even numbers separately.
- Instead of updating each element individually, we maintain running totals and update counts accordingly.

Time Complexity: O(n + q) per test case, where n is the number of elements in the array and q is the number of queries.
Space Complexity: O(1), only using a few variables to store counts and sums.

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    ll ac(0), as(0), ts(0), tc(0); // ac: count of even numbers, as: sum of even numbers, ts: sum of odd numbers, tc: count of odd numbers
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x & 1) { // if x is odd
        ++tc;
        ts += x;
      } else { // if x is even
        ++ac;
        as += x;
      }
    }
    for (ll p = 0; p < q; p++) {
      int w;
      ll x;
      scanf("%d %lld", &w, &x);
      if (w) { // query type 1: add x to all odd elements
        ts += tc * x; // update the sum of odds by adding x * count of odds
        if (x & 1) { // if x is odd
          ac += tc; // all formerly odd numbers become even
          tc = 0; // no more odd numbers
          as += ts; // transfer the sum of odds to even sum
          ts = 0; // reset odd sum
        }
      } else { // query type 0: add x to all even elements
        as += ac * x; // update the sum of evens by adding x * count of evens
        if (x & 1) { // if x is odd
          tc += ac; // all formerly even numbers become odd
          ac = 0; // no more even numbers
          ts += as; // transfer the sum of evens to odd sum
          as = 0; // reset even sum
        }
      }
      printf("%lld\n", as + ts); // print total sum
    }
  }
}


// https://github.com/VaHiX/codeForces/