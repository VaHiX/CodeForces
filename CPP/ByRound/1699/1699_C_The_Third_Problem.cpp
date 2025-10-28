// Problem: CF 1699 C - The Third Problem
// https://codeforces.com/contest/1699/problem/C

/*
C. The Third Problem
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Algorithm:
This problem involves counting the number of permutations that are "similar" to a given permutation,
where two permutations are similar if they have the same MEX for every subarray.
The key insight is to track the range of positions where elements 0, 1, ..., n-1 appear.
We process elements in order from 0 to n-1 and maintain the leftmost and rightmost position 
of all processed elements so far. When a new element's position falls within that range,
it contributes to the number of valid permutations.

The idea is based on maintaining an interval [left, right] representing where all previously 
processed elements have appeared. For each new element:
- If its position is outside this interval, extend one side
- If it's inside the interval, then we must choose how many ways we can place it without changing MEX values,
  which equals (right - left + 1 - current_position)
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n), pos(n); // pos[i] stores the position of value i in input array
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      pos[a[p]] = p; // store the index of each number
    }
    ll left(pos[0]), right(pos[0]), cnt(1); // Initialize with position of element 0
    for (ll p = 1; p < n; p++) {
      if (pos[p] < left) { // New element is to the left of current range
        left = pos[p];
      } else if (pos[p] > right) { // New element is to the right of current range
        right = pos[p];
      } else {
        // New element falls inside current range, so multiply by number of choices for valid positions
        cnt = cnt * (right - left + 1 - p) % MOD;
      }
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/