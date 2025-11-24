// Problem: CF 1873 E - Building an Aquarium
// https://codeforces.com/contest/1873/problem/E

/*
E. Building an Aquarium

Algorithms/Techniques: Binary Search on Answer, Prefix Sum (Implicit)

Time Complexity: O(n * log(max_height)) where max_height <= 2e9
Space Complexity: O(1) excluding input storage

Problem Summary:
Given a piece of coral made of n columns with heights a[i], we want to find the maximum height h 
such that filling up the tank to height h requires at most x units of water. Water needed for 
each column is max(0, h - a[i]).

Approach:
We use binary search on the answer (height h). For each candidate height, we calculate the total 
water required using the volume function. If it's within the limit x, we try a higher height; otherwise, 
we try a lower height.

Key Observations:
- The minimum possible height is 1.
- The maximum possible height is bounded by the constraint that total water used cannot exceed x.
- Since each column contributes at most (h - a[i]) water, and we can't use more than x water,
  we can bound the max height reasonably.

The volume function computes how much water is needed to fill all columns up to height h.
*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// Calculates total water needed to raise all columns to height h
ll volume(const std::vector<ll> &v, ll h) {
  ll total(0);
  for (ll p = 0; p < v.size(); p++) {
    total += (h > v[p]) * (h - v[p]); // Add water only if current column is shorter than h
  }
  return total;
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll left(0), right(2e9 + 7), res(0); // Binary search bounds
    while (left <= right) {
      ll height = (left + right) / 2;
      ll vol = volume(a, height);
      if (vol <= x) {
        res = height;
        left = height + 1; // Try for larger height
      } else {
        right = height - 1; // Try for smaller height
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/