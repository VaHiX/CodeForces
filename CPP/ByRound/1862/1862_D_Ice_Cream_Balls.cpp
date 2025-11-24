// Problem: CF 1862 D - Ice Cream Balls
// https://codeforces.com/contest/1862/problem/D

/*
D. Ice Cream Balls
Purpose: Given n different types of ice cream cones (each made from two balls), determine the minimum number of balls needed to create exactly n unique combinations.
Algorithm: Binary search on the answer. For a given number of ball types k, the total number of 2-ball combinations is k*(k-1)/2 + k = k*(k+1)/2. 
           This is because we can choose two distinct balls in k*(k-1)/2 ways and same ball in k ways.
           We binary search for the smallest k such that k*(k+1)/2 >= n.

Time Complexity: O(t * log(max_n)) where max_n = 1e18, so effectively O(t * 60) due to logarithmic search.
Space Complexity: O(1)

Techniques:
- Binary Search
- Mathematical formula for combinations with repetition
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(0), left(0), right(2e9 + 15); // Initialize binary search bounds
    while (left <= right) {
      ll mid = (left + right) / 2; // Midpoint for binary search
      ll comb = mid * (mid - 1) / 2; // Number of unique pairs from 'mid' elements
      if (comb <= n) {
        res = mid + (n - comb); // Calculate minimum balls required with this combination count
        left = mid + 1; // Search higher values
      } else {
        right = mid - 1; // Search lower values
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/