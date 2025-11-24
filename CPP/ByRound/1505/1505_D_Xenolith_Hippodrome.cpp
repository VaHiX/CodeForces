// Problem: CF 1505 D - Xenolith? Hippodrome?
// https://codeforces.com/contest/1505/problem/D

#include <cstdio>
#include <vector>
/*
D. Xenolith? Hippodrome?
Purpose: Determine if all digits in the base-M representation of N are unique.
Algorithm: Convert number N to base M representation and track seen digits.
Time Complexity: O(log_m(N)) - we process each digit once
Space Complexity: O(M) - for storing the boolean vector of size M
*/
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<bool> digits(m); // Track which digits (0 to M-1) have been seen
  bool res(true);
  while (n > 0) {
    long x = n % m; // Extract the least significant digit in base M
    if (digits[x]) { // If we've seen this digit before
      res = false; // Not unique, set result to false
      break;
    }
    digits[x] = true; // Mark this digit as seen
    n /= m; // Remove the last digit from N
  }
  puts(res ? "YES" : "NO"); // Output result
  return 0;
}

// https://github.com/VaHiX/codeForces/