// Problem: CF 2040 C - Ordered Permutations
// https://codeforces.com/contest/2040/problem/C

/*
C. Ordered Permutations
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms/Techniques:
- Bit manipulation to generate permutations in lexicographical order
- Greedy approach to construct the maximum sum permutation
- Efficient construction using binary representation of k

Time Complexity: O(n log k) per test case, where n is the length of the permutation and k is the index.
Space Complexity: O(n), for storing the vectors a, b, and d.

Description:
This code generates the k-th lexicographically smallest permutation of length n that maximizes S(p),
where S(p) is the sum over all subarrays of the minimum element in that subarray.
The approach uses bit manipulation to determine which elements should be placed where,
to achieve the desired maximum value and order.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    // Early check: if k is too large, no such permutation exists
    if ((n <= 62) && (1LL << (n - 1)) < k) {
      puts("-1");
      continue;
    }
    --k; // Convert to 0-based indexing
    
    std::vector<int> a, b, d;
    
    // Decompose k into binary representation
    while (k) {
      d.push_back(k % 2); // Store each bit
      k /= 2;             // Move to next bit
    }
    
    // Pad the binary representation to size n-1
    while (d.size() < n - 1) {
      d.push_back(0);
    }
    
    // Construct arrays a and b using the bits of k
    for (ll p = n - 2, j = 1; p >= 0; p--, j++) {
      if (!d[p]) {
        a.push_back(j);   // Place j in array a
      } else {
        b.push_back(j);   // Place j in array b
      }
    }
    
    std::reverse(b.begin(), b.end()); // Reverse b to ensure correct order
    
    // Output elements from a
    for (ll x : a) {
      printf("%lld ", x);
    }
    
    // Output the final element n
    printf("%lld ", n);
    
    // Output elements from b
    for (ll x : b) {
      printf("%lld ", x);
    }
    
    puts(""); // New line after outputting the permutation
  }
}


// https://github.com/VaHiX/codeForces/