// Problem: CF 2119 C - A Good Problem
// https://codeforces.com/contest/2119/problem/C

/*
C. A Good Problem

Algorithms/Techniques:
Bit manipulation, greedy strategy, construction of lexicographically smallest valid array.

Time Complexity: O(log(r)) per test case (due to bit manipulation loops)
Space Complexity: O(1) - only using a few variables

Problem Description:
Given four integers n, l, r, k, we need to find the lexicographically smallest array of length n,
where each element is between l and r inclusive, such that the bitwise AND of all elements
equals the bitwise XOR of all elements. If no such array exists, output -1.
We are only required to output the k-th element (1-indexed).

Approach:
The key insight is to understand when an array can satisfy the condition A & B & ... & X = A ^ B ^ ... ^ X.
For small n (n <= 2), we check directly. For larger n:
- If n is odd, we place l at the first position and construct rest with some valid values.
- If n is even and greater than 2, we try to make as many elements equal as possible,
  using a greedy method to find minimum lexicographical solution.
*/

#include <stdio.h>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, l, r, k;
    scanf("%lld %lld %lld %lld", &n, &l, &r, &k);
    if (n % 2) { // If odd length
      printf("%lld\n", l); // Simple case: first element is l
      continue;
    } else if (n == 2) { // If exactly two elements
      puts("-1"); // Cannot satisfy AND = XOR unless both are same, but we must be in [l,r]
      continue;
    }
    
    ll res(1); // Start with 1 to check powers of 2
    bool fl(false); // Flag to indicate if valid result was found
    
    while (res <= r) { // Loop through powers of 2 up to r
      if (res > l) { // If current power of 2 is greater than l
        fl = true;
        // Output based on whether k <= n - 2 or not
        printf("%lld\n", k <= n - 2 ? l : res);
        break;
      }
      res *= 2; // Move to next power of 2
    }
    
    if (!fl) { // If no valid value found
      puts("-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/