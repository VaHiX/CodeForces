// Problem: CF 893 B - Beautiful Divisors
// https://codeforces.com/contest/893/problem/B

/*
Algorithm: Beautiful Divisors
Approach:
- Generate all possible "beautiful numbers" up to a certain limit.
- A beautiful number is of the form (2^k - 1) * (2^(k-1)), which in binary is k ones followed by k zeros.
- Since n <= 10^5, we only need to check up to k = 14, because 2^14 > 10^5.
- For each generated beautiful number, check if it divides n.
- Return the largest such divisor.

Time Complexity: O(1) - Since we iterate through a fixed number of values (k from 1 to 13), the number of operations is constant.
Space Complexity: O(1) - The vector stores a constant number of values (13 elements).
*/

#include <cstdio>
#include <vector>
int main() {
  const int B = 14;
  std::vector<long> div;
  for (long p = 1; p < B; p++) {
    long u = (1 << p);  // Compute 2^p
    div.push_back((u - 1) * u / 2);  // Generate beautiful number (2^p - 1) * 2^(p-1)
  }
  long n;
  scanf("%ld", &n);
  long res(0);
  for (long p = 0; p < div.size(); p++) {
    if (n % div[p] == 0) {
      res = div[p];  // Keep the largest beautiful divisor found
    }
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/