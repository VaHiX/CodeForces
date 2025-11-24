// Problem: CF 1853 B - Fibonaccharsis
// https://codeforces.com/contest/1853/problem/B

/*
B. Fibonaccharsis

Purpose:
This program counts the number of Fibonacci-like sequences of a given length k such that the k-th element is n.
A Fibonacci-like sequence satisfies f[i] = f[i-1] + f[i-2] for i > 2, where f[1] and f[2] can be arbitrary non-negative integers.

Algorithm:
1. Precompute Fibonacci numbers up to a limit (1e7) to avoid recomputation.
2. For each test case:
   - If k is too large, output 0 (no valid sequences).
   - Otherwise, iterate through possible values of the first two elements (a, b), and count how many combinations
     yield a sequence ending in n.

Time Complexity: O(F) + O(T * sqrt(n)) where F is the number of Fibonacci numbers computed (~35),
                 and T is the number of test cases.
Space Complexity: O(F) for storing Fibonacci numbers where F ~ 35 (constant due to log_φ(1e7)).

Techniques:
- Precomputing Fibonacci numbers.
- Brute-force over small possible starting values.
*/

#include <cstdio>
#include <vector>
int main() {
  std::vector<long> f(2); // Initialize first two Fibonacci numbers
  f[0] = 0;
  f[1] = 1;
  while (f.back() < 1e7) { // Generate Fibonacci sequence up to 1e7
    long n = f.size();
    f.push_back(f[n - 1] + f[n - 2]);
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k); // Read input values
    if (k >= f.size()) { // If k is too large for precomputed Fibonacci sequence
      puts("0");
      continue;
    }
    long a(f[k - 2]), b(f[k - 1]); // Use precomputed Fibonacci numbers as base for iteration
    long cnt(0);
    for (long u = 0; u < 1e6; u++) { // Loop through possible first terms
      long diff = n - a * u;
      if (diff < b * u) { // Early termination condition
        break;
      }
      cnt += (diff % b == 0); // Check divisibility for valid second term
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/