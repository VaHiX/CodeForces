// Problem: CF 2022 B - Kar Salesman
// https://codeforces.com/contest/2022/problem/B

/*
B. Kar Salesman
Algorithms/Techniques: Greedy algorithm
Time Complexity: O(n) per test case
Space Complexity: O(1)

Karel needs to sell all cars by convincing customers to buy up to x cars each,
with the constraint that all cars a customer buys must be of different models.
We aim to minimize the number of customers required.

Approach:
1. For each test case, compute total cars (sa) and maximum cars of any single model (mxa).
2. The minimum customers needed is the maximum of:
   - Total cars rounded up by x (since each customer can buy at most x cars)
   - Maximum number of cars of a single model (as we must have at least that many customers to handle the largest group)

This greedy approach works because:
- If there are more cars than x, we need at least ceil(sa/x) customers.
- If one model has more cars than x, we must have at least mxa customers to serve this model.
- Therefore, the answer is max(ceil(sa/x), mxa).
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    ll sa(0), mxa(0); // sa: total cars, mxa: max cars of a single model
    for (ll p = 0; p < n; p++) {
      ll a;
      scanf("%lld", &a);
      sa += a; // accumulate total number of cars
      mxa = (mxa > a ? mxa : a); // track maximum number of cars in a model
    }
    ll res((sa + x - 1) / x); // ceiling division: (sa + x - 1) / x
    res = (res > mxa ? res : mxa); // take the larger of two values
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/