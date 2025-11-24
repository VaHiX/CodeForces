// Problem: CF 2008 C - Longest Good Array
// https://codeforces.com/contest/2008/problem/C

/*
C. Longest Good Array
Algorithm: Binary search on the answer.
Time Complexity: O(t * log(r - l))
Space Complexity: O(1)

Problem Description:
Given bounds l and r, we want to construct a "good" array of maximum length,
where:
1. The array is strictly increasing.
2. The differences between adjacent elements are also strictly increasing.

Approach:
We binary search on the length of the array. For a given length n, we try to
construct the minimum possible array that satisfies the constraints, and check
if this array's last element fits within [l, r].

The minimum good array starts with a[0] = l and uses the smallest valid
increments: 1, 2, 3, ..., (n-1). This leads to an arithmetic-like sequence
where the total length is approximately n*(n-1)/2.

We compute how much space we need for such an array and compare with r - l.
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b;            // a = l, b = r
    scanf("%lld %lld", &a, &b);
    ll dist = b - a;    // Distance between bounds
    ll left(1), right(dist + 7), res(1);  // Binary search bounds and result
    
    while (left <= right) {
      ll mid = (left + right) / 2;         // Midpoint of binary search
      ll tst = mid * (mid - 1) / 2;        // Minimum required distance for length 'mid'
      
      if (tst <= dist) {                   // If we can fit this length
        res = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/