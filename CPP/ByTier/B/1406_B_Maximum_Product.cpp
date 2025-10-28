// Problem: CF 1406 B - Maximum Product
// https://codeforces.com/contest/1406/problem/B

/*
B. Maximum Product
Problem Description:
Given an array of integers, find the maximum possible product of five distinct elements a_i * a_j * a_k * a_l * a_t where i < j < k < l < t.

Algorithm:
- Sort the array to easily access the largest and smallest elements.
- Consider only a few key combinations for the maximum product:
  1. Product of 5 largest elements (all positive or mixed).
  2. Product of 2 smallest (most negative) and 3 largest elements.
  3. Product of 4 smallest and 1 largest element.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage
*/

#include <algorithm>
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
      scanf("%lld", &a[p]); // Read all elements into vector
    }
    sort(a.begin(), a.end()); // Sort the array to easily access extremes
    
    // Compute three candidate products:
    ll prodA = a[n - 5] * a[n - 4] * a[n - 3] * a[n - 2] * a[n - 1]; // 5 largest
    ll prodB = a[0] * a[1] * a[n - 3] * a[n - 2] * a[n - 1];         // 2 smallest + 3 largest
    ll prodC = a[0] * a[1] * a[2] * a[3] * a[n - 1];                // 4 smallest + 1 largest
    
    ll res = (prodA > prodB) ? prodA : prodB; // Compare first two candidates
    res = (res > prodC) ? res : prodC;       // Compare with third candidate
    printf("%lld\n", res);                   // Print the maximum among all
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/