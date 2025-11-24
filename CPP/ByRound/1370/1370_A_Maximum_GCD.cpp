// Problem: CF 1370 A - Maximum GCD
// https://codeforces.com/contest/1370/problem/A

#include <cstdio>
// Flowerbox describing code purpose, algorithms, and complexity
/*
Problem: Maximum GCD
Task: Find the maximum possible greatest common divisor (GCD) of any two distinct integers in the range [1, n].
Algorithm:
- For any pair of distinct integers a and b where 1 <= a < b <= n, we want to maximize gcd(a, b).
- The key insight is that the maximum GCD occurs when we choose two multiples of some number d such that both multiples are within [1, n].
- To maximize d, we consider the largest possible d such that there exist at least two multiples of d in [1, n].
- If n is even, then n/2 is the maximum possible GCD (since we can take 2 and n).
- If n is odd, then (n-1)/2 is the maximum possible GCD (since we can take 1 and n-1).
Time Complexity: O(1) per test case
Space Complexity: O(1)
*/
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long n;
    scanf("%ld", &n); // Read the value of n
    printf("%ld\n", n / 2); // Output the maximum GCD, which is n/2
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/