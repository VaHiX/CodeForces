// Problem: CF 1870 A - MEXanized Array
// https://codeforces.com/contest/1870/problem/A

/*
Problem: A. MEXanized Array

Purpose:
This program computes the maximum possible sum of elements in an array of length n,
where the MEX (minimum excluded value) is exactly k, and all elements are ≤ x.
The algorithm determines if such an array exists and calculates the optimal sum.

Algorithms/Techniques:
- Greedy approach to maximize sum while satisfying constraints
- Mathematical formula for arithmetic progression sum

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input Format:
- First line: number of test cases t
- For each test case: three integers n, k, x

Output Format:
- For each test case: maximum possible sum or -1 if impossible
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, x;
    scanf("%ld %ld %ld", &n, &k, &x);
    // Check if array can exist:
    // - n must be at least k (we need to place k distinct values)
    // - x must be at least k-1 (to form a sequence 0..k-1)
    if (n < k || x < k - 1) {
      puts("-1");
      continue;
    }
    // If x equals k, we cannot use k in our array because it would make MEX > k
    if (x == k) {
      --x;
    }
    // Calculate maximum sum:
    // First k-1 elements: 0 + 1 + ... + (k-2) = (k-1)*k/2
    // Remaining (n - k) elements: use maximum allowed value x
    long res = k * (k - 1) / 2 + (n - k) * x;
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/