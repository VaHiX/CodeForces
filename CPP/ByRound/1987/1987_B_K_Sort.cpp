// Problem: CF 1987 B - K-Sort
// https://codeforces.com/contest/1987/problem/B

/*
B. K-Sort
Algorithms/Techniques: Greedy approach with tracking of maximum deficit and total operations.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1), only using a few variables for computation.

The problem asks to make an array non-decreasing by performing operations:
- Choose k indices and increase their values by 1, paying k+1 coins.
- Goal: minimize the total cost to make the array non-decreasing.

Approach:
- Traverse the array from left to right.
- For each element that is smaller than the previous one:
  - Calculate the difference (deficit).
  - Add this deficit to the total cost.
  - Track the maximum deficit seen so far.
- The result is total cost plus the maximum deficit since we can use one operation to cover
  the largest deficit with minimal additional cost.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll prev(0), total(0), mxd(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x >= prev) {
        prev = x;
      } else {
        ll diff = prev - x;
        total += diff;
        mxd = (mxd > diff ? mxd : diff);
      }
    }
    printf("%lld\n", total + mxd);
  }
}


// https://github.com/VaHiX/codeForces/