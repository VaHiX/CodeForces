// Problem: CF 2020 B - Brightness Begins
// https://codeforces.com/contest/2020/problem/B

/*
B. Brightness Begins

Algorithm:
The problem involves determining the minimum number of light bulbs `n` such that exactly `k` bulbs remain on after a series of operations.
Each operation i flips all bulbs j where j is divisible by i.

Key Insight:
A bulb at position j will be flipped once for each divisor of j. Since only perfect squares have an odd number of divisors, only bulbs at perfect square positions will end up ON.
Thus, the number of bulbs ON after all operations equals the number of perfect squares from 1 to n.

To find the smallest `n` such that there are exactly `k` perfect squares in [1, n], we solve for the smallest `n` where floor(sqrt(n)) = k.
This leads directly to the formula: n = k + floor(sqrt(k) + 0.5)

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/
#include <cmath>
#include <cstdio>
typedef long long ll;
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll k; // Target number of bulbs ON
    scanf("%lld", &k);
    // Formula to compute minimum n: n = k + floor(sqrt(k) + 0.5)
    printf("%lld\n", k + (ll)(sqrtl(k) + 0.5));
  }
}


// https://github.com/VaHiX/codeForces/