// Problem: CF 768 C - Jon Snow and his Favourite Number
// https://codeforces.com/contest/768/problem/C

/*
Algorithm: Simulation with Optimization
Approach:
- Sort the array of ranger strengths.
- For each operation, update the strength of every alternate ranger (starting from index 0) by XORing with x.
- Since the pattern of XOR operations repeats every 64 steps due to the nature of XOR and the limited range of values (up to 10^3), we can reduce k modulo 64 to avoid unnecessary iterations.
- After all operations, sort the array again to find the minimum and maximum values.

Time Complexity: O(n * log(n) * (k % 64)) where n <= 10^5 and k <= 10^5.
Space Complexity: O(n) for storing the array of strengths.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k, x;
  scanf("%ld %ld %ld", &n, &k, &x);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  k %= 64; // Optimization: cycle length for XOR is at most 64 due to small value constraint
  while (k--) {
    sort(a.begin(), a.end()); // Sort before each operation
    for (int p = 0; p < n; p += 2) {
      a[p] ^= x; // XOR operation on alternate elements
    }
  }
  sort(a.begin(), a.end()); // Final sort to get min and max
  printf("%ld %ld\n", a[n - 1], a[0]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/