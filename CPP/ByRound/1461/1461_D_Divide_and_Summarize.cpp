// Problem: CF 1461 D - Divide and Summarize
// https://codeforces.com/contest/1461/problem/D

/*
 * Problem: D. Divide and Summarize
 * Algorithms/Techniques: Divide and Conquer, Binary Search on Sorted Array
 *
 * Time Complexity:
 *   - Preprocessing (sorting + generating all possible sums): O(n * log n + 2^n)
 *   - Each query: O(1)
 * Space Complexity:
 *   - O(2^n) for storing all possible subset sums in a set
 *
 * The algorithm uses a divide-and-conquer approach to generate all possible sums
 * that can be achieved by choosing subsets of elements from the sorted array,
 * where each step splits the array based on the midpoint between min and max values.
 */
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

// Recursively computes all possible subset sums from a segment of array 'a'
// The recursion splits the array into left and right parts based on 'mid',
// which is the floor of (min + max) / 2
void getSums(const std::vector<ll> &a, std::set<ll> &sums, ll start, ll end) {
  if (start >= end) {
    return; // Base case: empty segment
  }
  ll cs(0);
  for (ll p = start; p < end; p++) {
    cs += a[p]; // Compute sum of current segment
  }
  sums.insert(cs); // Insert the sum of current segment into set

  if (a[start] == a[end - 1]) {
    return; // All elements are same, no further splits possible
  }

  ll mid = (a[start] + a[end - 1]) / 2; // Midpoint for splitting
  ll idx(start);
  while (a[idx] <= mid) {
    ++idx; // Find first element > mid
  }
  
  getSums(a, sums, start, idx);   // Recurse on left part
  getSums(a, sums, idx, end);     // Recurse on right part
  return;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to enable binary search logic
    std::set<ll> s;
    getSums(a, s, 0, n); // Generate all possible sums
    
    while (q--) {
      ll x;
      scanf("%lld", &x);
      puts(s.count(x) ? "Yes" : "No"); // Check if sum exists among possible ones
    }
  }
}


// https://github.com/VaHiX/codeForces/