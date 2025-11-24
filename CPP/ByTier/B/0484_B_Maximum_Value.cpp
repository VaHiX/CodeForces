// Problem: CF 484 B - Maximum Value
// https://codeforces.com/contest/484/problem/B

/*
Purpose: Find the maximum value of (a[i] % a[j]) such that a[i] >= a[j] and 1 <= i, j <= n.
Algorithm: 
    - Use a frequency-like array to mark presence of elements.
    - Preprocess a "max suffix" array to efficiently compute maximum values up to a point.
    - For each number p that is present in input, iterate through its multiples q (starting from 2*p) and 
      compute the remainder of the maximum value seen so far (in b[q-1]) when divided by p.
    - Track the maximum remainder encountered.

Time Complexity: O(N * log(N)) where N is the maximum value (1e6).
Space Complexity: O(N) for the arrays a and b.

*/
#include <cstdio>
#include <vector>
long max(long x, long y) { return (x > y) ? x : y; }
int main() {
  const long N = 2000007;
  std::vector<long> a(N), b(N);  // a marks presence of numbers, b stores max prefix
  long n;
  scanf("%ld", &n);
  while (n--) {
    long x;
    scanf("%ld", &x);
    a[x] = x;  // Mark the presence of x
  }
  for (long p = 1; p < N; p++) {
    b[p] = max(b[p - 1], a[p]);  // Build max prefix array
  }
  long res(0);  // Result to store maximum remainder
  for (long p = 2; p < N; p++) {
    if (!a[p]) {
      continue;  // Skip if p is not in input
    }
    for (long q = 2 * p; q < N; q += p) {
      res = max(res, b[q - 1] % a[p]);  // Compute remainder and update result
    }
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/