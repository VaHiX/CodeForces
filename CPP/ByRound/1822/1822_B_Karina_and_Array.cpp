// Problem: CF 1822 B - Karina and Array
// https://codeforces.com/contest/1822/problem/B

/*
Problem: Karina and Array
Purpose: Given an array of integers, find the maximum product of two adjacent elements after removing some elements (at least 2 elements must remain).

Algorithms/Techniques:
- Sorting
- Greedy selection of two largest/smallest products from sorted array

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

Approach:
1. Sort the array.
2. The maximum product of adjacent elements will be either:
   - Product of two smallest elements (handles negative numbers well)
   - Product of two largest elements
3. Compare these two cases and return the maximum.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]); // Read each element into vector
    }
    sort(a.begin(), a.end()); // Sort the array to easily access smallest and largest elements
    
    ll u = a[0] * a[1];       // Product of two smallest elements
    ll v = a[n - 2] * a[n - 1]; // Product of two largest elements
    
    printf("%lld\n", u > v ? u : v); // Output the maximum of the two products
  }
}


// https://github.com/VaHiX/codeForces/