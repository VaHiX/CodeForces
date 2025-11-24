// Problem: CF 2008 G - Sakurako's Task
// https://codeforces.com/contest/2008/problem/G

/*
G. Sakurako's Task
Algorithms/Techniques: Number Theory (GCD), Mathematical reasoning, Greedy approach
Time Complexity: O(n log(max(a))) per test case
Space Complexity: O(1)

Problem Summary:
Given an array of integers and a value k, we can perform operations to modify elements.
The goal is to maximize the k-th missing non-negative integer from the array after any number of operations.

Key insight:
Using GCD properties, all numbers in the array will eventually become multiples or linear combinations of their GCD.
So, the final state of the array only depends on the GCD of all elements.
We are trying to find the maximum possible "k-th missing" value by using this transformed array.

Approach:
1. For n = 1: Only one element, so we need to adjust based on whether it's >= k.
2. For n > 1:
   - Reduce all values to their GCD (as per allowed operations).
   - Compute how much "space" we can fill using k + (n-1) * (d-1) where d = gcd(all elements).
   - If this value exceeds k, then we can set max possible missing to k + n - 1.
   - Otherwise, compute the exact count of k-th missing by solving a formula.

*/

#include <cstdio>
int t, n, k, d, a;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k), d = 0;
    for (int i = 0; i < n; ++i)
      scanf("%d", &a), d = gcd(d, a); // Compute GCD of all elements
    if (n == 1)                           // Special case when there is only one element
      printf("%d\n", k - (a >= k));
    else if (k > 1ll * (n - 1) * (d - 1)) // If k is large enough, we can get to k + n - 1 easily
      printf("%d\n", k + n - 1);
    else                                  // Otherwise, calculate exactly how far we can go
      a = (k + d - 2) / (d - 1) - 1, printf("%d\n", a + k);  // Compute the answer using formula
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/