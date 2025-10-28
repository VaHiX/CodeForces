// Problem: CF 1196 A - Three Piles of Candies
// https://codeforces.com/contest/1196/problem/A

/*
Problem: Three Piles of Candies
Algorithm/Technique: Greedy, Math
Time Complexity: O(1)
Space Complexity: O(1)

Alice and Bob want to divide three piles of candies as fairly as possible.
Alice picks one pile, Bob picks another, and the last pile is split between them.
They both act optimally to maximize their final number of candies.

The key insight is that after分配, both players should end up with the same number of candies,
and we want to maximize this common amount. The maximum possible value is (x + y + z) / 2,
because in the best case, all candies can be split evenly between Alice and Bob.

For each test case:
- Read three integers a, b, c representing pile sizes.
- Output (a + b + c) / 2.

Sample Input:
4
1 3 4
1 10 100
10000000000000000 10000000000000000 10000000000000000
23 34 45

Sample Output:
4
55
15000000000000000
51
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);  // Read number of test cases
  while (t--) {
    ll x, y, z;
    scanf("%lld %lld %lld", &x, &y, &z);  // Read three pile sizes
    printf("%lld\n", (x + y + z) / 2);   // Output maximum candies Alice can have
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/