// Problem: CF 1392 C - Omkar and Waterslide
// https://codeforces.com/contest/1392/problem/C

/*
C. Omkar and Waterslide
Algorithm: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks us to make an array nondecreasing by performing operations where we can choose a contiguous nondecreasing subsegment and increment all elements in it by 1.
The greedy strategy is to iterate from left to right. For each element, if it's smaller than the previous one, we need to perform operations to bring it up to at least the level of the previous element. The number of such operations needed equals the difference between the previous and current element (if positive).

Key idea:
- Traverse the array once
- For each position, if current height is less than previous height, we must increment the elements in the subarray ending here by (previous - current)
- Accumulate total increments needed

This greedy approach works because when we move from left to right, any element that needs to be increased can only be affected by previous operations.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll prev;
    scanf("%lld", &prev);
    ll total(0); // Total operations needed
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ll diff = prev - x; // Calculate how much we need to increase current element
      diff = (diff > 0) ? diff : 0; // Only consider positive differences
      total += diff; // Add to total operations
      prev = x; // Update previous element
    }
    printf("%lld\n", total);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/