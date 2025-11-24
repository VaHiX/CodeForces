// Problem: CF 1183 C - Computer Game
// https://codeforces.com/contest/1183/problem/C

/*
C. Computer Game
Algorithm: Binary search on the number of "just play" turns.
Time Complexity: O(q * log n)
Space Complexity: O(1)

For each query, we want to find the maximum number of turns where Vova just plays (decreases battery by 'a'),
and the rest of the turns are "play and charge" (decreases battery by 'b').

We perform binary search on the number of "just play" turns (x). For a given x:
- x turns use 'a' charge each
- (n - x) turns use 'b' charge each
- Total charge used = x * a + (n - x) * b

The constraint is that after n turns, the total charge used must be less than k.
We need to ensure that battery never drops to zero or below during any turn.
So we check if there exists valid assignment of "just play" and "play and charge" turns such that
the total energy consumed is less than k.

If k <= n * b, it's impossible because even playing and charging every turn would still consume at least n*b.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll k, n, a, b;
    scanf("%lld %lld %lld %lld", &k, &n, &a, &b);
    if (k <= n * b) {  // Impossible case: even playing and charging every turn is not enough
      puts("-1");
      continue;
    }
    ll x(0), y(n), res(n);  // Binary search bounds [x, y], initial result = n
    while (x <= y) {
      ll z = (x + y) / 2;  // Midpoint number of "just play" turns
      if (z * a + (n - z) * b < k) {  // If total charge used is less than k, this is valid
        res = z;  // Store this as a potential answer
        x = z + 1;  // Try to increase number of "just play" turns
      } else {
        y = z - 1;  // Need to decrease number of "just play" turns
      }
    }
    printf("%lld\n", res);  // Print the maximum valid number of "just play" turns
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/