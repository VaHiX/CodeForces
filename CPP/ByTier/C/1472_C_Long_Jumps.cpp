// Problem: CF 1472 C - Long Jumps
// https://codeforces.com/contest/1472/problem/C

/*
C. Long Jumps
Algorithms/Techniques: Dynamic Programming (backward pass)
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Problem Description:
Given an array of integers, find the maximum score achievable by choosing a starting position 
and following rules where from index i, you move to i + a[i] and add a[i] to your score until 
you go out of bounds.

Approach:
Use dynamic programming going backwards. For each position, if it's possible to jump 
from that position (i.e., i + a[i] < n), update the current value by adding the value 
at the next reachable position. This ensures we compute the maximum score obtainable 
from each index in a bottom-up manner.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll mx(0); // Initialize maximum score
    for (ll p = n - 1; p >= 0; p--) {
      if (p + a[p] < n) {
        // If we can make a jump, add the score from the next position
        ll x = a[p + a[p]]; 
        a[p] += x;
      }
      // Update global maximum score
      mx = (mx > a[p]) ? mx : a[p];
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/