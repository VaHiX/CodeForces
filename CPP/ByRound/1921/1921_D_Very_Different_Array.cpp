// Problem: CF 1921 D - Very Different Array
// https://codeforces.com/contest/1921/problem/D

/*
D. Very Different Array
Algorithms/Techniques: Greedy algorithm, sorting, two pointers
Time Complexity: O(n log n + m log m) per test case due to sorting
Space Complexity: O(n + m) for storing arrays a and b

The problem is about selecting n elements from array b and arranging them 
to maximize the total absolute difference with array a. 
This can be solved greedily by sorting a in ascending order and b in descending order.
Then, we use two pointers to match elements from a and b optimally:
- Pair smallest element of a with largest element of b (and vice versa)
- This ensures maximum difference at each step.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(m);
    for (ll p = 0; p < m; p++) {
      scanf("%lld", &b[p]);
    }
    sort(a.begin(), a.end());           // Sort array a in ascending order
    sort(b.rbegin(), b.rend());         // Sort array b in descending order
    ll diff(0), left(0), right(n - 1), idxL(0), idxR(m - 1);
    while (left <= right) {
      long curA = a[left] - b[idxL];     // Difference if we pair a[left] with b[idxL]
      curA = (curA > 0 ? curA : -curA);  // Absolute value
      long curB = a[right] - b[idxR];    // Difference if we pair a[right] with b[idxR]
      curB = (curB > 0 ? curB : -curB);  // Absolute value
      if (curA > curB) {                 // Choose the larger difference
        diff += curA;
        ++left;                          // Move to next element in a
        ++idxL;                          // Move to next element in b
      } else {
        diff += curB;
        --right;                         // Move to previous element in a
        --idxR;                          // Move to previous element in b
      }
    }
    printf("%lld\n", diff);
  }
}


// https://github.com/VaHiX/codeForces/