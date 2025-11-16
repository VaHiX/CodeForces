// Problem: CF 1609 A - Divide and Multiply
// https://codeforces.com/contest/1609/problem/A

#include <cstdio>
typedef long long ll;

/*
Purpose: Maximizes the sum of array elements by strategically dividing even numbers and multiplying others.
Algorithms/Techniques: 
    - Greedy approach with bit manipulation (dividing by 2 and multiplying by 2)
    - Track maximum value and accumulate smaller values during processing
    - Distribute all available division operations to increase the largest element

Time Complexity: O(n * log(max(a_i))) per test case, where n <= 15 and max(a_i) < 16
Space Complexity: O(1) - only using a few variables regardless of input size

*/
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll mx(0), cnt(0), res(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // Count total factors of 2 in x by repeatedly dividing by 2
      while (x % 2 == 0) {
        x /= 2;
        ++cnt;
      }
      // If current x is greater than the maximum seen so far,
      // add previous maximum to result and update maximum
      if (x > mx) {
        res += mx;
        mx = x;
      } else {
        // Otherwise, add x to result
        res += x;
      }
    }
    // Distribute all counted factors of 2 to the maximum element
    for (ll p = 0; p < cnt; p++) {
      mx *= 2;
    }
    res += mx;
    printf("%lld\n", res);
  }
}

// https://github.com/VaHiX/codeForces/