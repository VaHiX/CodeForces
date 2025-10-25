// Problem: CF 1657 B - XY Sequence
// https://codeforces.com/contest/1657/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n, b, x, y; // n: length of sequence, b: max allowed value, x/y: step sizes
    scanf("%lld %lld %lld %lld", &n, &b, &x, &y);
    ll cur(0), res(0); // cur: current value in sequence, res: running sum
    for (ll p = 0; p < n; p++) {
      if (cur + x <= b) { // if adding x won't exceed limit
        cur += x; // take the step of x
      } else {
        cur -= y; // otherwise subtract y to stay within bounds
      }
      res += cur; // accumulate current value into result
    }
    printf("%lld\n", res);
  }
}
/*
B. XY Sequence

Algorithms/Techniques: Greedy algorithm

Time Complexity: O(n) per test case
Space Complexity: O(1)

The solution uses a greedy strategy:
- At each step, try to increase the value by x if possible.
- If that would exceed the bound B, decrease by y instead.
This ensures we maximize the sum while respecting the constraint that all values must be <= B.
*/

// https://github.com/VaHiX/codeForces/