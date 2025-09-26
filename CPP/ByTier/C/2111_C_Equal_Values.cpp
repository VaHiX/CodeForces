// Problem: CF 2111 C - Equal Values
// https://codeforces.com/contest/2111/problem/C

/*
C. Equal Values

Algorithm: Greedy with prefix/suffix processing
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves making all array elements equal using two types of operations:
1. Make all elements to the left of position i equal to a[i], cost = (i - 1) * a[i]
2. Make all elements to the right of position i equal to a[i], cost = (n - i) * a[i]

We process the array from left to right and maintain a running calculation of:
- The minimal cost to make all elements equal
- Tracking the previous element value and the index of the last change

Key idea:
At each step, we calculate two potential operations:
- Left operation: make elements before current index equal to current element
- Right operation: make elements after current index equal to current element

We greedily choose the cheaper option and update the running cost accordingly.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll prev, left(0); // 'prev' tracks last unique value; 'left' tracks index of last change
    scanf("%lld", &prev);
    ll cost(prev * (n - 1)); // Initial cost if we make all elements equal to first element
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // Compute cost if we choose current element and apply a right operation at position p
      ll test = x * ((prev == x) ? (left + n - p - 1) : (n - 1));
      // Update left to the index after the last change if current element differs from previous
      left = (prev == x ? left : p);
      // Keep track of the minimum cost so far
      cost = (cost < test ? cost : test);
      prev = x; // Update previous element
    }
    printf("%lld\n", cost);
  }
}


// https://github.com/VaHiX/codeForces/