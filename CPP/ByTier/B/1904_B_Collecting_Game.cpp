// Problem: CF 1904 B - Collecting Game
// https://codeforces.com/contest/1904/problem/B

/*
B. Collecting Game
Algorithms/Techniques: Sorting, Greedy, Prefix/Suffix Processing

Time Complexity: O(n log n) per test case due to sorting;
Space Complexity: O(n) for storing the array and auxiliary vectors.

Problem Description:
Given an array of positive integers, for each element a[i], if we use it to start a game
with score a[i], we can remove elements that are less than or equal to our current score.
We want to compute, for each i, how many additional elements we can remove after using a[i] as the starting score.

Approach:
1. Sort the array to process elements in increasing order.
2. For each element in sorted order, determine whether we can "stop" (i.e., not proceed further)
   based on if the accumulated sum is less than the next element.
3. Use a prefix-like logic with backward pass to track the stopping points.
4. Reconstruct final answer by mapping back elements to their original indices.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::pair<ll, ll>> a(n); // Store value and original index
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p].first);
      a[p].second = p; // Keep track of original index
    }
    sort(a.begin(), a.end()); // Sort by value
    
    std::vector<ll> stop(n, 0); // Stores stopping flags for each element in sorted order
    
    ll cs(a[0].first); // cumulative sum initialized with first element
    
    for (ll p = 1; p < n; p++) {
      if (cs < a[p].first) { // If cumulative sum is less than current element, we cannot proceed
        stop[p - 1] = 1; // Mark this as a stopping point
      }
      cs += a[p].first; // Add current value to cumulative sum
    }
    
    ll idx(n - 1); // Index to track last valid stopping position
    
    for (ll p = n - 1; p >= 0; p--) {
      if (stop[p]) { // If we marked this index as a stop
        idx = p; // Update the rightmost stopping index
      }
      stop[p] = idx; // Assign to all prior indices up till last stop
    }
    
    std::vector<ll> f(n); // Final result vector
    
    for (ll p = 0; p < n; p++) {
      f[a[p].second] = stop[p]; // Map result back to original indices
    }
    
    for (ll p = 0; p < n; p++) {
      printf("%lld ", f[p]); // Print results
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/