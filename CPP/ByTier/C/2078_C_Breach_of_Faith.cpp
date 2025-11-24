// Problem: CF 2078 C - Breach of Faith
// https://codeforces.com/contest/2078/problem/C

/*
C. Breach of Faith
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Breach of Faith - Supire feat.eili

Problem Description:
Given a shuffled sequence b of 2n integers, we need to reconstruct the original sequence a of 2n+1 integers such that:
- All elements are distinct and in range [1, 10^18]
- The alternating sum formula holds: a1 = a2 - a3 + a4 - a5 + ... + a_{2n} - a_{2n+1}
- Sequence b is the result of removing one element from a and shuffling the remaining elements.

Algorithm:
1. Sort the given sequence b.
2. To form a valid sequence a, we try to construct it by placing the largest element at the end,
   then interleaving the rest in a way that satisfies the alternating sum formula.
3. The key insight is to use the sorted array and insert one missing element (the one originally deleted),
   which can be calculated using the alternating sum constraint.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector

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
    std::vector<ll> v(2 * n);
    for (ll p = 0; p < 2 * n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the sequence to help reconstruct
    ll sumdiff(v.back());     // Initialize with the last element (to be placed at end)
    printf("%lld ", v.back()); // Output the last element first
    
    for (ll p = 0; p < 2 * n - 2; p++) {
      printf("%lld ", v[p]);            // Output elements in sorted order
      sumdiff += (p % 2 ? 1 : -1) * v[p]; // Apply alternating sign for calculation
    }
    
    printf("%lld %lld\n", sumdiff + v[2 * n - 2], v[2 * n - 2]); 
    // Final element is calculated using alternating sum formula and placed at end
  }
}


// https://github.com/VaHiX/codeForces/